#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
q = int(sys.argv[3])

# Follow a few seats that always have people on them

print(n, q)

follow = random.sample(list(range(n)), 10)

for i in range(q):
    r = random.randint(1,3)
    if r == 1:
        f = random.choice(follow)
        if f == 0:
            f = n
        print("?", f)
    if r == 2:
        x = random.randint(1,n)
        for j in range(len(follow)):
            follow[j] += x
            follow[j] %= n
        print("+", x)
    if r == 3:
        x = random.randint(1,n)
        for j in range(len(follow)):
            follow[j] *= x
            follow[j] %= n
        print("*", x)
    
