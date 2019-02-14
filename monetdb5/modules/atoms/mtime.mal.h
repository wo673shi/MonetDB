/*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.  If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
*/

// This file was generated automatically with mal2h.py. Do not edit this file directly.
{ "mtime", "\natom date :int;\ncommand date(s:date):date\naddress MTIMEdate_date\ncomment \"Noop routine.\";\n\ncommand fromstr()\naddress date_fromstr;\ncommand tostr()\naddress date_tostr;\n\n\npattern ==(v:date,w:date):bit\naddress CMDvarEQ\ncomment \"Equality of two dates\";\npattern ==(v:date,w:date,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two dates\";\npattern !=(v:date,w:date):bit\naddress CMDvarNE\ncomment \"Equality of two dates\";\npattern !=(v:date,w:date,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two dates\";\npattern <(v:date,w:date):bit\naddress CMDvarLT\ncomment \"Equality of two dates\";\npattern <=(v:date,w:date):bit\naddress CMDvarLE\ncomment \"Equality of two dates\";\npattern >(v:date,w:date):bit\naddress CMDvarGT\ncomment \"Equality of two dates\";\npattern >=(v:date,w:date):bit\naddress CMDvarGE\ncomment \"Equality of two dates\";\npattern isnil(v:date):bit\naddress CMDvarISNIL\ncomment \"Nil test for date value\";\n\nmodule mtime;\npattern calc.==(v:date,w:date):bit\naddress CMDvarEQ\ncomment \"Equality of two dates\";\npattern calc.==(v:date,w:date,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two dates\";\npattern calc.!=(v:date,w:date):bit\naddress CMDvarNE\ncomment \"Equality of two dates\";\npattern calc.!=(v:date,w:date,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two dates\";\npattern calc.<(v:date,w:date):bit\naddress CMDvarLT\ncomment \"Equality of two dates\";\npattern calc.<=(v:date,w:date):bit\naddress CMDvarLE\ncomment \"Equality of two dates\";\npattern calc.>(v:date,w:date):bit\naddress CMDvarGT\ncomment \"Equality of two dates\";\npattern calc.>=(v:date,w:date):bit\naddress CMDvarGE\ncomment \"Equality of two dates\";\n\n\n\natom daytime :int;\ncommand fromstr()\naddress daytime_tz_fromstr;\ncommand tostr()\naddress daytime_tostr;\n\n\npattern ==(v:daytime,w:daytime):bit\naddress CMDvarEQ\ncomment \"Equality of two daytimes\";\npattern ==(v:daytime,w:daytime,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two daytimes\";\npattern !=(v:daytime,w:daytime):bit\naddress CMDvarNE\ncomment \"Equality of two daytimes\";\npattern !=(v:daytime,w:daytime,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two daytimes\";\npattern <(v:daytime,w:daytime):bit\naddress CMDvarLT\ncomment \"Equality of two daytimes\";\npattern <=(v:daytime,w:daytime):bit\naddress CMDvarLE\ncomment \"Equality of two daytimes\";\npattern >(v:daytime,w:daytime):bit\naddress CMDvarGT\ncomment \"Equality of two daytimes\";\npattern >=(v:daytime,w:daytime):bit\naddress CMDvarGE\ncomment \"Equality of two daytimes\";\npattern isnil(v:daytime):bit\naddress CMDvarISNIL\ncomment \"Nil test for daytime value\";\n\nmodule mtime;\npattern calc.==(v:daytime,w:daytime):bit\naddress CMDvarEQ\ncomment \"Equality of two daytimes\";\npattern calc.==(v:daytime,w:daytime,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two daytimes\";\npattern calc.!=(v:daytime,w:daytime):bit\naddress CMDvarNE\ncomment \"Equality of two daytimes\";\npattern calc.!=(v:daytime,w:daytime,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two daytimes\";\npattern calc.<(v:daytime,w:daytime):bit\naddress CMDvarLT\ncomment \"Equality of two daytimes\";\npattern calc.<=(v:daytime,w:daytime):bit\naddress CMDvarLE\ncomment \"Equality of two daytimes\";\npattern calc.>(v:daytime,w:daytime):bit\naddress CMDvarGT\ncomment \"Equality of two daytimes\";\npattern calc.>=(v:daytime,w:daytime):bit\naddress CMDvarGE\ncomment \"Equality of two daytimes\";\n\n\n\n\natom timestamp :lng;\ncommand fromstr()\naddress timestamp_fromstr;\n\ncommand tostr()\naddress timestamp_tostr;\n\nunsafe command unix_epoch():timestamp\naddress MTIMEunix_epoch\ncomment \"The Unix epoch time (00:00:00 UTC on January 1, 1970)\";\nunsafe command epoch():timestamp\naddress MTIMEcurrent_timestamp\ncomment \"unix-time (epoch) support: seconds since the Unix epoch\";\n\ncommand epoch(t:timestamp):int\naddress MTIMEepoch2int\ncomment \"unix-time (epoch) support: seconds since epoch\";\n\ncommand epoch(t:int):timestamp\naddress MTIMEtimestamp\ncomment \"convert seconds since epoch into a timestamp\";\ncommand epoch(t:lng):timestamp\naddress MTIMEtimestamplng\ncomment \"convert milli seconds since epoch into a timestamp\";\n\n\npattern ==(v:timestamp,w:timestamp):bit\naddress CMDvarEQ\ncomment \"Equality of two timestamps\";\npattern ==(v:timestamp,w:timestamp,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two timestamps\";\npattern !=(v:timestamp,w:timestamp):bit\naddress CMDvarNE\ncomment \"Equality of two timestamps\";\npattern !=(v:timestamp,w:timestamp,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two timestamps\";\npattern <(v:timestamp,w:timestamp):bit\naddress CMDvarLT\ncomment \"Equality of two timestamps\";\npattern <=(v:timestamp,w:timestamp):bit\naddress CMDvarLE\ncomment \"Equality of two timestamps\";\npattern >(v:timestamp,w:timestamp):bit\naddress CMDvarGT\ncomment \"Equality of two timestamps\";\npattern >=(v:timestamp,w:timestamp):bit\naddress CMDvarGE\ncomment \"Equality of two timestamps\";\npattern isnil(v:timestamp):bit\naddress CMDvarISNIL\ncomment \"Nil test for timestamp value\";\n\nmodule mtime;\npattern calc.==(v:timestamp,w:timestamp):bit\naddress CMDvarEQ\ncomment \"Equality of two timestamps\";\npattern calc.==(v:timestamp,w:timestamp,nil_matches:bit):bit\naddress CMDvarEQ\ncomment \"Equality of two timestamps\";\npattern calc.!=(v:timestamp,w:timestamp):bit\naddress CMDvarNE\ncomment \"Equality of two timestamps\";\npattern calc.!=(v:timestamp,w:timestamp,nil_matches:bit):bit\naddress CMDvarNE\ncomment \"Equality of two timestamps\";\npattern calc.<(v:timestamp,w:timestamp):bit\naddress CMDvarLT\ncomment \"Equality of two timestamps\";\npattern calc.<=(v:timestamp,w:timestamp):bit\naddress CMDvarLE\ncomment \"Equality of two timestamps\";\npattern calc.>(v:timestamp,w:timestamp):bit\naddress CMDvarGT\ncomment \"Equality of two timestamps\";\npattern calc.>=(v:timestamp,w:timestamp):bit\naddress CMDvarGE\ncomment \"Equality of two timestamps\";\n\n\n\n\natom timezone :lng;\ncommand fromstr()\naddress tzone_fromstr;\ncommand tostr()\naddress tzone_tostr;\ncommand str(z:timezone):str\naddress MTIMEtzone_tostr;\ncommand timestamp(s:str):timestamp\naddress MTIMEtimestamp_fromstr;\ncommand timestamp(secs:int):timestamp\naddress MTIMEtimestamp\ncomment \"Utility function to create a timestamp from a number of seconds since the Unix epoch\";\n\natom zrule :int;\ncommand fromstr()\naddress rule_fromstr;\ncommand tostr()\naddress rule_tostr;\ncommand define(m:int,d:int,w:int,h:int,min:int):zrule\naddress MTIMEruleDef0\ncomment \"Introduce a synomym timezone rule.\";\ncommand define(m:int,d:str,w:int,h:int,min:int):zrule\naddress MTIMEruleDef1\ncomment \"Introduce a synomym timezone rule.\";\ncommand define(m:int,d:str,w:int,min:int):zrule\naddress MTIMEruleDef2\ncomment \"Introduce a synomym timezone rule.\";\n\n\nmodule batmtime;\nmodule mtime;\ncommand date_sub_sec_interval(t:date,s:int):date\naddress MTIMEdate_sub_sec_interval_wrap\ncomment \"Subtract seconds from a date\";\ncommand date_sub_msec_interval(t:date,ms:lng):date\naddress MTIMEdate_sub_msec_interval_lng_wrap;\n\ncommand date_add_sec_interval(t:date,s:int):date\naddress MTIMEdate_add_sec_interval_wrap\ncomment \"Add seconds to a date\";\ncommand date_add_msec_interval(t:date,ms:lng):date\naddress MTIMEdate_add_msec_interval_lng_wrap;\n\ncommand timestamp_sub_msec_interval(t:timestamp,ms:lng):timestamp\naddress MTIMEtimestamp_sub_msec_interval_lng_wrap;\ncommand timestamp_add_msec_interval(t:timestamp,ms:lng):timestamp\naddress MTIMEtimestamp_add;\n\ncommand timestamp_sub_month_interval(t:timestamp,s:int):timestamp\naddress MTIMEtimestamp_sub_month_interval_wrap\ncomment \"Subtract months from a timestamp\";\n\ncommand timestamp_sub_month_interval(t:timestamp,s:lng):timestamp\naddress MTIMEtimestamp_sub_month_interval_lng_wrap\ncomment \"Subtract months from a timestamp\";\n\ncommand timestamp_add_month_interval(t:timestamp,s:int):timestamp\naddress MTIMEtimestamp_add_month_interval_wrap\ncomment \"Add months to a timestamp\";\n\ncommand timestamp_add_month_interval(t:timestamp,s:lng):timestamp\naddress MTIMEtimestamp_add_month_interval_lng_wrap\ncomment \"Add months to a timestamp\";\n\ncommand timestamp(t:timestamp):timestamp\naddress MTIMEtimestamp2timestamp;\n\ncommand time_sub_msec_interval(t:daytime,ms:lng):daytime\naddress MTIMEtime_sub_msec_interval_wrap\ncomment \"Subtract seconds from a time\";\ncommand time_add_msec_interval(t:daytime,ms:lng):daytime\naddress MTIMEtime_add_msec_interval_wrap\ncomment \"Add seconds to a time\";\n\ncommand diff(val1:daytime, val2:daytime) :lng\naddress MTIMEdaytime_diff\ncomment \"returns the number of msec between 'val1' and 'val2'.\";\n\ncommand date_add_month_interval(t:date,s:int):date\naddress MTIMEdate_addmonths\ncomment \"Add months to a date\";\n\ncommand date_sub_month_interval(t:date,s:int):date\naddress MTIMEdate_submonths\ncomment \"Subtract months from a date\";\n\ncommand date(:date):date\naddress MTIMEdate2date\ncomment \"generate the nil date\";\ncommand date(:void):date\naddress MTIMEnil2date\ncomment \"generate the nil date\";\n\ncommand local_timezone():lng\naddress MTIMElocal_timezone\ncomment \"get the local timezone in seconds\";\n\ncommand timezone_local(t:timezone):void\naddress MTIMEtzone_set_local\ncomment \"set the local timezone; which is used for printing timestamps\";\ncommand timezone_local() :timezone\naddress MTIMEtzone_get_local\ncomment \"get the local timezone; which is used for printing timestamps\";\n\ncommand date(s:str):date\naddress MTIMEdate_fromstr\ncomment \"convert the string to a type date value\";\n\ncommand date(yr:int, mo:int, day:int):date\naddress MTIMEdate_create\ncomment \"creates a date from (year,month,day).\";\n\ncommand daytime(s:str):daytime\naddress MTIMEdaytime_fromstr\ncomment \"convert the string to a daytime value.\";\ncommand daytime(:daytime):daytime\naddress MTIMEdaytime2daytime;\ncommand daytime(:lng):daytime\naddress MTIMEsecs2daytime;\n\ncommand daytime(h:int,m:int,s:int,mi:int)\n\t\t:daytime\naddress MTIMEdaytime_create\ncomment \"creates a time from (hours,minutes,\n\tseconds,milliseconds) parameters.\";\ncommand timestamp(d:date,dt:daytime,t:timezone) :timestamp\naddress MTIMEtimestamp_create\ncomment \"creates a timestamp from (date, daytime,timezone) parameters.\";\ncommand timestamp(d:date,dt:daytime) :timestamp\naddress MTIMEtimestamp_create_default\ncomment \"creates a timestamp from (d,dt) parameters (in the local timezone).\";\ncommand timestamp(d:date) :timestamp\naddress MTIMEtimestamp_create_from_date\ncomment \"creates a timestamp from (d,00:00:00) parameters (in the local timezone).\";\n\ncommand rule(s:str):zrule\naddress MTIMErule_fromstr\ncomment \"create a rule from a  string.\";\ncommand rule (mo:int,d:int,wkday:int,mi:int) :zrule\naddress MTIMErule_create\ncomment \"create a DST start/end date rule.\";\n\ncommand timezone(s:str):timezone\naddress MTIMEtzone_fromstr\ncomment \"Convert the string to a timezone.\";\ncommand timezone(s:int):timezone\naddress MTIMEtzone_create\ncomment \"Convert the int to a timezone.\";\ncommand timezone(s:lng):timezone\naddress MTIMEtzone_create_lng\ncomment \"Convert the int to a timezone.\";\ncommand timezone(mi:int,s:zrule,erule:zrule):timezone\naddress MTIMEtzone_create_dst\ncomment \"create a timezone as an hour difference\n\tfrom GMT and a DST.\";\n\ncommand year(d:date) :int\naddress MTIMEdate_extract_year\ncomment \"extracts year from date (nonzero\n\tvalue between -5867411 and +5867411).\";\ncommand batmtime.year(d:bat[:date]):bat[:int]\naddress MTIMEdate_extract_year_bulk;\n\ncommand quarter(d:date) :int\naddress MTIMEdate_extract_quarter\ncomment \"extracts quarter from date\";\ncommand batmtime.quarter(d:bat[:date]):bat[:int]\naddress MTIMEdate_extract_quarter_bulk;\n\ncommand month(d:date) :int\naddress MTIMEdate_extract_month\ncomment \"extracts month from date\";\ncommand batmtime.month(d:bat[:date]):bat[:int]\naddress MTIMEdate_extract_month_bulk;\n\ncommand day(d:date) :int\naddress MTIMEdate_extract_day\ncomment \"extracts day from date \";\ncommand batmtime.day(d:bat[:date]):bat[:int]\naddress MTIMEdate_extract_day_bulk;\n\ncommand hours(h:daytime) :int\naddress MTIMEdaytime_extract_hours\ncomment \"extracts hour from daytime\";\ncommand batmtime.hours(d:bat[:daytime]):bat[:int]\naddress MTIMEdaytime_extract_hours_bulk;\n\ncommand minutes(d:daytime) :int\naddress MTIMEdaytime_extract_minutes\ncomment \"extracts minutes from daytime\";\ncommand batmtime.minutes(d:bat[:daytime]):bat[:int]\naddress MTIMEdaytime_extract_minutes_bulk;\n\ncommand seconds(d:daytime) :int\naddress MTIMEdaytime_extract_seconds\ncomment \"extracts seconds from daytime\";\ncommand batmtime.seconds(d:bat[:daytime]):bat[:int]\naddress MTIMEdaytime_extract_seconds_bulk;\n\ncommand sql_seconds(d:daytime) :int\naddress MTIMEdaytime_extract_sql_seconds\ncomment \"extracts seconds (with fractional milliseconds) from daytime\";\ncommand batmtime.sql_seconds(d:bat[:daytime]):bat[:int]\naddress MTIMEdaytime_extract_sql_seconds_bulk;\n\ncommand milliseconds(d:daytime) :int\naddress MTIMEdaytime_extract_milliseconds\ncomment \"extracts milliseconds from daytime\";\ncommand batmtime.milliseconds(d:bat[:daytime]):bat[:int]\naddress MTIMEdaytime_extract_milliseconds_bulk;\n\ncommand daytime(t:timestamp) :daytime\naddress MTIMEtimestamp_extract_daytime_default\ncomment \"extracts daytime from timestamp\n\tin the local timezone.\";\ncommand daytime(t:timestamp, v:timezone) :daytime\naddress MTIMEtimestamp_extract_daytime\ncomment \"extracts daytime from timestamp\n\tin a specific timezone.\";\n\ncommand date(t:timestamp) :date\naddress MTIMEtimestamp_extract_date_default\ncomment \"extracts date from timestamp\n\tin the local timezone.\";\ncommand date(t:timestamp,v:timezone) :date\naddress MTIMEtimestamp_extract_date\ncomment \"extracts date from timestamp in a\n\tspecific timezone.\";\n\ncommand setTimezone(name:str):timezone\naddress MTIMEtimezone\ncomment \"Test and set the timezone.\";\n\ncommand start_dst(t:timezone) :zrule\naddress MTIMEtzone_extract_start\ncomment \"extract rule that determines\n\tstart of DST from timezone.\";\ncommand end_dst(t:timezone) :zrule\naddress MTIMEtzone_extract_end\ncomment \"extract rule that determines\n\tend of DST from timezone.\";\ncommand minutes(t:timezone) :int\naddress MTIMEtzone_extract_minutes\ncomment \"extract number of minutes that\n\ttime zone is offset wrt GMT.\";\n\ncommand month(t:zrule) :int\naddress MTIMErule_extract_month\ncomment \"extract month from rule.\";\ncommand day(t:zrule) :int\naddress MTIMErule_extract_day\ncomment \"extract day from rule.\";\ncommand weekday(t:zrule) :int\naddress MTIMErule_extract_weekday\ncomment \"extract weekday from rule.\";\ncommand minutes(t:zrule) :int\naddress MTIMErule_extract_minutes\ncomment \"extract minutes from rule.\";\n\ncommand addyears(value:date, years:int) :date\naddress MTIMEdate_addyears\ncomment \"returns the date after a number\n\tof years (possibly negative).\";\ncommand addmonths(value:date, months:int) :date\naddress MTIMEdate_addmonths\ncomment \"returns the date after a number of\n\tmonths (possibly negative).\";\ncommand adddays(value:date, days:int) :date\naddress MTIMEdate_adddays\ncomment \"returns the date after a number\n\tof days (possibly negative).\";\ncommand diff(val1:date, val2:date) :int\naddress MTIMEdate_diff\ncomment \"returns the number of days\n\tbetween 'val1' and 'val2'.\";\n\ncommand dayofyear(d:date) :int\naddress MTIMEdate_extract_dayofyear\ncomment \"Returns N where d is the Nth day\n\tof the year (january 1 returns 1)\";\ncommand weekofyear(d:date) :int\naddress MTIMEdate_extract_weekofyear\ncomment \"Returns the week number in the year.\";\ncommand week(d:date) :int\naddress MTIMEdate_extract_weekofyear\ncomment \"Returns the week number in the year.\";\ncommand dayofweek(d:date) :int\naddress MTIMEdate_extract_dayofweek\ncomment \"Returns the current day of the week\n\twhere 1=monday, .., 7=sunday\";\n\ncommand add(v:timestamp, msecs:lng) :timestamp\naddress MTIMEtimestamp_add\ncomment \"returns the timestamp that comes 'msecs'\n\t(possibly negative) after 'value'.\";\ncommand diff(val1:timestamp, val2:timestamp) :lng\naddress MTIMEtimestamp_diff\ncomment \"returns the number of milliseconds\n\tbetween 'val1' and 'val2'.\";\n\ncommand dst(t:timestamp,v:timezone) :bit\naddress MTIMEtimestamp_inside_dst\ncomment \"return whether DST holds in the\n\ttimezone at a certain point of time.\";\n\ncommand compute(r:zrule, year:int) :date\naddress MTIMEcompute_rule_foryear\ncomment \"compute the date from a rule in a given year\";\n\ncommand monthnum(month:str) :int\naddress MTIMEmonth_from_str\ncomment \"Returns month number [1-12] from a string\n\t or nil if does not match any.\";\ncommand monthname(month:int) :str\naddress MTIMEmonth_to_str\ncomment \"Returns month name from a number\n\tbetween [1-12], str(nil) otherwise.\";\ncommand daynum(day:str) :int\naddress MTIMEday_from_str\ncomment \"Returns number of day [1-7] from a\n\tstring or nil if does not match any.\";\ncommand dayname(day:int) :str\naddress MTIMEday_to_str\ncomment \"Returns day name from a number\n\tbetween [1-7], str(nil) otherwise.\";\n\ncommand time_synonyms(allow:bit)\naddress MTIMEsynonyms\ncomment \"Allow synonyms for the parse format of\n\tdate/timestamp.\";\n\ncommand str_to_date(s:str, format:str) :date\naddress MTIMEstr_to_date\ncomment \"create a date from the string, using the specified format (see man strptime)\";\n\ncommand date_to_str(d:date, format:str) :str\naddress MTIMEdate_to_str\ncomment \"create a string from the date, using the specified format (see man strftime)\";\n\ncommand str_to_time(s:str, format:str) :daytime\naddress MTIMEstr_to_time\ncomment \"create a time from the string, using the specified format (see man strptime)\";\n\ncommand time_to_str(d:daytime, format:str) :str\naddress MTIMEtime_to_str\ncomment \"create a string from the time, using the specified format (see man strftime)\";\n\ncommand str_to_timestamp(s:str, format:str) :timestamp\naddress MTIMEstr_to_timestamp\ncomment \"create a timestamp from the string, using the specified format (see man strptime)\";\n\ncommand timestamp_to_str(d:timestamp, format:str) :str\naddress MTIMEtimestamp_to_str\ncomment \"create a string from the time, using the specified format (see man strftime)\";\n\n\ncommand msecs(d:int,h:int,m:int,s:int,ms:int):lng\naddress MTIMEmsecs\ncomment \"convert date components to milliseconds\";\n\ncommand daytime(h:int):daytime\naddress MTIMEdaytime1\ncomment \"default time with zeroed components\";\ncommand daytime(h:int,m:int):daytime\naddress MTIMEdaytime2\ncomment \"default time with zeroed components\";\ncommand daytime(h:int,m:int,s:int):daytime\naddress MTIMEdaytime3\ncomment \"default time with zeroed components\";\n\ncommand current_timestamp():timestamp\naddress MTIMEcurrent_timestamp;\ncommand current_date():date\naddress MTIMEcurrent_date;\ncommand current_time():daytime\naddress MTIMEcurrent_time;\n\ncommand year(t:timestamp):int\naddress MTIMEtimestamp_year;\ncommand quarter(t:timestamp):int\naddress MTIMEtimestamp_quarter;\ncommand month(t:timestamp):int\naddress MTIMEtimestamp_month;\ncommand day(t:timestamp):int\naddress MTIMEtimestamp_day;\ncommand hours(t:timestamp):int\naddress MTIMEtimestamp_hours;\ncommand minutes(t:timestamp):int\naddress MTIMEtimestamp_minutes;\ncommand seconds(t:timestamp):int\naddress MTIMEtimestamp_seconds;\ncommand sql_seconds(t:timestamp):int\naddress MTIMEtimestamp_sql_seconds;\ncommand milliseconds(t:timestamp):int\naddress MTIMEtimestamp_milliseconds;\n\ncommand year(months:int):int\naddress MTIMEsql_year;\ncommand month(months:int):int\naddress MTIMEsql_month;\ncommand day(msecs:lng):lng\naddress MTIMEsql_day;\ncommand hours(msecs:lng):int\naddress MTIMEsql_hours;\ncommand minutes(msecs:lng):int\naddress MTIMEsql_minutes;\ncommand seconds(msecs:lng):int\naddress MTIMEsql_seconds;\n\nunsafe command msec():lng\naddress MTIMEmsec\ncomment \"get time of day in msec since 1-1-1970.\";\n\ncommand prelude() :void\naddress MTIMEprelude;\n\ncommand epilogue() :void\naddress MTIMEepilogue;\n\nmtime.prelude();\n\nmodule calc;\n\ncommand date(s:str):date address MTIMEdate_fromstr;\ncommand date(d:date):date address MTIMEdate_date;\ncommand date(t:timestamp) :date address MTIMEtimestamp_extract_date_default;\n\ncommand timestamp(s:str):timestamp address MTIMEtimestamp_fromstr;\ncommand timestamp(t:timestamp):timestamp address MTIMEtimestamp2timestamp;\ncommand timestamp(d:date) :timestamp address MTIMEtimestamp_create_from_date;\ncommand timestamp(secs:int):timestamp address MTIMEtimestamp;\ncommand timestamp(msecs:lng):timestamp address MTIMEtimestamp_lng;\n\ncommand daytime(s:str):daytime address MTIMEdaytime_fromstr;\ncommand daytime(d:daytime):daytime address MTIMEdaytime2daytime;\ncommand daytime(s:lng):daytime address MTIMEsecs2daytime;\ncommand daytime(t:timestamp) :daytime address MTIMEtimestamp_extract_daytime_default;\n\nmodule batcalc;\n\ncommand date(t:bat[:timestamp]) :bat[:date]\naddress MTIMEtimestamp_extract_date_default_bulk;\n\ncommand timestamp(d:bat[:date]) :bat[:timestamp]\naddress MTIMEtimestamp_create_from_date_bulk;\ncommand timestamp(secs:bat[:int]) :bat[:timestamp]\naddress MTIMEtimestamp_bulk;\ncommand timestamp(msecs:bat[:lng]) :bat[:timestamp]\naddress MTIMEtimestamp_lng_bulk;\n\ncommand daytime(s:bat[:lng]) :bat[:daytime]\naddress MTIMEsecs2daytime_bulk;\ncommand daytime(t:bat[:timestamp]) :bat[:daytime]\naddress MTIMEtimestamp_extract_daytime_default_bulk;" }, 
