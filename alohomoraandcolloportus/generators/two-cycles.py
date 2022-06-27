#!/usr/bin/env python3
import random
import sys

# Two disjoint cycles:
# - `a`: length of first cycle
# - `b`: length of second cycle
# - `s`: random seed

a, b, s = map(int, sys.argv[1:])
random.seed(s)

cycle1 = [(i,(i+1)%a) for i in range(a)]
cycle2 = [(i,(i+1)%b) for i in range(b)]
edges = cycle1 + [(i+a,j+a) for (i,j) in cycle2]

perm = list(range(1,a+b+1))
random.shuffle(perm)
edges = [(perm[i],perm[j]) for (i,j) in edges]
random.shuffle(edges)

print(a+b, len(edges))
for i,j in edges:
    if i > j: i,j = j,i
    print(i,j)
