#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))

# This alternates a multiplication (which does not make the list shorter)
# with querying for n-1 (the worst case for linear lookup)

maxn = 500000
maxq = 500000

print(maxn, maxq)
chairq = maxn - 1
for i in range(maxq):
    if i % 2 == 0:
        print('?', chairq)
    else:
        m = 1
        while True:
            m = random.randint(2, maxn)
            if math.gcd(m, maxn) == 1:
                break
        chairq = (chairq * m) % maxn
        print('*', m)
