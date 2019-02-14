/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "wlc", "\nmodule wlc;\n\npattern init()\naddress WLCinitCmd\ncomment \"Test for running as master\";\n\npattern master()\naddress WLCmaster\ncomment \"Activate the workload-capture-replay process\";\n\npattern master(path:str)\naddress WLCmaster\ncomment \"Activate the workload-capture-replay process. Use a different location for the logs.\";\n\npattern stopmaster()\naddress WLCstopmaster\ncomment \"Stop capturing the logs\";\n\npattern setmasterbeat(duration:int)\naddress WLCsetmasterbeat\ncomment \"Maximal delay for transaction log flushing\";\n\npattern getmasterbeat(duration:int):str\naddress WLCgetmasterbeat\ncomment \"Maximal delay for transaction log flushing\";\n\npattern getmasterclock():str\naddress WLCgetmasterclock\ncomment \"Timestamp of last update transaction\";\n\npattern getmastertick():lng\naddress WLCgetmastertick\ncomment \"Transaction identifier of the last committed transaction\";\n\npattern rollback()\naddress WLCrollbackCmd\ncomment \"Mark the end of the work unit\";\n\npattern commit()\naddress WLCcommitCmd\ncomment \"Mark the end of the work unit\";\n\npattern query(q:str)\naddress WLCquery\ncomment \"Keep the queries for replay.\";\n\npattern catalog(q:str)\naddress WLCcatalog\ncomment \"Keep the catalog changing queries for replay. \";\n\npattern action(q:str)\naddress WLCaction\ncomment \"Keep the database changing queries for replay. \";\n\npattern append(sname:str, tname:str, cname:str, ins:any):int\naddress WLCappend\ncomment \"Keep the insertions in the workload-capture-replay list\";\n\npattern update(sname:str, tname:str, cname:str, tid:any, val:any):int\naddress WLCupdate\ncomment \"Keep the update in the workload-capture-replay list\";\n\npattern delete(sname:str, tname:str, b:any):int\naddress WLCdelete\ncomment \"Keep the deletions in the workload-capture-replay list\";\n\npattern clear_table(sname:str, tname:str):int\naddress WLCclear_table\ncomment \"Keep the deletions in the workload-capture-replay list\";\n\npattern commit()\naddress WLCcommitCmd\ncomment \"Commit the workload-capture-replay record\";\n\npattern rollback()\naddress WLCcommitCmd\ncomment \"Rollback the workload-capture-replay record\";\n\npattern create_seq( sname:str, seqname:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation create_seq\";\n\npattern alter_seq( sname:str, seqname:str, val:lng)\naddress WLCgeneric\ncomment \"Catalog operation alter_seq\";\n\npattern drop_seq( sname:str, nme:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_seq\";\n\npattern create_schema(sname:str, auth:str, ifnotexists:int, action:int)\naddress WLCgeneric\ncomment \"Catalog operation create_schema\";\n\npattern drop_schema( sname:str, s:str, ifexists:int, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_schema\";\n\npattern create_table(sname:str, tname:str, temp:int)\naddress WLCgeneric\ncomment \"Catalog operation create_table\";\n\npattern create_view(sname:str, tname:str, temp:int)\naddress WLCgeneric\ncomment \"Catalog operation create_view\";\n\npattern drop_table( sname:str, name:str, action:int, ifexists:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_table\";\n\npattern drop_view( sname:str, name:str, action:int, ifexists:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_view\";\n\npattern drop_constraint( sname:str, name:str, action:int, ifexists:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_constraint\";\n\npattern alter_table( sname:str, tname:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_table\";\n\npattern create_type( sname:str, nme:str, impl:str)\naddress WLCgeneric\ncomment \"Catalog operation create_type\";\n\npattern drop_type( sname:str, nme:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_type\";\n\npattern grant_roles( sname:str, auth:str, grantor:int, admin:int)\naddress WLCgeneric\ncomment \"Catalog operation grant_roles\";\n\npattern revoke_roles( sname:str, auth:str, grantor:int, admin:int)\naddress WLCgeneric\ncomment \"Catalog operation revoke_roles\";\n\npattern grant( sname:str, tbl:str, grantee:str, privs:int, cname:str, gr:int, grantor:int)\naddress WLCgeneric\ncomment \"Catalog operation grant\";\n\npattern revoke ( sname:str, tbl:str, grantee:str, privs:int, cname:str,grant:int, grantor:int)\naddress WLCgeneric\ncomment \"Catalog operation revoke\";\n\npattern grant_function( sname:str, fcnid:int, grantee:str, privs:int, grant:int, grantor:int)\naddress WLCgeneric\ncomment \"Catalog operation grant_function\";\n\npattern revoke_function( sname:str, fcnid:int, grantee:str, privs:int, grant:int, grantor:int)\naddress WLCgeneric\ncomment \"Catalog operation revoke_function\";\n\npattern create_user( sname:str, passwrd:str, enc:int, schema:str, fullname:str)\naddress WLCgeneric\ncomment \"Catalog operation create_user\";\n\npattern drop_user(sname:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_user\";\n\npattern drop_user(sname:str, auth:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_user\";\n\npattern alter_user( sname:str, passwrd:str, enc:int, schema:str, oldpasswrd:str)\naddress WLCgeneric\ncomment \"Catalog operation alter_user\";\n\npattern rename_user( sname:str, newnme:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation rename_user\";\n\npattern create_role(sname:str,role:str,grator:int)\naddress WLCgeneric\ncomment \"Catalog operation create_role\";\n\npattern drop_role( auth:str, role:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_role\";\npattern drop_role( role:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_role\";\n\npattern drop_index( sname:str, iname:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_index\";\n\npattern drop_function( sname:str, fname:str, fid:int, type:int, action:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_function\";\n\npattern create_function( sname:str, fname:str)\naddress WLCgeneric\ncomment \"Catalog operation create_function\";\n\npattern create_trigger( sname:str, tname:str, triggername:str, time:int, orientation:int, event:int, old:str, new:str, cond:str, qry:str)\naddress WLCgeneric\ncomment \"Catalog operation create_trigger\";\n\npattern drop_trigger(sname:str, nme:str, ifexists:int)\naddress WLCgeneric\ncomment \"Catalog operation drop_trigger\";\n\npattern alter_add_table( sname:str, mtnme:str, psnme:str, ptnme:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_add_table\";\n\npattern alter_del_table( sname:str, mtnme:str, psnme:str, ptnme:str, action:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_del_table\";\n\npattern alter_set_table( sname:str, tnme:str, access:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_set_table\";\n\npattern alter_add_range_partition( sname:str, mtnme:str, psnme:str, ptnme:str, min:str, max:str, nills:int, update:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_add_range_partition\";\n\npattern comment_on(objid:int, remark:str)\naddress WLCgeneric\ncomment \"Catalog operation comment_on\";\n\npattern rename_schema(sname:str, newnme:str)\naddress WLCgeneric\ncomment \"Catalog operation rename_schema\";\n\npattern rename_table(sname:str, tname:str, newnme:str)\naddress WLCgeneric\ncomment \"Catalog operation rename_table\";\n\npattern rename_column(sname:str, tname:str, cname:str, newnme:str)\naddress WLCgeneric\ncomment \"Catalog operation rename_column\";\n\npattern transaction_release(chain:int,name:str):void\naddress WLCgeneric\ncomment \"A transaction statement (type can be commit,release,rollback or start)\";\n\npattern transaction_commit(chain:int,name:str):void\naddress WLCgeneric\ncomment \"A transaction statement (type can be commit,release,rollback or start)\";\n\npattern transaction_rollback(chain:int,name:str):void\naddress WLCgeneric\ncomment \"A transaction statement (type can be commit,release,rollback or start)\";\n\npattern transaction_begin(chain:int,name:str):void\naddress WLCgeneric\ncomment \"A transaction statement (type can be commit,release,rollback or start)\";\n\nunsafe pattern transaction()\naddress WLCgeneric\ncomment \"Start an autocommit transaction\";\n\npattern alter_add_value_partition( sname:str, mtnme:str, psnme:str, ptnme:str, nills:int, update:int)\naddress WLCgeneric\ncomment \"Catalog operation alter_add_value_partition\";\n\npattern alter_add_value_partition( sname:str, mtnme:str, psnme:str, ptnme:str, nills:int, update:int, arg:str...)\naddress WLCgeneric\ncomment \"Catalog operation alter_add_value_partition\";" }, 
