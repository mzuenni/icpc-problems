#!/usr/bin/env python3

d, stack, tree = [-1] * (n := int(input())), [(0, 0)], [[] for i in range(n)]
for u, v in [[int(j) - 1 for j in input().split()] for i in range(n - 1)]: tree[u].append(v), tree[v].append(u)
for i in range(n): stack += [(stack[i][1], c) for c in tree[stack[i][1]] if c != stack[i][0]]  # p, v = stack[i]
for p, v in reversed(stack): d[v] = min((ds := sorted([-1, -1] + [d[c] for c in tree[v]]))[-1] + 1, ds[-2] + 2)
for p, v in stack[1:]: d[v] = min(d[v], d[p] - 1)
print(sum(i < 0 for i in d))
