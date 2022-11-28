#!/usr/bin/python3
import sys
import random

# First, place three rectangles in such a way that there is only one line passing through them,
# the line y = Qx/P where P and Q are coprime. Then, place a bunch of random rectangles that 
# cover this line.  

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])

P = 100000007
Q = 100000000
MAX_X = 10**9

x_coords = [P, 2*P, 3*P]
X = set(x_coords)

for _ in range(n-3):
    x = random.randint(0, MAX_X-1)
    while x in X:
        x = random.randint(0, MAX_X-1)
    X.add(x)
    x_coords.append(x)

x_coords.sort()

rectangles = []

for i in range(n):
    x1 = x_coords[i]
    lim = MAX_X
    if i < n-1:
        lim = x_coords[i+1]
    x2 = random.randint(x1+1, lim)
    if lim == 2*P:
        x2 = 2*P
        y1 = 2*Q
    

    y_lo = max(0, (Q*x1)//P - Q)
    y_hi = min(MAX_X, (Q*x1)//P + Q)

    y1 = random.randint(y_lo, (Q*x1)//P)
    y2 = random.randint((Q*x1+P-1)//P, y_hi)

    if x1 == P:
        y2 = Q
    if x1 == 3*P:
        y2 = 3*Q

    rectangles.append((x1,y1,x2,y2))

random.shuffle(rectangles)

print(n)
for R in rectangles:
    print(*R)
