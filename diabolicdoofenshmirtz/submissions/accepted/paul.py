#!/usr/bin/env python3
import math
import random
import sys

random.seed(987)
queries = sorted(random.sample(range(1, 10**18), 30))
g = 0
for x in queries:
    print('?', x)
    sys.stdout.flush()
    g = math.gcd(g, x-int(input()))

print('!', g)
