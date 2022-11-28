#!/usr/bin/env python3

import sys
import random

# seed, #intervals, max x
seed, n, x = map(int, sys.argv[1:])
random.seed(seed)

n = min(n, x * (x - 1) // 2)

s = set()
while len(s) < n:
    [a, b] = sorted(random.sample(range(1, x + 1), k=2))
    s.add((a, b))

print(n)
for a, b in s:
    print(a, b - a)
