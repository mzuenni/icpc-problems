#!/usr/bin/env python3
import math
import random
import sys

print('?', 2)
if input() == '0':
    print('?', 3)
    sys.stdout.flush()
    print('!', 1+int(input()))
    sys.exit(0)

for k in range(2, 41):
    x = pow(2,k)
    print('?', x)
    sys.stdout.flush()
    a = int(input())
    if a < x:
        print('!', x-a)
        break
