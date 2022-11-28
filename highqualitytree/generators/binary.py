#!/usr/bin/env python3
import sys
import random

# Takes a binary tree and randomly moves leaves around

random.seed(sys.argv[1])
n = int(sys.argv[2])
noise = int(sys.argv[3])

edges = []

outdeg = [0] * n
parent = [0] * n
parent[0] = -1

for i in range(1, n):
    parent[i] = (i-1) // 2
    outdeg[parent[i]] += 1

leaves = []
for i in range(n):
    if outdeg[i] == 0:
        leaves.append(i)
random.shuffle(leaves)

x = 0
for _ in range(0, noise):
    y = leaves[x]
    while outdeg[y] > 0:
        x += 1
        y = leaves[x]
    outdeg[parent[y]] -= 1
    if outdeg[parent[y]] == 0:
        leaves.append(parent[y])
    
    new_parent = random.randrange(0, n)
    while outdeg[new_parent] == 2 or new_parent == y:
        new_parent = random.randrange(0, n)
    
    parent[y] = new_parent
    outdeg[new_parent] += 1
    leaves.append(y)
    x += 1

for i in range(1, n):
    edges.append((i, parent[i]))

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
