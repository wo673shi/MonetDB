/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2018 MonetDB B.V.
 */

#include "monetdb_config.h"
#include "gdk.h"
#include "mal_exception.h"
#include "mal_interpreter.h"
#include "mal_instruction.h"
#include "mal_weld.h"
#include "weld.h"

#define STR_SIZE_INC 4096
#define OP_GET 0
#define OP_SET 1

/* Variables in Weld will be named vXX - e.g. v19 
 * */

#define getOrSetStructMemberImpl(ADDR, TYPE, VALUE, OP)                 \
	if ((long)*ADDR % sizeof(TYPE) != 0)                                \
		*ADDR += sizeof(TYPE) - (long)*ADDR % sizeof(TYPE); /* aling */ \
	if (OP == OP_GET)                                                   \
		*(TYPE *)VALUE = *(TYPE *)(*ADDR); /* get */                    \
	else                                                                \
		*(TYPE *)(*ADDR) = *(TYPE *)VALUE; /* set */                    \
	*ADDR += sizeof(TYPE);				   /* increase */

struct weldMinMax {
	char i8min, i8max;
	int i32min, i32max;
	long i64min, i64max;
	float f32min, f32max;
	double f64min, f64max;
} weldMinMaxInst = {SCHAR_MIN, SCHAR_MAX, INT_MIN, INT_MAX, LLONG_MIN,
					LLONG_MAX, FLT_MIN,   FLT_MAX, DBL_MIN, DBL_MAX};

static void prependWeldStmt(weldState *wstate, str weldStmt) {
	if (strlen(wstate->program) + strlen(weldStmt) >= wstate->programMaxLen) {
		wstate->programMaxLen = strlen(wstate->program) + strlen(weldStmt) + 1;
		wstate->program = realloc(wstate->program, wstate->programMaxLen * sizeof(char));
	}
	memmove(wstate->program + strlen(weldStmt), wstate->program, strlen(wstate->program) + 1);
	memcpy(wstate->program, weldStmt, strlen(weldStmt));
}

static void appendWeldStmt(weldState *wstate, str weldStmt) {
	if (strlen(wstate->program) + strlen(weldStmt) >= wstate->programMaxLen) {
		wstate->programMaxLen = strlen(wstate->program) + strlen(weldStmt) + 1;
		wstate->program = realloc(wstate->program, wstate->programMaxLen * sizeof(char));
	}
	wstate->program = strcat(wstate->program, weldStmt);
}

static str getWeldType(int type) {
	if (type == TYPE_bte)
		return "i8";
	else if (type == TYPE_int)
		return "i32";
	else if (type == TYPE_lng)
		return "i64";
	else if (type == TYPE_flt)
		return "f32";
	else if (type == TYPE_dbl)
		return "f64";
	else if (type == TYPE_str)
		return "vec[i8]";
	else if (ATOMstorage(type) != type)
		return getWeldType(ATOMstorage(type));
	else
		return NULL;
}

static str getWeldUTypeFromWidth(int width) {
	if (width == 1)
		return "u8";
	else if (width == 2)
		return "u16";
	else if (width == 4)
		return "u32";
	else
		return "u64";
}

static void getOrSetStructMember(char **addr, int type, void *value, int op) {
	if (type == TYPE_bte) {
		getOrSetStructMemberImpl(addr, char, value, op);
	} else if (type == TYPE_int) {
		getOrSetStructMemberImpl(addr, int, value, op);
	} else if (type == TYPE_lng) {
		getOrSetStructMemberImpl(addr, long, value, op);
	} else if (type == TYPE_flt) {
		getOrSetStructMemberImpl(addr, float, value, op);
	} else if (type == TYPE_dbl) {
		getOrSetStructMemberImpl(addr, double, value, op);
	} else if (type == TYPE_str) {
		getOrSetStructMemberImpl(addr, char*, value, op);
	} else if (type == TYPE_ptr) {
		/* TODO - will assume that all pointers have the same size */
		getOrSetStructMemberImpl(addr, char*, value, op);
	} else if (ATOMstorage(type) != type) {
		return getOrSetStructMember(addr, ATOMstorage(type), value, op);
	}
}

/* Candidate lists can be dense so we have to replace them with a rangeiter */
static str getWeldCandList(int sid, bat s) {
	static char candList[STR_SIZE_INC];
	BAT *list = is_bat_nil(s) ? NULL : BATdescriptor(s);
	if (list == NULL || !BATtdense(list)) {
		sprintf(candList, "v%d", sid);
	} else {
		sprintf(candList, "rangeiter(%ldL, %ldL, 1L)", list->tseqbase,
				list->tseqbase + list->batCount);
	}
	return candList;
}

/* Candidate lists can be dense so we have to replace them with a rangeiter */
static str getWeldCandListFull(int sid, bat s) {
	static char candList[STR_SIZE_INC];
	BAT *list = is_bat_nil(s) ? NULL : BATdescriptor(s);
	if (list == NULL || !BATtdense(list)) {
		sprintf(candList, "v%d", sid);
	} else {
		sprintf(candList,
				"result(for(rangeiter(%ldL, %ldL, 1L), appender[?], |b, i, x| merge(b, x)))",
				list->tseqbase, list->tseqbase + list->batCount);
	}
	return candList;
}

