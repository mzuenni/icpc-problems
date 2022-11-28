#!/usr/bin/python3
import sys
import random
from fractions import Fraction
import math

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
w = int(sys.argv[3])
h = int(sys.argv[4])
d = float(sys.argv[5])
mirror = int(sys.argv[6]) != 0

y0 = random.random()*h
y1 = random.random()*h

l = lambda x: y0 + (y1-y0)*x/w + random.random()*d

A = set()
A.add((0, 0, 1, h))
A.add((w-1, 0, w, h))
while len(A) < n:
    x = random.random()*(w-2) + 1
    y = int(l(x))
    x = int(x)
    A.add((x, y, x+1, y+1))

A = list(A)
random.shuffle(A)

print(n)
for r in A:
    if not mirror:
        print(r[0], r[1], r[2], r[3])
    else:
        print(r[1], r[0], r[3], r[2])
