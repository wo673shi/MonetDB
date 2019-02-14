/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "sql_hge", "\nmodule batsql;\nmodule sql;\n\n\npattern calc.hash( v:hge ) :lng address MKEYhash; \ncommand batcalc.hash( b:bat[:hge] ) :bat[:lng] address MKEYbathash;\n\ncommand sql.dec_round( v:hge, r:hge ) :hge \naddress hge_dec_round_wrap\ncomment \"round off the value v to nearests multiple of r\";\ncommand batsql.dec_round( v:bat[:hge], r:hge ) :bat[:hge] \naddress hge_bat_dec_round_wrap\ncomment \"round off the value v to nearests multiple of r\";\n\ncommand sql.round( v:hge, d:int, s:int, r:bte) :hge\naddress hge_round_wrap\ncomment \"round off the decimal v(d,s) to r digits behind the dot (if r < 0, before the dot)\";\ncommand batsql.round( v:bat[:hge], d:int, s:int, r:bte) :bat[:hge]\naddress hge_bat_round_wrap\ncomment \"round off the decimal v(d,s) to r digits behind the dot (if r < 0, before the dot)\";\n\ncommand calc.second_interval( sc:int, v:hge, ek:int, sk:int ) :lng\naddress hge_dec2second_interval\ncomment \"cast hge decimal to a second_interval\";\n\n\ncommand calc.hge( v:void, digits:int ) :hge \naddress nil_2num_hge\ncomment \"cast to hge and check for overflow\";\ncommand calc.hge( v:void, digits:int, scale:int ) :hge \naddress nil_2dec_hge\ncomment \"cast to dec(hge) and check for overflow\";\ncommand batcalc.hge( v:bat[:void], digits:int ) :bat[:hge] \naddress batnil_2num_hge\ncomment \"cast to hge and check for overflow\";\ncommand batcalc.hge( v:bat[:void], digits:int, scale:int ) :bat[:hge] \naddress batnil_2dec_hge\ncomment \"cast to dec(hge) and check for overflow\";\n\ncommand calc.hge( v:str, digits:int ) :hge \naddress str_2num_hge\ncomment \"cast to hge and check for overflow\";\ncommand calc.hge( v:str, digits:int, scale:int ) :hge \naddress str_2dec_hge\ncomment \"cast to dec(hge) and check for overflow\";\ncommand batcalc.hge( v:bat[:str], digits:int ) :bat[:hge] \naddress batstr_2num_hge\ncomment \"cast to hge and check for overflow\";\ncommand batcalc.hge( v:bat[:str], digits:int, scale:int ) :bat[:hge] \naddress batstr_2dec_hge\ncomment \"cast to dec(hge) and check for overflow\";\n\n\npattern calc.month_interval( v:hge, ek:int, sk:int ) :int\naddress month_interval\ncomment \"cast hge to a month_interval and check for overflow\";\n\npattern calc.second_interval( v:hge, ek:int, sk:int ) :lng\naddress second_interval\ncomment \"cast hge to a second_interval and check for overflow\";\n\ninclude sql_decimal_hge;\ninclude sql_aggr_hge;\ninclude sql_rank_hge;" }, 