static void dumpProgram(weldState *wstate, MalBlkPtr mb) {
	FILE *f = fopen(tmpnam(NULL), "w");
	int i;
	for (i = 0; i < mb->stop; i++) {
		fprintInstruction(f, mb, NULL, mb->stmt[i], LIST_MAL_ALL);
	}
	fprintf(f, "\n\n\n");
	for (i = 0; i < (int)strlen(wstate->program); i++) {
		fputc(wstate->program[i], f);
		if (wstate->program[i] != '\t' && wstate->program[i + 1] == '\t')
			fputc('\n', f);
		if (wstate->program[i] == ';')
			fputc('\n', f);
	}
	fclose(f);
}

str
WeldInitState(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	weldState *wstate = malloc(sizeof(weldState));
	wstate->programMaxLen = 1;
	wstate->program = calloc(wstate->programMaxLen, sizeof(char));
	wstate->groupDeps = calloc(mb->vtop, sizeof(InstrPtr));
	*getArgReference_ptr(stk, pci, 0) = wstate;;
	return MAL_SUCCEED;
}

str
WeldRun(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	(void)mb;
	weldState *wstate = *getArgReference_ptr(stk, pci, pci->retc);
	int i, j, inputLen = 0, inputMaxLen = 0, outputLen = 0, outputMaxLen = 0;
	str inputStmt = NULL, outputStmt = NULL;

	/* Build the input stmt, e.g.: |v13:i32, v50:vec[i8], v50hseqbase:i64| */
	for (i = pci->retc + 1; i < pci->argc; i++) { /* skip wstate on pci->retc */
		if (inputLen + 128 > inputMaxLen) {
			inputMaxLen += STR_SIZE_INC;
			inputStmt = realloc(inputStmt, inputMaxLen * sizeof(char));
		}
		int type = getArgType(mb, pci, i);
		if (isaBatType(type) && getBatType(type) != TYPE_str) {
			inputLen += sprintf(inputStmt + inputLen, " v%d:vec[%s], v%dhseqbase:i64,",
								getArg(pci, i), getWeldType(getBatType(type)), getArg(pci, i));
		} else if (isaBatType(type) && getBatType(type) == TYPE_str) {
			bat bid = *getArgReference_bat(stk, pci, i);
			BAT *b = BATdescriptor(bid);
			if (b == NULL) throw(MAL, "weld.run", SQLSTATE(HY002) RUNTIME_OBJECT_MISSING);
			inputLen += sprintf(inputStmt + inputLen,
								" v%d:vec[%s], v%dhseqbase:i64, v%dstr:vec[i8], v%dstroffset:i64,",
								getArg(pci, i), getWeldUTypeFromWidth(b->twidth), getArg(pci, i),
								getArg(pci, i), getArg(pci, i));
		} else {
			inputLen +=
				sprintf(inputStmt + inputLen, " v%d:%s,", getArg(pci, i), getWeldType(type));
		}
	}
	/* Min/Max constants for the Weld types */
	if (inputLen + 128 > inputMaxLen) {
		inputMaxLen += STR_SIZE_INC;
		inputStmt = realloc(inputStmt, inputMaxLen * sizeof(char));
	}
	inputLen += sprintf(inputStmt + inputLen,
						"i8MIN:i8, i8MAX:i8, i32MIN:i32, i32MAX:i32, i64MIN:i64, i64MAX:i64, "
						"f32MIN:f32, f32MAX:f32, f64MIN:f64, f64MAX:f64 ");

	inputStmt[0] = '|';
	inputStmt[inputLen - 1] = '|';
	prependWeldStmt(wstate, inputStmt);
	free(inputStmt);
	/* Build the output stmt, e.g.: {v1, v99} */
	for (i = 0; i < pci->retc; i++) {
		if (outputLen + 128 > outputMaxLen) {
			outputMaxLen += STR_SIZE_INC;
			outputStmt = realloc(outputStmt, outputMaxLen * sizeof(char));
		}
		int type = getArgType(mb, pci, i);
		outputLen += sprintf(outputStmt + outputLen, " v%d,", getArg(pci, i));
		if (isaBatType(type) && getBatType(type) == TYPE_str) {
			/* Also return the string column base ptr */
			outputLen += sprintf(outputStmt + outputLen, " v%dstr,", getArg(pci, i));
		}
	}

	outputStmt[0] = '{';
	outputStmt[outputLen - 1] = '}';
	appendWeldStmt(wstate, outputStmt);
	free(outputStmt);

	weld_error_t e = weld_error_new();
	weld_conf_t conf = weld_conf_new();
	(void)dumpProgram; /* supress the unused warning */
#ifdef WELD_DEBUG
	dumpProgram(wstate, mb);
	weld_conf_set(conf, "weld.compile.dumpCode", "true");
	weld_conf_set(conf, "weld.compile.dumpCodeDir", "/tmp");
#endif
	weld_module_t m = weld_module_compile(wstate->program, conf, e);
	weld_conf_free(conf);
	free(wstate->program);
	free(wstate->groupDeps);
	free(wstate);
	if (weld_error_code(e)) {
		throw(MAL, "weld.run", PROGRAM_GENERAL ": %s", weld_error_message(e));
	}

	/* Prepare the input for Weld. We're building an array that has the layout of a struct */
	/* Max possible size is when we only have string bats: 2 ptrs for theap and tvheap and 4 lngs
	 * for batCount, hseqbase, stroffset and tvheap->size.
	 * The extra 10 * sizeof(double) are for the constants */
	char *inputStruct = malloc((pci->argc - pci->retc) * (2 * sizeof(void *) + 3 * sizeof(lng)) +
							   10 * sizeof(double));
	char *inputPtr = inputStruct;
	for (i = pci->retc + 1; i < pci->argc; i++) { /* skip wstate on pci->retc */
		int type = getArgType(mb, pci, i);
		if (isaBatType(type)) {
			bat bid = *getArgReference_bat(stk, pci, i);
			BAT *b = BATdescriptor(bid);
			if (b == NULL) throw(MAL, "weld.run", SQLSTATE(HY002) RUNTIME_OBJECT_MISSING);
			getOrSetStructMember(&inputPtr, TYPE_ptr, &b->theap.base, OP_SET);
			getOrSetStructMember(&inputPtr, TYPE_lng, &b->batCount, OP_SET);
			getOrSetStructMember(&inputPtr, TYPE_lng, &b->hseqbase, OP_SET);
			if (getBatType(type) == TYPE_str) {
				getOrSetStructMember(&inputPtr, TYPE_str, &b->tvheap->base, OP_SET);
				getOrSetStructMember(&inputPtr, TYPE_lng, &b->tvheap->size, OP_SET);
				lng offset = b->twidth <= 2 ? GDK_VAROFFSET : 0;
				getOrSetStructMember(&inputPtr, TYPE_lng, &offset, OP_SET);
			}
		} else {
			getOrSetStructMember(&inputPtr, type, getArgReference(stk, pci, i), OP_SET);
			if (type == TYPE_str) {
				long len = strlen(*getArgReference_str(stk, pci, i));
				getOrSetStructMember(&inputPtr, TYPE_lng, &len, OP_SET);
			}
		}
	}
	getOrSetStructMember(&inputPtr, TYPE_bte, &weldMinMaxInst.i8min, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_bte, &weldMinMaxInst.i8max, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_int, &weldMinMaxInst.i32min, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_int, &weldMinMaxInst.i32max, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_lng, &weldMinMaxInst.i64min, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_lng, &weldMinMaxInst.i64max, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_flt, &weldMinMaxInst.f32min, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_flt, &weldMinMaxInst.f32max, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_dbl, &weldMinMaxInst.f64min, OP_SET);
	getOrSetStructMember(&inputPtr, TYPE_dbl, &weldMinMaxInst.f64max, OP_SET);

	weld_value_t arg = weld_value_new(inputStruct);
	conf = weld_conf_new();
	weld_value_t result = weld_module_run(m, conf, arg, e);

	/* Retrieve the output */
	char *outputStruct = weld_value_data(result);
	for (i = 0; i < pci->retc; i++) {
		int type = getArgType(mb, pci, i);
		if (isaBatType(type)) {
			BAT *b = COLnew(0, getBatType(type), 0, TRANSIENT);
			getOrSetStructMember(&outputStruct, TYPE_ptr, &b->theap.base, OP_GET);
			getOrSetStructMember(&outputStruct, TYPE_lng, &b->batCount, OP_GET);
			if (b->batCount == 0)
				b->theap.base = NULL;
			b->batCapacity = b->batCount;
			b->theap.storage = STORE_CMEM;
			/* TODO check if the sorted props are important for the rest of the execution */
			b->tsorted = b->trevsorted = 0;
			if (getBatType(type) == TYPE_str) {
				char *base;
				long size;
				getOrSetStructMember(&outputStruct, TYPE_str, &base, OP_GET);
				getOrSetStructMember(&outputStruct, TYPE_lng, &size, OP_GET);
				/* Find the matching vheap from the input bats */
				for (j = pci->retc; j < pci->argc; j++) {
					int inputType = getArgType(mb, pci, j);
					if (isaBatType(inputType) && getBatType(inputType) == TYPE_str) {
						bat inid = *getArgReference_bat(stk, pci, j);
						BAT *in = BATdescriptor(inid);
						if (in == NULL) throw(MAL, "weld.run", SQLSTATE(HY002) RUNTIME_OBJECT_MISSING);
						if (in->tvheap->base == base) {
							BBPshare(in->tvheap->parentid);
							b->tvheap = in->tvheap;
							b->ttype = in->ttype;
							b->twidth = in->twidth;
							b->tshift = in->tshift;
							b->tvarsized = 1;
							break;
						}
					}
				}
			}
			b->theap.free = b->batCount << b->tshift;
			b->theap.size = b->batCount << b->tshift;
			BBPkeepref(b->batCacheid);
			*getArgReference_bat(stk, pci, i) = b->batCacheid;
		} else {
			/* TODO handle strings */
			getOrSetStructMember(&outputStruct, type, getArgReference(stk, pci, i), OP_GET);
		}
	}

	weld_error_free(e);
	weld_value_free(arg);
	/* TODO does not work as advertised in the doc. It will free our data buffers as well */
	//weld_value_free(result);
	weld_conf_free(conf);
	weld_module_free(m);
	free(inputStruct);

	return MAL_SUCCEED;
}

