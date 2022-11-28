#!/usr/bin/python3
import sys
import random
from fractions import Fraction
import math

random.seed(int(sys.argv[1]))
a = int(sys.argv[2])
b = int(sys.argv[3])
M = int(sys.argv[4])
orientation = int(sys.argv[5])

y = random.randint(1, M)

A = set()
A.add(0)
A.add(M)
while len(A) < a+b+1:
    A.add(random.randint(0, M))

A = list(A)
A.sort()
B = set()

print(a+1)
x0 = 0
x1 = M
y0 = y
y1 = y+1
if orientation == 0:
    print(x0, y0, x1, y1)
elif orientation == 1:
    print(M-y1, x0, M-y0, x1)
elif orientation == 2:
    print(M-x1, M-y1, M-x0, M-y0)
else:
    print(y0, M-x1, y1, M-x0)
while len(B) < a:
    i = random.randint(0, a+b-1)
    if i in B: continue
    B.add(i)
    x0 = A[i]
    x1 = A[i+1]
    y0 = random.randint(0, y-1)
    y1 = y
    if orientation == 0:
        print(x0, y0, x1, y1)
    elif orientation == 1:
        print(M-y1, x0, M-y0, x1)
    elif orientation == 2:
        print(M-x1, M-y1, M-x0, M-y0)
    else:
        print(y0, M-x1, y1, M-x0)
