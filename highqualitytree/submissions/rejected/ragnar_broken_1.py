#!/usr/bin/env python3
# Can RTE because of out of memory.
# WAs on a few cases as well.
# @EXPECTED_RESULTS@: RUN_TIME_ERROR,TIME_LIMIT_EXCEEDED,WRONG_ANSWER
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

target_depth = [0] * n


def dfst(u, p):
    t = 1000000
    if len(g[u]) == 1:
        t = 1
    if len(g[u]) == 2:
        t = 2
    if len(g[u]) == 3:
        for v in g[u]:
            if v != p:
                t = min(t, 2 + dfst(v, u))
    target_depth[u] = t
    return t


dfst(0, -1)

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