static str
WeldAggrUnary(MalBlkPtr mb, MalStkPtr stk, InstrPtr pci, str op, str malfunc)
{
	int ret = getArg(pci, 0); /* any_1 */
	int bid = getArg(pci, 1); /* bat[:any_1] */
	int sid;
	bat s;
	weldState *wstate;
	if (pci->argc == 4) {
		sid = getArg(pci, 2);						/* bat:[oid] */
		s = *getArgReference_bat(stk, pci, 2);		/* might have value */
		wstate = *getArgReference_ptr(stk, pci, 3); /* has value */
		if (!isaBatType(getArgType(mb, pci, 2))) {  /* nil_if_empty not implemented */
			throw(MAL, malfunc, PROGRAM_NYI);
		}
	} else {
		sid = -1;
		s = -1;
		wstate = *getArgReference_ptr(stk, pci, 2); /* has value */
	}
	str any_1 = getWeldType(getArgType(mb, pci, 0));
	char weldStmt[STR_SIZE_INC];
	if (sid != -1) {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, merger[%s, %s], |b: merger[%s, %s], i: i64, oid: i64|"
		"		merge(b, lookup(v%d, oid - v%dhseqbase))"
		"	)"
		");",
		ret, getWeldCandList(sid, s), any_1, op, any_1, op, bid, bid);
	} else {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (v%d, merger[%s, %s], |b: merger[%s, %s], i: i64, x: %s|"
		"		merge(b, x)"
		"	)"
		");",
		ret, bid, any_1, op, any_1, op, any_1);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldAggrSum(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldAggrUnary(mb, stk, pci, "+", "weld.aggrsum");
}

str
WeldAlgebraProjection(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;

	int ret = getArg(pci, 0);										   /* bat[:any_1] */
	int left = getArg(pci, 1);										   /* bat[:oid] */
	bat leftBat = *getArgReference_bat(stk, pci, 1);				   /* might have value */
	int right = getArg(pci, 2);										   /* bat[:any_1] */
	bat rightBat = *getArgReference_bat(stk, pci, 2);				   /* might have value */
	weldState *wstate = *getArgReference_ptr(stk, pci, pci->argc - 1); /* has value */
	char weldStmt[STR_SIZE_INC];
	BAT *rb = is_bat_nil(rightBat) ? NULL : BATdescriptor(rightBat);
	if (rb != NULL && BATtdense(rb)) {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[?], |b, i, oid|"
		"		merge(b, oid - v%dhseqbase + %ldL)"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, getWeldCandList(left, leftBat), right, rb->tseqbase, ret);
	} else {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[?], |b, i, oid|"
		"		merge(b, lookup(v%d, oid - v%dhseqbase))"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, getWeldCandList(left, leftBat), right, right, ret);
	}
	if (getBatType(getArgType(mb, pci, 0)) == TYPE_str) {
		/* any_1 = str */
		sprintf(weldStmt + strlen(weldStmt),
		"let v%dstr = v%dstr;"
		"let v%dstroffset = v%dstroffset;",
	   	ret, right, ret, right);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldSqlProjectDelta(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	/* For tpch queries we only do project(s, c) */
	return WeldAlgebraProjection(cntxt, mb, stk, pci);
}

str
WeldAlgebraSelect1(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;

	int ret = getArg(pci, 0);							   /* bat[:oid] */
	int bid = getArg(pci, 1);							   /* bat[:any_1] */
	int low = getArg(pci, 2);							   /* any_1 */
	int high = getArg(pci, 3);							   /* any_1 */
	int li = *getArgReference_bit(stk, pci, 4);			   /* has value */
	int hi = *getArgReference_bit(stk, pci, 5);			   /* has value */
	int anti = *getArgReference_bit(stk, pci, 6);		   /* has value */
	weldState *wstate = *getArgReference_ptr(stk, pci, 7); /* has value */

	char *lCmp, *op, *rCmp;
	char weldStmt[STR_SIZE_INC];

	/* Inspired from gdk_select.c */
	if (!anti) {
		op = "&&";
		if (!li)
			lCmp = "<";
		else
			lCmp = "<=";
		if (!hi)
			rCmp = ">";
		else
			rCmp = ">=";
	} else {
		op = "||";
		if (!li)
			lCmp = ">=";
		else
			lCmp = ">";
		if (!hi)
			rCmp = "<=";
		else
			rCmp = "<";
	}

	sprintf(weldStmt,
	"let v%d = result("
	"	for (v%d, appender[i64], |b: appender[i64], oid: i64, x|"
	"		if (v%d %s x    %s    v%d %s x,"
	"			merge(b, oid),"
	"			b"
	"		)"
	"	)"
	");"
	"let v%dhseqbase = 0L;",
	ret, bid, low, lCmp, op, high, rCmp, ret);
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldAlgebraSelect2(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;

	int ret = getArg(pci, 0);							   /* bat[:oid] */
	int bid = getArg(pci, 1);							   /* bat[:any_1] */
	int sid = getArg(pci, 2);							   /* bat[:oid] */
	bat s = *getArgReference_bat(stk, pci, 2);			   /* might have value */
	int low = getArg(pci, 3);							   /* any_1 */
	int high = getArg(pci, 4);							   /* any_1 */
	int li = *getArgReference_bit(stk, pci, 5);			   /* has value */
	int hi = *getArgReference_bit(stk, pci, 6);			   /* has value */
	int anti = *getArgReference_bit(stk, pci, 7);		   /* has value */
	weldState *wstate = *getArgReference_ptr(stk, pci, 8); /* has value */
	char *lCmp, *op, *rCmp;
	char x[STR_SIZE_INC], weldStmt[STR_SIZE_INC];

	/* Inspired from gdk_select.c */
	if (!anti) {
		op = "&&";
		if (!li)
			lCmp = "<";
		else
			lCmp = "<=";
		if (!hi)
			rCmp = ">";
		else
			rCmp = ">=";
	} else {
		op = "||";
		if (!li)
			lCmp = ">=";
		else
			lCmp = ">";
		if (!hi)
			rCmp = "<=";
		else
			rCmp = "<";
	}

	sprintf(x, "lookup(v%d, oid - v%dhseqbase)", bid, bid);
	sprintf(weldStmt,
	"let v%d = result("
	"	for (%s, appender[i64], |b: appender[i64], i: i64, oid: i64|"
	"		if (v%d %s %s    %s    v%d %s %s,"
	"			merge(b, oid),"
	"			b"
	"		)"
	"	)"
	");"
	"let v%dhseqbase = 0L;",
	ret, getWeldCandList(sid, s), low, lCmp, x, op, high, rCmp, x, ret);
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldAlgebraThetaselect1(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;

	int ret = getArg(pci, 0);							   /* bat[:oid] */
	int bid = getArg(pci, 1);							   /* bat[:any_1] */
	int val = getArg(pci, 2);							   /* any_1 */
	int valType = getArgType(mb, pci, 2);
	str op = *getArgReference_str(stk, pci, 3);			   /* has value */
	weldState *wstate = *getArgReference_ptr(stk, pci, 4); /* has value */
	char weldStmt[STR_SIZE_INC];
	if (valType == TYPE_str) {
		if (strcmp(op, "==") != 0) {
			throw(MAL, "weld.algebrathetaselect", PROGRAM_NYI": str thetaselect only supports ==");
		}
		sprintf(weldStmt,
		"let v%d = result("
		"	for (v%d, appender[i64], |b, i, x|"
		"		if (strslice(v%dstr, i64(x) + v%dstroffset) %s v%d,"
		"			merge(b, i + v%dhseqbase),"
		"			b"
		"		)"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, bid, bid, bid, op, val, bid, ret);
	} else {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (v%d, appender[i64], |b, i, x|"
		"		if (x %s v%d,"
		"			merge(b, i + v%dhseqbase),"
		"			b"
		"		)"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, bid, op, val, bid, ret);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldAlgebraThetaselect2(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;

	int ret = getArg(pci, 0);							   /* bat[:oid] */
	int bid = getArg(pci, 1);							   /* bat[:any_1] */
	int sid = getArg(pci, 2);							   /* bat[:oid] */
	bat s = *getArgReference_bat(stk, pci, 2);			   /* might have value */
	int val = getArg(pci, 3);							   /* any_1 */
	int valType = getArgType(mb, pci, 3);
	str op = *getArgReference_str(stk, pci, 4);			   /* has value */
	weldState *wstate = *getArgReference_ptr(stk, pci, 5); /* has value */
	char weldStmt[STR_SIZE_INC];
	if (valType == TYPE_str) {
		if (strcmp(op, "==") != 0) {
			throw(MAL, "weld.algebrathetaselect", PROGRAM_NYI": str thetaselect only supports ==");
		}
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[i64], |b, i, oid|"
		"		let offset = lookup(v%d, oid - v%dhseqbase);"
		"		if (strslice(v%dstr, i64(offset) + v%dstroffset) %s v%d,"
		"			merge(b, oid),"
		"			b"
		"		)"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, getWeldCandList(sid, s), bid, bid, bid, bid, op, val, ret);
	} else {
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[i64], |b: appender[i64], i: i64, oid: i64|"
		"		if (lookup(v%d, oid - v%dhseqbase) %s v%d,"
		"			merge(b, oid),"
		"			b"
		"		)"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, getWeldCandList(sid, s), bid, bid, op, val, ret);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

static str
WeldBatcalcBinary(MalBlkPtr mb, MalStkPtr stk, InstrPtr pci, str op, str malfunc)
{
	int ret = getArg(pci, 0);   /* bat[:any_1] */
	int left = getArg(pci, 1);  /* bat[:any_1] or any_1 */
	int right = getArg(pci, 2); /* bat[:any_1] or any_1 */
	int sid;
	bat s;
	weldState *wstate;
	if (pci->argc == 5) {
		sid = getArg(pci, 3);						/* bat[:oid] */
		s = *getArgReference_bat(stk, pci, 3);		/* might have value */
		wstate = *getArgReference_ptr(stk, pci, 4); /* has value */
	} else {
		sid = -1;
		s = -1;
		wstate = *getArgReference_ptr(stk, pci, 3); /* has value */
	}
	int leftType = getArgType(mb, pci, 1);
	int rightType = getArgType(mb, pci, 2);
	str any_1 = getWeldType(getBatType(getArgType(mb, pci, 0)));

	if (getBatType(leftType) != getBatType(rightType)) {
		throw(MAL, malfunc, PROGRAM_NYI);
	}

	char weldStmt[STR_SIZE_INC], *cast;
	if (getBatType(getArgType(mb, pci, 0)) == TYPE_bit) {
		cast = any_1;
	} else {
		cast = "";
	}

	if (sid != -1) {
		char leftStmt[STR_SIZE_INC];
		char rightStmt[STR_SIZE_INC];
		if (isaBatType(leftType)) {
			if (getBatType(leftType) == TYPE_str) {
				sprintf(leftStmt,
						"strslice(v%dstr, i64(lookup(v%d, oid - v%dhseqbase)) + v%dstroffset)",
						left, left, left, left);
			} else {
				sprintf(leftStmt, "lookup(v%d, oid - v%dhseqbase)", left, left);
			}
		} else {
			sprintf(leftStmt, "v%d", left);
		}
		if (isaBatType(rightType)) {
			if (getBatType(rightType) == TYPE_str) {
				sprintf(rightStmt,
						"strslice(v%dstr, i64(lookup(v%d, oid - v%dhseqbase)) + v%dstroffset)",
						right, right, right, right);
			} else {
				sprintf(rightStmt, "lookup(v%d, oid - v%dhseqbase)", right, right);
			}
		} else {
			sprintf(rightStmt, "v%d", right);
		}

		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[?], |b, i, oid|"
		"		merge(b, %s(%s %s %s))"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, getWeldCandList(sid, s), cast, leftStmt, op, rightStmt, ret);
	} else {
		char forStmt[64];
		char leftStmt[512], rightStmt[512];
		if (isaBatType(leftType) && isaBatType(rightType)) {
			sprintf(forStmt, "zip(v%d, v%d)", left, right);
			if (getBatType(leftType) == TYPE_str) {
				sprintf(leftStmt, "strslice(v%dstr, i64(x.$0) + v%dstroffset)", left, left);
				sprintf(rightStmt, "strslice(v%dstr, i64(x.$1) + v%dstroffset)", right, right);
			} else {
				sprintf(leftStmt, "x.$0");
				sprintf(rightStmt, "x.$1");
			}
		} else if (isaBatType(leftType)) {
			sprintf(forStmt, "v%d", left);
			if (getBatType(leftType) == TYPE_str) {
				sprintf(leftStmt, "strslice(v%dstr, i64(x) + v%dstroffset)", left, left);
			} else {
				sprintf(leftStmt, "x");
			}
			sprintf(rightStmt, "v%d", right);
		} else if (isaBatType(rightType)) {
			sprintf(forStmt, "v%d", right);
			sprintf(leftStmt, "v%d", left);
			if (getBatType(rightType) == TYPE_str) {
				sprintf(rightStmt, "strslice(v%dstr, i64(x) + v%dstroffset)", right, right);
			} else {
				sprintf(rightStmt, "x");
			}
		}
		sprintf(weldStmt,
		"let v%d = result("
		"	for (%s, appender[?], |b , i, x|"
		"		merge(b, %s(%s %s %s))"
		"	)"
		");"
		"let v%dhseqbase = 0L;",
		ret, forStmt, cast, leftStmt, op, rightStmt, ret);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldBatcalcADDsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "+", "weld.batcalcadd");
}

str
WeldBatcalcSUBsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "-", "weld.batcalcsub");
}

str
WeldBatcalcMULsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "*", "weld.batcalcmul");
}

