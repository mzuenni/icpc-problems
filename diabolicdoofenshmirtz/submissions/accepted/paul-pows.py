#!/usr/bin/env python3
import math
import random
import sys

random.seed(987)
g = 0
x = 1
for _ in range(40):
    print('?', x)
    sys.stdout.flush()
    a = int(input())
    if a == -1: break
    g = math.gcd(g, x-a)
    x = random.randint(x+1, 5*x)

print('!', g)
