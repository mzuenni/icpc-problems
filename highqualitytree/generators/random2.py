#!/usr/bin/env python3
import sys
import random

random.seed(sys.argv[1])
n = int(sys.argv[2])
branch = int(sys.argv[3])

edges = []

outdeg = [0] * n

for i in range(1, n):
    lo = max(0,i-branch)
    parent = random.randrange(lo, i)
    tries = 0
    while outdeg[parent] == 2:
        parent = random.randrange(lo, i)
        tries += 1
        if tries >= 10:
            lo = 0
    outdeg[parent] += 1
    edges.append((i, parent))

remap = list(range(1, n))
random.shuffle(remap)
remap = [0] + remap

print(n)
random.shuffle(edges)
for (u, v) in edges:
    u = remap[u]
    v = remap[v]
    if random.randint(0, 1) == 0:
        (u, v) = (v, u)
    print(u+1, v+1)
