# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.  If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.

from __future__ import print_function

import os
import sys


if len(sys.argv) < 2:
    raise Exception("One argument must be given to sql2h.py")

sql_content_file = open(sys.argv[1], 'r')
sql_content = sql_content_file.read()
sql_content_file.close()

# get the file name and extension
base = os.path.basename(sys.argv[1])
split = os.path.splitext(base)
filebasename = split[0]

sql_h_output_file = open(filebasename + ".sql.h", 'w')

# write the common header
insert1 = (
'/*\n'
'* This Source Code Form is subject to the terms of the Mozilla Public\n'
'* License, v. 2.0.  If a copy of the MPL was not distributed with this\n'
'* file, You can obtain one at http://mozilla.org/MPL/2.0/.\n'
'*\n'
'* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.\n'
'*/\n'
'\n'
'// This file was generated automatically with sql2h.py. Do not edit this file directly.\n'
'{{ "{0}", "').format(filebasename)

sql_h_output_file.write(insert1)

# Let's remove comments from the sql script with a Markov chain :) Bugs might still be there
# STATES 0 - OK, 1 in # comment, 2 in -- comment, 3 in /* comment, 4 inside ' string, 5 inside " string,
# 6 inside whitespaces
CACHE_SIZE = 4096

buffer = ['\0'] * CACHE_SIZE
cur_state = 0
current_pointer = 0
i = 0
endloop = len(sql_content) - 1


def write_to_buffer(input_c):
    global current_pointer, sql_h_output_file, buffer
    if current_pointer == CACHE_SIZE:
        sql_h_output_file.write("".join(buffer))
        current_pointer = 0
    buffer[current_pointer] = input_c
    current_pointer += 1


while i < endloop:
    c = sql_content[i]

    if cur_state == 1:
        if c == '\n':
            cur_state = 0
        i += 1
        continue
    elif cur_state == 2:
        if c == '\n':
            cur_state = 0
        i += 1
        continue
    elif cur_state == 3:
        if c == '*' and i + 1 < endloop and sql_content[i + 1] == '/':
            cur_state = 0
            i += 1
        i += 1
        continue
    elif cur_state == 4:
        if c == '\\' and i + 1 < endloop:
            write_to_buffer('\\')
            write_to_buffer('\\')
            write_to_buffer('\\')
            write_to_buffer(sql_content[i + 1])
            i += 2
        else:
            if c == '\'':
                cur_state = 0
            write_to_buffer(c)
            i += 1
        continue
    elif cur_state == 5 and i + 1 < endloop:
        if c == '\\':
            write_to_buffer('\\')
            write_to_buffer('\\')
            write_to_buffer('\\')
            write_to_buffer(sql_content[i + 1])
            i += 2
        else:
            if c == '"':
                cur_state = 0
                write_to_buffer('\\')
            write_to_buffer(c)
            i += 1
        continue
    elif cur_state == 6:
        if c not in (' ', '\t', '\n'):
            cur_state = 0
            continue
        i += 1
        continue

    if c == '#':
        cur_state = 1
        i += 1
        continue
    elif c == '-' and i + 1 < endloop and sql_content[i + 1] == '-':
        cur_state = 2
        i += 2
        continue
    elif c == '/' and i + 1 < endloop and sql_content[i + 1] == '*':
        cur_state = 3
        i += 2
        continue
    elif c == '\'':
        write_to_buffer(c)
        cur_state = 4
        i += 1
        continue
    elif c == '"':
        write_to_buffer('\\')
        write_to_buffer(c)
        cur_state = 5
        i += 1
        continue
    elif c in (' ', '\t', '\n'):
        if c == '\n':
            write_to_buffer('\\')
            write_to_buffer('n')
        elif c == '\t':
            write_to_buffer('\\')
            write_to_buffer('t')
        else:
            write_to_buffer(c)
        cur_state = 6
        i += 1
        continue

    if c == '\\':
        write_to_buffer('\\')
    write_to_buffer(c)
    i += 1

if current_pointer > 0:
    sql_h_output_file.write("".join(buffer[:current_pointer]))

# insert more common stuff
sql_h_output_file.write('" }}, \n'.format())
sql_h_output_file.close()

sql_h_output_file.close()
