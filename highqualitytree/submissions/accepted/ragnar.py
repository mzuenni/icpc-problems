#!/usr/bin/env python3
import sys

sys.setrecursionlimit(10000000)

n = int(input())

g = [[] for _ in range(n)]
g[0].append(-1)
depth = [0] * n

for _ in range(n - 1):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    g[x].append(y)
    g[y].append(x)

target_depth = [1000000] * n

stack = [(0, -1)]
for i in range(n):
    u, p = stack[i]
    for v in g[u]:
        if v != p:
            stack.append((v, u))

for u, p in reversed(stack):
    t = 1000000
    assert 1 <= len(g[u]) <= 3
    if len(g[u]) == 1:
        t = 1
    if len(g[u]) == 2:
        t = 2
    if len(g[u]) == 3:
        cs = []
        for v in g[u]:
            if v != p:
                assert target_depth[v] != 1000000
                cs.append(target_depth[v])
        t = 2 + min(cs[0], cs[1])
        if cs[0] == cs[1]:
            t = 1 + cs[0]
    target_depth[u] = t

removed = 0

# returns depth of tree, and max target depth of subtree
stack = [(0, -1, target_depth[0])]
while len(stack) > 0:
    u, p, maxt = stack.pop()
    maxt = min(maxt, target_depth[u])
    if maxt <= 0:
        removed += 1
    for v in g[u]:
        if v != p:
            stack.append((v, u, maxt - 1))

print(removed)
