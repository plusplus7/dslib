#!/usr/bin/env python

import os
import sys
import re

def usage():
    print "./gen.py [file_path]"
    sys.exit(1)

if len(sys.argv) != 2:
    usage()

precodes = ""
for line in open("ds.h", "r").readlines():
    inc = line.split("\"")
    if len(inc) != 1:
        precodes = precodes + open(inc[1], "r").read()

precodes = re.sub('(#include\s*"ds_\w+.h")', "", precodes)

codes = ""
try:
    fd = open(sys.argv[1], "r")
    print "Insert templates"
    codes = fd.read()
    codes = re.sub('(#include\s*"ds.h")', "", codes)
    codes = precodes + codes

except:
    print "Generate template file"
    codes = precodes + "int main()\n{\nreturn 0;\n}"
if os.path.isfile(sys.argv[1]):
    print sys.argv[1], "file exists, renamed as", sys.argv[1] + ".cpp"
    sys.argv[1] = sys.argv[1] + ".cpp"

fd = open(sys.argv[1], "w")
fd.write(codes)
