#!/usr/bin/python3
import sys
import random
from fractions import Fraction
import math

random.seed(int(sys.argv[1]))
a = int(sys.argv[2])
b = int(sys.argv[3])
M = int(sys.argv[4])

A = [(0,0,M,M)]

while len(A) < a+b:
    i = random.randint(0, len(A)-1)
    if A[i][2]-A[i][0] == 1 and A[i][3]-A[i][1] == 1: continue
    t = A[i]
    del A[i]
    if (random.randint(0,1) == 0 and t[2]-t[0] > 1) or t[3]-t[1] == 1:
        x = random.randint(t[0]+1, t[2]-1)
        A.append((t[0], t[1], x, t[3]))
        A.append((x, t[1], t[2], t[3]))
    else:
        y = random.randint(t[1]+1, t[3]-1)
        A.append((t[0], t[1], t[2], y))
        A.append((t[0], y, t[2], t[3]))

print(a)
B = set()
while len(B) != a:
    i = random.randint(0, len(A)-1)
    if i in B: continue
    B.add(i)
    print(A[i][0], A[i][1], A[i][2], A[i][3])
    
