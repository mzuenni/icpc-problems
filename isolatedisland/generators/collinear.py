#!/usr/bin/python3
import sys
import random
import math

n = int(sys.argv[1])
minx = int(sys.argv[2])
maxx = int(sys.argv[3])
xstep = int(sys.argv[4])
ystep = int(sys.argv[5])
random.seed(int(sys.argv[6]))

k = n-2
xstart = random.randint(minx, maxx-xstep*k)
ystart = random.randint(minx, maxx-ystep*k)

R = []
for i in range(k):
	P0 = (xstart + i*xstep, ystart + i*ystep)
	P1 = (xstart + (i+1)*xstep, ystart + (i+1)*ystep)
	R.append([P0, P1])

Q = (random.randint(minx, maxx), random.randint(minx, maxx))
R.append([Q, (xstart, ystart)])
R.append([Q, (xstart + k*xstep, ystart + k*ystep)])

for r in R:
	random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
	print(r[0][0], r[0][1], r[1][0], r[1][1])
