#!/usr/bin/python3
import sys
import random
import math

n = int(sys.argv[1])
minx = int(sys.argv[2])
maxx = int(sys.argv[3])
random.seed(int(sys.argv[4]))

P0 = (minx+1, maxx-1)
P1 = (maxx-1, minx+1)
R = [[P0,P1]]
k0 = (n-5)//2
k1 = n-5-k0
prev = P0
for i in range(k0-1):
	x = 0; y = 0
	while x >= y:
		x = random.randint(minx+1, maxx-1)
		y = random.randint(minx+1, maxx-1)
	R.append([prev, (x,y)])
	prev = (x,y)
R.append([prev, P0])

prev = P1
for i in range(k1-1):
	x = 0; y = 0
	while x <= y:
		x = random.randint(minx+1, maxx-1)
		y = random.randint(minx+1, maxx-1)
	R.append([prev, (x,y)])
	prev = (x,y)
R.append([prev, P1])

R.append([(minx, minx), (minx, maxx)])
R.append([(minx, maxx), (maxx, maxx)])
R.append([(maxx, maxx), (maxx, minx)])
R.append([(maxx, minx), (minx, minx)])

for r in R:
	random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
	print(r[0][0], r[0][1], r[1][0], r[1][1])
