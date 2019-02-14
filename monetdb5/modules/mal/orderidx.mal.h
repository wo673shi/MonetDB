/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "orderidx", "pattern bat.orderidx(bv:bat[:any_1]):void\naddress OIDXcreate\ncomment \"Introduces the OID index arrangement of ordered values\";\n\npattern bat.orderidx(bv:bat[:any_1], pieces:int):void\naddress OIDXcreate\ncomment \"Introduces the OID index arrangement of ordered values\";\n\npattern bat.orderidx(bv:bat[:any_1], l:bat[:any_1]...):void\naddress OIDXmerge\ncomment \"Consolidates the OID index arrangement\";\n\npattern bat.hasorderidx(bv:bat[:any_1]):bit\naddress OIDXhasorderidx\ncomment \"Return true if order index exists\";\n\npattern bat.getorderidx(bv:bat[:any_1]):bat[:oid]\naddress OIDXgetorderidx\ncomment \"Return the order index if it exists\";\n\ncommand algebra.orderidx(bv:bat[:any_1], stable:bit):bat[:any_1]\naddress OIDXorderidx\ncomment \"Create an order index\";" }, 
