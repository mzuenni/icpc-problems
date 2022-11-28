#!/usr/bin/python3
import sys
import random
from fractions import Fraction
import math

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
M = int(sys.argv[3])
t = int(sys.argv[4]) > 0
mirror = int(sys.argv[5]) != 0

def random_chain(n, Mx, My):
    A = set()
    while len(A) < n-1:
        x = random.randint(1, Mx//2//n)
        y = random.randint(-My//2//n, My//2//n)
        if (math.gcd(x, y) == 1):
            A.add((x,y))
    B = [Fraction(y, x) for (x, y) in A]
    B.sort(reverse=True)
    C = [(0,0)]
    for i in range(n-1):
        C.append((C[-1][0] + B[i].denominator, C[-1][1] + B[i].numerator))
    return C

def random_transform(A):
    x0 = min(p[0] for p in A)
    x1 = max(p[0] for p in A)
    y0 = min(p[1] for p in A)
    y1 = max(p[1] for p in A)
    dx = x1-x0
    dy = y1-y0
    a = random.randint(-((M-dy)//dx), (M-dy)//dx) # (x, y) -> (x, y + a*x)
    fx = random.randint(1, M//dx)     # (x, y + a*x) -> (fx*x, y + a*x)
    tx = random.randint(-fx*x0, M-1-fx*x1)
    ty = random.randint(-(y0 + min(a*x0, a*x1)), M - (y1 + max(a*x0, a*x1)))
    return [(fx*x + tx, y+a*x + ty) for (x, y) in A]

def printm(a, b, c, d):
    if (not mirror):
        print(a,b,c,d)
    else:
        print(b,a,d,c)

if not t:
    A = random_chain(n, M, M//2)
    random.shuffle(A)
    y1 = max(p[1] for p in A)
    A += [(x, 2*y1+1-y) for (x, y) in A]
    A = random_transform(A)

    print(n)
    for i in range(n):
        printm(A[i][0], A[i][1], A[i][0]+1, A[n+i][1])
else:
    A = random_chain(n//2, M//2, M//2)
    B = random_chain(n - n//2, (M-1)//2, M//2)
    random.shuffle(A)
    random.shuffle(B)
    A = [(2*x, y) for (x, y) in A]
    B = [(2*x+1, y) for (x, y) in B]
    y1a = max(p[1] for p in A)
    y1b = max(p[1] for p in B)
    x1a = [p for p in A if p[1] == y1a][0][0]
    x1b = [p for p in B if p[1] == y1b][0][0]
    yd = random.randint(-10, 10)
    A += [(x - x1b + x1a + 1, -y + y1a + y1b + yd) for (x, y) in B]
    A = random_transform(A)
    
    print(n)
    for i in range(n):
        if i < n//2:
            printm(A[i][0], A[i][1], A[i][0]+1, M)
        else:
            printm(A[i][0], 0, A[i][0]+1, A[i][1])
    
