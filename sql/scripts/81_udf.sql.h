/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with sql2h.py. Do not edit this file directly.
{ "81_udf", "\n\ncreate function reverse(src string)\nreturns string external name udf.reverse;\ncreate function fuse(one tinyint, two tinyint)\nreturns smallint external name udf.fuse;\ncreate function fuse(one smallint, two smallint)\nreturns integer external name udf.fuse;\ncreate function fuse(one integer, two integer)\nreturns bigint external name udf.fuse;" }, 
