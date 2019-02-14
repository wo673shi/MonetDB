/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "mal_mapi", "\nmodule mapi;\n\ncommand listen():int\naddress SERVERlisten_default\ncomment \"Start a Mapi server with the default settings.\";\ncommand listen(port:int):int\naddress SERVERlisten_port\ncomment \"Start a Mapi listener on the port given.\";\ncommand listen(unixsocket:str):int\naddress SERVERlisten_usock\ncomment \"Start a Mapi listener on the unix socket file given.\";\n\ncommand stop():void\naddress SERVERstop\ncomment \"Terminate connection listeners.\";\n\ncommand suspend():void\naddress SERVERsuspend\ncomment \"Suspend accepting connections.\";\n\ncommand resume():void\naddress SERVERresume\ncomment \"Resume connection listeners.\";\n\ncommand malclient(in:streams, out:streams):void\naddress SERVERclient\ncomment \"Start a Mapi client for a particular stream pair.\";\n\n\ncommand trace(mid:int,flag:int):void\naddress SERVERtrace\ncomment \"Toggle the Mapi library debug tracer.\";\n\npattern reconnect(host:str, port:int, usr:str, passwd:str,lang:str):int\naddress SERVERreconnectWithoutAlias\ncomment \"Re-establish connection with a remote mserver.\";\n\npattern reconnect(host:str, port:int, db_alias:str, usr:str, passwd:str,lang:str):int\naddress SERVERreconnectAlias\ncomment \"Re-establish connection with a remote mserver.\";\n\ncommand reconnect(mid:int):void\naddress SERVERreconnect\ncomment \"Re-establish a connection.\";\n\npattern connect(host:str, port:int, usr:str, passwd:str,lang:str):int\naddress SERVERconnect\ncomment \"Establish connection with a remote mserver.\";\n\ncommand disconnect(dbalias:str):int\naddress SERVERdisconnectWithAlias\ncomment \"Close connection with a remote Mserver.\";\n\ncommand disconnect():int\naddress SERVERdisconnectALL\ncomment \"Close connections with all remote Mserver.\";\n\ncommand setAlias(key:int,dbalias:str)\naddress SERVERsetAlias\ncomment \"Give the channel a logical name.\";\n\ncommand lookup(dbalias:str):int\naddress SERVERlookup\ncomment \"Retrieve the connection identifier.\";\n\ncommand disconnect(mid:int):void\naddress SERVERdisconnect\ncomment \"Terminate the session.\";\n\ncommand destroy(mid:int):void\naddress SERVERdestroy\ncomment \"Destroy the handle for an Mserver.\";\n\ncommand ping(mid:int):int\naddress SERVERping\ncomment \"Test availability of an Mserver.\";\n\ncommand query(mid:int, qry:str):int\naddress SERVERquery\ncomment \"Send the query for execution\";\n\ncommand query_handle(mid:int, qry:str):int\naddress SERVERquery_handle\ncomment \"Send the query for execution.\";\n\npattern query_array(mid:int, qry:str, arg:str...):int\naddress SERVERquery_array\ncomment \"Send the query for execution replacing '?' by arguments.\";\n\ncommand prepare(mid:int, qry:str):int\naddress SERVERprepare\ncomment \"Prepare a query for execution.\";\n\ncommand finish(hdl:int):int\naddress SERVERfinish\ncomment \"Remove all remaining answers.\";\n\ncommand get_field_count(hdl:int):int\naddress SERVERget_field_count\ncomment \"Return number of fields.\";\n\ncommand get_row_count(hdl:int):lng\naddress SERVERget_row_count\ncomment \"Return number of rows.\";\n\ncommand rows_affected(hdl:int):lng\naddress SERVERrows_affected\ncomment \"Return number of affected rows.\";\n\ncommand fetch_row(hdl:int):int\naddress SERVERfetch_row\ncomment \"Retrieve the next row for analysis.\";\n\ncommand fetch_all_rows(hdl:int):lng\naddress SERVERfetch_all_rows\ncomment \"Retrieve all rows into the cache.\";\n\ncommand fetch_field(hdl:int,fnr:int):str\naddress SERVERfetch_field_str\ncomment \"Retrieve a single field.\";\n\ncommand fetch_field(hdl:int,fnr:int):int\naddress SERVERfetch_field_int\ncomment \"Retrieve a single int field.\";\n\ncommand fetch_field(hdl:int,fnr:int):lng\naddress SERVERfetch_field_lng\ncomment \"Retrieve a single lng field.\";\n\ncommand fetch_field(hdl:int,fnr:int):sht\naddress SERVERfetch_field_sht\ncomment \"Retrieve a single sht field.\";\n\ncommand fetch_field(hdl:int,fnr:int):void\naddress SERVERfetch_field_void\ncomment \"Retrieve a single void field.\";\n\ncommand fetch_field(hdl:int,fnr:int):oid\naddress SERVERfetch_field_oid\ncomment \"Retrieve a single void field.\";\n\ncommand fetch_field(hdl:int,fnr:int):bte\naddress SERVERfetch_field_bte\ncomment \"Retrieve a single bte field.\";\n\ncommand fetch_field_array(hdl:int):bat[:str]\naddress SERVERfetch_field_bat\ncomment \"Retrieve all fields for a row.\";\n\ncommand fetch_line(hdl:int):str\naddress SERVERfetch_line\ncomment \"Retrieve a complete line.\";\n\ncommand fetch_reset(hdl:int):int\naddress SERVERfetch_reset\ncomment \"Reset the cache read line.\";\n\ncommand next_result(hdl:int):int\naddress SERVERnext_result\ncomment \"Go to next result set.\";\n\ncommand error(mid:int):int\naddress SERVERerror\ncomment \"Check for an error in the communication.\";\n\ncommand getError(mid:int):str\naddress SERVERgetError\ncomment \"Get error message.\";\n\ncommand explain(mid:int):str\naddress SERVERexplain\ncomment \"Turn the error seen into a string.\";\n\npattern put(mid:int, nme:str, val:any_1):void\naddress SERVERput\ncomment \"Send a value to a remote site.\";\n\npattern put(nme:str, val:any_1):str\naddress SERVERputLocal\ncomment \"Prepare sending a value to a remote site.\";\n\npattern rpc(key:int,qry:str...):any\naddress SERVERmapi_rpc_single_row\ncomment \"Send a simple query for execution and fetch result.\";\n\npattern rpc(key:int,qry:str):bat[:any_2]\naddress SERVERmapi_rpc_bat;\n\ncommand rpc(key:int,qry:str):int\naddress SERVERquery\ncomment \"Send a simple query for execution.\";\n\npattern bind(key:int,rschema:str,rtable:str,rcolumn:str,i:int):bat[:any_2]\naddress SERVERbindBAT\ncomment \"Bind a remote variable to a local one.\";\n\npattern bind(key:int,rschema:str,rtable:str,i:int):bat[:any_2]\naddress SERVERbindBAT\ncomment \"Bind a remote variable to a local one.\";\n\npattern bind(key:int,remoteName:str):bat[:any_2]\naddress SERVERbindBAT\ncomment \"Bind a remote variable to a local one.\";\n\n\nmapi.listen();" }, 
