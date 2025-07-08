#!/usr/bin/python3
#Echoes all arguments to stdout. Additionally, unescaped backslash escape
#character, e.g. \n will produce a newline.
import sys
import random
from random import randint

random.seed(sys.argv[1])

l, r = eval(' '.join(sys.argv[2:]).encode('ascii').decode('unicode_escape'))
print(l, r)
