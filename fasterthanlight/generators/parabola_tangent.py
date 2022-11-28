#!/usr/bin/python3
import sys
import random

"""
Generate two parabolas touching a line
with boxes touching the line and/or parabolas
"""


random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
Mx = int(sys.argv[3])
My = int(sys.argv[4])
topP = float(sys.argv[5])
bottomP = float(sys.argv[6])

def random_parabolas():
    y0 = random.randint(0, My)
    y1 = random.randint(0, My)
    l = lambda x: (y1-y0)*x/Mx + y0

    xt = random.randint(0, Mx)
    a0 = random.random()*min(l(0)/xt**2, l(Mx)/(xt-Mx)**2)
    a1 = random.random()*min((My-l(0))/xt**2, (My-l(Mx))/(xt-Mx)**2)
    f = lambda x: l(x) - (x-xt)**2 * a0
    g = lambda x: l(x) + (x-xt)**2 * a1

    return f, l, g


f, l, g = random_parabolas()

X = set()
while len(X) < n:
    X.add(random.randint(0, Mx))

X = list(X)

print(n)
for i in range(n):
    x1 = X[i]
    x2 = x1+1
    r = random.random()
    if r < bottomP:
        y1 = f(x1)
        y2 = l(x1)
    elif r < bottomP + topP:
        y1 = l(x1)
        y2 = g(x1)
    else:
        y1 = f(x1)
        y2 = g(x1)
    y1, y2 = int(y1), int(y2+1)
    while (y1 >= y2): y1 -= 1
    print(x1,y1,x2,y2)