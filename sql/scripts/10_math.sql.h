/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with sql2h.py. Do not edit this file directly.
{ "10_math", "\nCREATE FUNCTION degrees(r double)\nRETURNS double\nRETURN r*180/pi();\nCREATE FUNCTION radians(d double)\nRETURNS double\nRETURN d*pi()/180;\ngrant execute on function degrees to public;\ngrant execute on function radians to public;" }, 