str
WeldBatcalcDIVsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "/", "weld.batcalcdiv");
}

str
WeldBatcalcLTsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "<", "weld.batcalclt");
}

str
WeldBatcalcLEsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "<=", "weld.batcalcle");
}
str
WeldBatcalcEQsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "==", "weld.batcalceq");
}

str
WeldBatcalcGTsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, ">", "weld.batcalcgt");
}

str
WeldBatcalcGEsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, ">=", "weld.batcalcge");
}

str
WeldBatcalcNEsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "!=", "weld.batcalcne");
}

str
WeldBatcalcMODsignal(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	return WeldBatcalcBinary(mb, stk, pci, "%", "weld.batcalcmod");
}

/* Ignore the existing groups and instead use all the columns up to this point to
 * generate the new group ids. Weld will remove the unnecessary computations. e.g.:
 * g1, e1, h1 = group.group(col1)  -> for(zip(col1), dictmerger[ty1, i64, min]...
 * g2, e2, h2 = group.grou(col2, g1) -> for(zip(col2, col1), dictmerger[{ty1, ty2}, i64, min]...
 */
str
WeldGroup(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	int groups = getArg(pci, 0);  /* bat[:oid] */
	int extents = getArg(pci, 1); /* bat[:oid] */
	int histo = getArg(pci, 2);   /* bat[:lng] */
	weldState *wstate;
	if (pci->argc == 6) {
		wstate = *getArgReference_ptr(stk, pci, 5); /* has value */
	} else {
		wstate = *getArgReference_ptr(stk, pci, 4); /* has value */
	}

	/* Build zip(col1, col2, ...) */
	wstate->groupDeps[groups] = pci;
	InstrPtr dep = pci;
	int count = 0, colArgNo = 3;
	char zipStmt[STR_SIZE_INC] = {'\0'};
	char dictTypeStmt[STR_SIZE_INC] = {'\0'};
	char dictKeyStmt[STR_SIZE_INC] = {'\0'};
	char structMember[64];
	while (dep != NULL) {
		int col = getArg(dep, colArgNo);
		int colType = getBatType(getArgType(mb, dep, colArgNo));
		if (dep->argc == 6) {
			int oldGrps = getArg(dep, 4);
			if (wstate->groupDeps[oldGrps] != NULL) {
				/* the previous groups were computed in this Weld program so we can use the column */
				dep = wstate->groupDeps[oldGrps];
			} else if (colArgNo == 3) {
				/* the previous groups were not computed in this Weld program so we need to use them */
				colArgNo = 4;
			} else {
				/* currently using the precomputed group ids, this is the last step */
				dep = NULL;
			}
		} else {
			/* last column in the grouping */
			dep = NULL;
		}
		sprintf(zipStmt + strlen(zipStmt), "v%d,", col);
		sprintf(dictTypeStmt + strlen(dictTypeStmt), " %s,", getWeldType(colType));
		if (count > 0 || dep != NULL) {
			sprintf(structMember, ".$%d", count);
		} else {
			structMember[0] = '\0';
		}
		if (getBatType(colType) == TYPE_str) {
			sprintf(dictKeyStmt + strlen(dictKeyStmt),
					" strslice(v%dstr, i64(n%s) + v%dstroffset),", col, structMember, col);
		} else {
			sprintf(dictKeyStmt + strlen(dictKeyStmt), " n%s,", structMember);
		}
		++count;
	}
	/* Replace the last comma */
	zipStmt[strlen(zipStmt) - 1] = '\0';
	if (count == 1) {
		dictTypeStmt[strlen(dictTypeStmt) - 1] = '\0';
		dictKeyStmt[strlen(dictKeyStmt) -1] = '\0';
	} else {
		dictTypeStmt[0] = '{';
		dictTypeStmt[strlen(dictTypeStmt) - 1] = '}';
		dictKeyStmt[0] = '{';
		dictKeyStmt[strlen(dictKeyStmt) -1] = '}';
	}

	char weldStmt[STR_SIZE_INC * 2];
	sprintf(weldStmt,
	"let groupHash = result("
	"	for(zip(%s), dictmerger[%s, i64, min], |b, i, n|"
	"		merge(b, {%s, i})"
	"	)"
	");"
	"let groupHashVec = tovec(groupHash);"
	"let groupIdsDict = result("
	"	for(groupHashVec, dictmerger[%s, i64, min], |b, i, n|"
	"		merge(b, {n.$0, i})"
	"	)"
	");"
	"let empty = result("
	"	for(rangeiter(0L, len(groupHashVec), 1L), appender[i64], |b, i, n|"
	"		merge(b, 0L)"
	"	)"
	");"
	"let ids = for(zip(%s), appender[i64], |b, i, n|"
	"	let groupId = lookup(groupIdsDict, %s);"
	"	merge(b, groupId)"
	");"
	"let counts = for(zip(%s), vecmerger[i64, +](empty), |b, i, n|"
	"	let groupId = lookup(groupIdsDict, %s);"
	"	merge(b, {groupId, 1L})"
	");"
	"let v%d = result(ids);"
	"let v%dhseqbase = 0;"
	"let v%d = result(counts);"
	"let v%dhseqbase = 0;"
	"let v%d = result("
	"	for(groupHashVec, vecmerger[i64, +](empty), |b, i, n|"
	"		merge(b, {i, lookup(groupHash, n.$0)})"
	"	)"
	");"
	"let v%dhseqbase = 0;",
	zipStmt, dictTypeStmt, dictKeyStmt, dictTypeStmt, zipStmt, dictKeyStmt, zipStmt, dictKeyStmt, groups, groups, histo, histo,
	extents, extents);
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

static str
WeldAggrSub(MalBlkPtr mb, MalStkPtr stk, InstrPtr pci, str op, str malfunc)
{
	int ret = getArg(pci, 0); /* any_1 */
	int bid = getArg(pci, 1); /* bat[:any_1] */
	int gid = getArg(pci, 2); /* bat[:oid] */
	int eid = getArg(pci, 3); /* bat[:oid] */
	int sid = getArg(pci, 4); /* bat[:oid] ? */
	int retType = getBatType(getArgType(mb, pci, 0));
	int bidType = getBatType(getArgType(mb, pci, 1));
	int sidType = getArgType(mb, pci, 4);
	weldState *wstate = *getArgReference_ptr(stk, pci, pci->argc - 1); /* has value */
	/* TODO Weld doesn't yet accept mismatching types for binary ops */
	if (retType != bidType) {
		throw(MAL, malfunc, PROGRAM_NYI);
	}

	char identValue[128];
	if (strcmp(op, "+") == 0)
		sprintf(identValue, "%s(0c)", getWeldType(retType));
	else if (strcmp(op, "*") == 0)
		sprintf(identValue, "%s(1c)", getWeldType(retType));
	else if (strcmp(op, "min") == 0)
		sprintf(identValue, "%sMAX", getWeldType(retType));
	else if (strcmp(op, "max") == 0)
		sprintf(identValue, "%sMIN", getWeldType(retType));

	char weldStmt[STR_SIZE_INC];
	sprintf(weldStmt,
	"let empty = result("
	"	for(rangeiter(0L, len(v%d), 1L), appender[%s], |b, i, x|"
	"		merge(b, %s)"
	"	)"
	");",
	eid, getWeldType(retType), identValue);

	if (isaBatType(sidType)) {
		bat s = *getArgReference_bat(stk, pci, 4);		/* might have value */
		sprintf(weldStmt + strlen(weldStmt),
		"let v%d = result("
		"	for(%s, vecmerger[%s, %s](empty), |b, i, oid|"
		"		let groupId = lookup(v%d, oid - v%dhseqbase);"
		"		let val = lookup(v%d, oid - v%dhseqbase);"
		"		merge(b, {groupId, val})"
		"	)"
		");"
		"let v%dhseqbase = 0;",
		ret, getWeldCandList(sid, s), getWeldType(retType), op, gid, gid, bid, bid, ret);
	} else {
		sprintf(weldStmt + strlen(weldStmt),
		"let v%d = result("
		"	for(zip(v%d, v%d), vecmerger[%s, %s](empty), |b, i, x|"
		"		merge(b, {x.$0, x.$1})"
		"	)"
		");"
		"let v%dhseqbase = 0;",
		ret, gid, bid, getWeldType(retType), op, ret);
	}
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldAggrSubSum(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	return WeldAggrSub(mb, stk, pci, "+", "weld.aggrsubsum");
}

str
WeldAggrSubProd(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	return WeldAggrSub(mb, stk, pci, "*", "weld.aggrsubprod");
}

str
WeldAggrSubMin(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	return WeldAggrSub(mb, stk, pci, "min", "weld.aggrsubmin");
}

str
WeldAggrSubMax(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void)cntxt;
	return WeldAggrSub(mb, stk, pci, "max", "weld.aggrsubmax");
}

str
WeldBatMtimeYear(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;
	int ret = getArg(pci, 0); /* bat[:int] */
	int bid = getArg(pci, 1); /* bat[:date] */
	weldState *wstate = *getArgReference_ptr(stk, pci, pci->argc - 1); /* has value */
	char weldStmt[STR_SIZE_INC];
	/* Only works for days >= 0. Logic taken from mtime.c */
	sprintf(weldStmt,
	"let v%d = result("
	"	for(v%d, appender[i32], |b, i, x|"
	"		let year = x / 365;"
	"		let leapyears = (year - 1) / 4 + (year - 1) / 400 - (year - 1) / 100 + 1;"
	"		let day = (x - year * 365) - leapyears;"
	"		merge(b,"
	"			iterate({day, year}, |p|"
	"				let year = p.$1 - 1;"
	"				let isLeap = year %% 4 == 0 && (year %% 100 != 0 || year %% 400 == 0);"
	"				{{p.$0 + if(isLeap, 366, 365), year}, p.$0 < 0}).$1 + 1)"
	"	)"
	");"
	"let v%dhseqbase = 0L;",
	ret, bid, ret);
	appendWeldStmt(wstate, weldStmt);
	return MAL_SUCCEED;
}

str
WeldBatMergeCand(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;
	int ret = getArg(pci, 0);										   /* bat[:oid] */
	int left = getArg(pci, 1);										   /* bat[:oid] */
	bat leftBat = *getArgReference_bat(stk, pci, 1);				   /* might have value */
	int right = getArg(pci, 2);										   /* bat[:oid] */
	bat rightBat = *getArgReference_bat(stk, pci, 2);				   /* might have value */
	weldState *wstate = *getArgReference_ptr(stk, pci, pci->argc - 1); /* has value */

	char *leftWeld = strdup(getWeldCandListFull(left, leftBat));
	char *rightWeld = strdup(getWeldCandListFull(right, rightBat));
	char weldStmt[STR_SIZE_INC];
	sprintf(weldStmt,
	"let left = %s;"
	"let right = %s;"
	"let iter_res = if(len(left) > 0L && len(right) > 0L,"
	"	iterate({0L, 0L, appender[i64]}, |x|"
	"		let leftIdx = x.$0;"
	"		let rightIdx = x.$1;"
	"		let b = x.$2;"
	"		let leftVal = lookup(left, leftIdx);"
	"		let rightVal = lookup(right, rightIdx);"
	"		let output = "
	"		if(leftVal < rightVal,"
	"			{leftIdx + 1L, rightIdx, merge(b, leftVal)},"
   	"			if (leftVal > rightVal,"
	"				{leftIdx, rightIdx + 1L, merge(b, rightVal)},"
	"				{leftIdx + 1L, rightIdx + 1L, merge(b, leftVal)}"
	"			)"
	"		);"	
	"		{output, output.$0 < len(left) && output.$1 < len(right)}),"
	"	{0L, 0L, appender[i64]});"
	"let res = iter_res.$2;"
	"let res = for(rangeiter(iter_res.$0, len(left), 1L), res, |b, i, x| merge(b, lookup(left, x)));"
	"let res = for(rangeiter(iter_res.$1, len(right), 1L), res, |b, i, x| merge(b, lookup(right, x)));"
	"let v%d = result(res);"
	"let v%dhseqbase = 0L;",
	leftWeld, rightWeld, ret, ret);
	appendWeldStmt(wstate, weldStmt);
	free(leftWeld);
	free(rightWeld);
	return MAL_SUCCEED;
}

str
WeldLanguagePass(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	(void) cntxt;
	(void) mb;
	(void) stk;
	(void) pci;
	return MAL_SUCCEED;
}
