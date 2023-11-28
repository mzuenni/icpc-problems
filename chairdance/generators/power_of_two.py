#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))
maxn = int(sys.argv[2])
q = int(sys.argv[3])

# n is a power of two and multiplications by two are rare.

n = 1
log2 = 0
while 2*n <= maxn:
    n *= 2
    log2 += 1

print(n, q)

for i in range(q):

    if i % (q // log2) == 0:
        print("*",2)
    else:
        r = random.randint(1,3)
        if r == 1:
            print("?", random.randint(1,n))
        if r == 2:
            print("+", random.randint(1,n))
        if r == 3:
            x = random.randrange(0,n//2)*2+1
            print("*", x)
    



