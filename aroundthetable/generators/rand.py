#!/usr/bin/python3
#Echoes all arguments to stdout. Additionally, unescaped backslash escape
#character, e.g. \n will produce a newline.
import sys
import random
from random import randint

random.seed(sys.argv[1])

l = randint(2+2, 10**9-2)
r = l + randint(-2, 2)
print(l, r)
