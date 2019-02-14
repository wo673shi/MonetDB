/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "sqlcatalog", "\nmodule sqlcatalog;\n\npattern create_seq( sname:str, seqname:str, seq:ptr, action:int)\naddress SQLcreate_seq \ncomment \"Catalog operation create_seq\";\n\npattern alter_seq( sname:str, seqname:str, seq:ptr, val:lng) \naddress SQLalter_seq \ncomment \"Catalog operation alter_seq\";\n\npattern drop_seq( sname:str, nme:str, action:int) \naddress SQLdrop_seq \ncomment \"Catalog operation drop_seq\";\n\npattern create_schema(sname:str, auth:str, ifnotexists:int, action:int)\naddress SQLcreate_schema \ncomment \"Catalog operation create_schema\";\n\npattern drop_schema( sname:str, s:str, ifexists:int, action:int)\naddress SQLdrop_schema \ncomment \"Catalog operation drop_schema\";\n\npattern create_table(sname:str, tname:str, tbl:ptr, temp:int) \naddress SQLcreate_table \ncomment \"Catalog operation create_table\";\n\npattern create_view(sname:str, vname:str, tbl:ptr, temp:int) \naddress SQLcreate_view \ncomment \"Catalog operation create_view\";\n\npattern drop_table( sname:str, name:str, action:int, ifexists:int)\naddress SQLdrop_table \ncomment \"Catalog operation drop_table\";\n\npattern drop_view( sname:str, name:str, action:int, ifexists:int)\naddress SQLdrop_view \ncomment \"Catalog operation drop_view\";\n\npattern drop_constraint( sname:str, name:str, action:int, ifexists:int)\naddress SQLdrop_constraint \ncomment \"Catalog operation drop_constraint\";\n\npattern alter_table( sname:str, tname:str, tbl:ptr, action:int) \naddress SQLalter_table \ncomment \"Catalog operation alter_table\";\n\npattern create_type( sname:str, nme:str, impl:str) \naddress SQLcreate_type \ncomment \"Catalog operation create_type\";\n\npattern drop_type( sname:str, nme:str, action:int) \naddress SQLdrop_type \ncomment \"Catalog operation drop_type\";\n\npattern grant_roles( sname:str, auth:str, grantor:int, admin:int) \naddress SQLgrant_roles \ncomment \"Catalog operation grant_roles\";\n\npattern revoke_roles( sname:str, auth:str, grantor:int, admin:int) \naddress SQLrevoke_roles \ncomment \"Catalog operation revoke_roles\";\n\npattern grant( sname:str, tbl:str, grantee:str, privs:int, cname:str, gr:int, grantor:int) \naddress SQLgrant \ncomment \"Catalog operation grant\";\n\npattern revoke ( sname:str, tbl:str, grantee:str, privs:int, cname:str,grant:int, grantor:int) \naddress SQLrevoke \ncomment \"Catalog operation revoke\";\n\npattern grant_function( sname:str, fcnid:int, grantee:str, privs:int, grant:int, grantor:int) \naddress SQLgrant_function \ncomment \"Catalog operation grant_function\";\n\npattern revoke_function( sname:str, fcnid:int, grantee:str, privs:int, grant:int, grantor:int) \naddress SQLrevoke_function \ncomment \"Catalog operation revoke_function\";\n\npattern create_user( sname:str, passwrd:str, enc:int, schema:str, fullname:str) \naddress SQLcreate_user \ncomment \"Catalog operation create_user\";\n\npattern drop_user(sname:str, action:int) \naddress SQLdrop_user \ncomment \"Catalog operation drop_user\";\n\npattern drop_user(sname:str, auth:str, action:int) \naddress SQLdrop_user \ncomment \"Catalog operation drop_user\";\n\n\npattern alter_user( sname:str, passwrd:str, enc:int, schema:str, oldpasswrd:str) \naddress SQLalter_user \ncomment \"Catalog operation alter_user\";\n\npattern rename_user( sname:str, newnme:str, action:int) \naddress SQLrename_user \ncomment \"Catalog operation rename_user\";\n\npattern create_role(sname:str,role:str,grator:int) \naddress SQLcreate_role \ncomment \"Catalog operation create_role\";\n\npattern drop_role( auth:str, role:str, action:int) \naddress SQLdrop_role \ncomment \"Catalog operation drop_role\";\npattern drop_role( role:str, action:int) \naddress SQLdrop_role \ncomment \"Catalog operation drop_role\";\n\npattern drop_index( sname:str, iname:str, action:int) \naddress SQLdrop_index \ncomment \"Catalog operation drop_index\";\n\npattern drop_function( sname:str, fname:str, fid:int, type:int, action:int)\naddress SQLdrop_function \ncomment \"Catalog operation drop_function\";\n\npattern create_function( sname:str, fname:str, fcn:ptr) \naddress SQLcreate_function \ncomment \"Catalog operation create_function\";\n\npattern create_trigger( sname:str, tname:str, triggername:str, time:int, orientation:int, event:int, old:str, new:str, cond:str, qry:str) \naddress SQLcreate_trigger \ncomment \"Catalog operation create_trigger\";\n\npattern drop_trigger(sname:str, nme:str, ifexists:int)\naddress SQLdrop_trigger \ncomment \"Catalog operation drop_trigger\";\n\npattern alter_add_table( sname:str, mtnme:str, psnme:str, ptnme:str, action:int) \naddress SQLalter_add_table \ncomment \"Catalog operation alter_add_table\";\n\npattern alter_del_table( sname:str, mtnme:str, psnme:str, ptnme:str, action:int) \naddress SQLalter_del_table \ncomment \"Catalog operation alter_del_table\";\n\npattern alter_set_table( sname:str, tnme:str, access:int) \naddress SQLalter_set_table \ncomment \"Catalog operation alter_set_table\";\n\npattern alter_add_range_partition( sname:str, mtnme:str, psnme:str, ptnme:str, min:any_1, max:any_1, nills:int, update:int)\naddress SQLalter_add_range_partition\ncomment \"Catalog operation alter_add_range_partition\";\n\npattern alter_add_value_partition( sname:str, mtnme:str, psnme:str, ptnme:str, nills:int, update:int)\naddress SQLalter_add_value_partition\ncomment \"Catalog operation alter_add_value_partition\";\n\npattern alter_add_value_partition( sname:str, mtnme:str, psnme:str, ptnme:str, nills:int, update:int, arg:any...)\naddress SQLalter_add_value_partition\ncomment \"Catalog operation alter_add_value_partition\";\n\npattern comment_on(objid:int, remark:str)\naddress SQLcomment_on\ncomment \"Catalog operation comment_on\";\n\npattern rename_schema(sname:str, newnme:str)\naddress SQLrename_schema\ncomment \"Catalog operation rename_schema\";\n\npattern rename_table(sname:str, tname:str, newnme:str)\naddress SQLrename_table\ncomment \"Catalog operation rename_table\";\n\npattern rename_column(sname:str, tname:str, cname:str, newnme:str)\naddress SQLrename_column\ncomment \"Catalog operation rename_column\";" }, 
