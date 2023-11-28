#!/usr/bin/python3
import sys
import random
import math

P = (int(sys.argv[1]), int(sys.argv[2]))
Q = (int(sys.argv[3]), int(sys.argv[4]))
random.seed(int(sys.argv[5]))

R = []
for i in range(3):
	a = (random.randint(-1000000,1000000), random.randint(-1000000,1000000))
	R.append([a,P])
	R.append([a,Q])

for r in R:
	random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
	print(r[0][0], r[0][1], r[1][0], r[1][1])
