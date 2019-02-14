/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "identifier", "\natom identifier:str;\n\ncommand fromstr()\naddress IDfromString\ncomment \"Convert a string to an identifier without any check\";\n\ncommand tostr()\naddress IDtoString\ncomment \"Convert identifier to string equivalent\";\n\ncommand identifier(s:str):identifier\naddress IDentifier\ncomment \"Cast a string to an identifer \";\n\ncommand prelude():void\naddress IDprelude\ncomment \"Initialize the module\";\n\nidentifier.prelude();\n" }, 
