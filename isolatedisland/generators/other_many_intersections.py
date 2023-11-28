#!/usr/bin/python3
import sys
import random
import math

n = int(sys.argv[1])
minx = int(sys.argv[2])
maxx = int(sys.argv[3])
random.seed(int(sys.argv[4]))

k = n//4 - 1
A = []
for i in range(4):
	B = set()
	while len(B) < k:
		B.add(random.randint(minx, maxx))
	A.append(sorted(list(B)))

P = [(minx,minx),(minx,maxx),(maxx,maxx),(maxx,minx)]
R = [[P[0],P[1]], [P[1],P[2]], [P[2],P[3]], [P[3],P[0]]]
for i in range(k):
	R.append([(minx, A[0][i]), (maxx, A[1][-(i+1)])])
	R.append([(A[2][i], minx), (A[3][-(i+1)], maxx)])
for r in R:
	random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
	print(r[0][0], r[0][1], r[1][0], r[1][1])
