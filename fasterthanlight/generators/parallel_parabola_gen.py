#!/usr/bin/python3
import sys
import random

"""
Generate two random parabolas and generate
boxes in between
"""


random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
M = int(sys.argv[3])

def random_parabolas():
    xt = random.randint(0, M)
    yt = random.randint(0, M)
    mirror = False
    if 2*xt < M:
        mirror = True
        xt = M-xt
    y0 = random.randint(0, M)

    a = (y0-yt)/(xt*xt)
    b = -2*a*xt
    c = y0    

    if mirror:
        a, b, c = a, -b-2*a*M, c+b*M+a*M**2
        xt = M-xt
    f = lambda x: a*x*x + b*x + c
    c2 = c + random.randint(-int(min(f(0), f(M), f(xt))), int(M - max(f(0), f(M), f(xt))))
    g = lambda x: a*x*x + b*x + c2
    return f, g


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