#!/usr/bin/python3
#Echoes all arguments to stdout. Additionally, unescaped backslash escape
#character, e.g. \n will produce a newline.
import sys
import random

random.seed(13425463352)
list = eval(' '.join(sys.argv[2:]).encode('ascii').decode('unicode_escape'))
random.shuffle(list)
print(len(list), eval(sys.argv[1]))
print(*list)
