#!/usr/bin/env python3
import math
import random
import sys

for k in range(42):
    x = pow(2,k)
    print('?', x)
    sys.stdout.flush()
    a = int(input())
    if a < x:
        print('!', x-a)
        break
