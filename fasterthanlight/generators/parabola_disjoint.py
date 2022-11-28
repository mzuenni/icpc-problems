#!/usr/bin/python3
import sys
import random

"""
Generate two random disjunct parabolas and generate
boxes in between
"""


random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
M = int(sys.argv[3])

def random_parabolas():
    done = False
    while not done:
        xt = random.randint(0, M)
        yt = random.randint(0, M)
        mirror = False
        if 2*xt < M:
            mirror = True
            xt = M-xt
        y0 = random.randint(0, M)

        a0 = (y0-yt)/(xt*xt)
        b0 = -2*a0*xt
        c0 = y0

        if mirror:
            a0, b0, c0 = a0, -b0-2*a0*M, c0+b0*M+a0*M**2

        xt = random.randint(0, M)
        yt = random.randint(0, M)
        mirror = False
        if 2*xt < M:
            mirror = True
            xt = M-xt
        y0 = random.randint(0, M)

        a1 = (y0-yt)/(xt*xt)
        b1 = -2*a1*xt
        c1 = y0

        if mirror:
            a1, b1, c1 = a1, -b1-2*a1*M, c1+b1*M+a1*M**2
        
        if (b0-b1)**2 - 4*(a0-a1)*(c0-c1) <= 0:
            done = True
    return lambda x: a0*x*x + b0*x + c0, lambda x: a1*x*x + b1*x + c1


f, g = random_parabolas()

X = set()
while len(X) < 2*n:
    X.add(random.randint(0, M))

X = list(X)
X.sort()

print(n)
for i in range(n):
    x1 = X[2*i]
    x2 = X[2*i+1]
    y1 = int(min(f(x1), g(x1)))
    y2 = int(max(f(x1), g(x1)))
    if (y1 == y2): y1 -= 1
    print(x1,y1,x2,y2)