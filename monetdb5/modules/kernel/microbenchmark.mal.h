/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "microbenchmark", "\nmodule microbenchmark;\n\ncommand random(base:oid, size:lng, domain:int):bat[:int]\naddress MBMrandom\ncomment \"Create a BAT with random integer distribution; domain == nil:int ? [0:RAND_MAX] : [0,domain)\";\n\ncommand random(base:oid, size:lng, domain:int, seed:int):bat[:int]\naddress MBMrandom_seed\ncomment \"Create a BAT with random integer distribution,\n         using given seed (seed == nil:int -> no seed used);\n         domain == nil:int ? [0:RAND_MAX] : [0,domain)\";\n\ncommand uniform(base:oid, size:lng, domain:int):bat[:int]\naddress MBMuniform\ncomment \"Create a BAT with uniform integer distribution\";\n\ncommand normal(base:oid, size:lng, domain:int, stddev:int, mean:int):bat[:int]\naddress MBMnormal\ncomment \"Create a BAT with a normal integer distribution\";\n\ncommand mix(b1:bat[:int]):bat[:int]\naddress MBMmix\ncomment \"Mix the BUNs of this BAT\";\n\ncommand skewed(base:oid, size:lng, domain:int, skew:int):bat[:int]\naddress MBMskewed\ncomment \"Create a BAT with skewed integer distribution\";\n" }, 
