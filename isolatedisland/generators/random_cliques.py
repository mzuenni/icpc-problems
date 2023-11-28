#!/usr/bin/python3
import sys
import random
import math

n = int(sys.argv[1])
minx = int(sys.argv[2])
maxx = int(sys.argv[3])
first_k = int(sys.argv[4])
random.seed(int(sys.argv[5]))


R = []
while n >= 3:
    if first_k > 0:
        k = first_k
        first_k = 0
    elif n >= 21:
        k = random.randint(1, 3) * 2 + 1
    elif n >= 10:
        k = 5
    elif n >= 3:
        k = 3
    n -= k * (k - 1) // 2
    A = [(random.randint(minx, maxx), random.randint(minx, maxx)) for i in range(k)]
    for i in range(k):
        for j in range(i + 1, k):
            R.append([A[i], A[j]])

for r in R:
    random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
    print(r[0][0], r[0][1], r[1][0], r[1][1])
