#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
q = int(sys.argv[3])

print(n, q)

for i in range(q):
    r = random.randint(1, 3)
    if r == 1:
        i = random.randint(1, n)
        print("?", i)
    if r == 2:
        i = random.randint(1, n)
        print("+", i)
    if r == 3:
        i = random.randint(1, n-1)
        print("*", i)

    
