#!/usr/bin/env python3
import sys
import random

random.seed(sys.argv[1])
a = int(sys.argv[2])-1
b = int(sys.argv[3])+1

n = a+b
edges = []
for i in range(a):
    edges.append((i,i+1))
for i in range(1,b):
    edges.append((a+i,a+i//2))

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
