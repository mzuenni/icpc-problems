#!/usr/bin/env python3

n, m = map(int, input().split())
adj = [[] for _ in range(n)]
for _ in range(n): input()
for _ in range(m):
    a, b = [int(x)-1 for x in input().split()]
    adj[a].append(b)
    adj[b].append(a)

v = sorted(list(range(n)), key=lambda a: -len(adj[a]))

deleted = [False] * n
mark1 = [False] * n
mark2 = [0] * n
c3, c4 = False, False
for a in v:
    deleted[a] = True
    for b in adj[a]:
        if deleted[b]: continue
        mark1[b] = True
        if mark2[b]: c3 = True
        for c in adj[b]:
            if deleted[c]: continue
            mark2[c] += 1
            if mark1[c]: c3 = True
            if mark2[c] > 1: c4 = True
    for b in adj[a]:
        if deleted[b]: continue
        mark1[b] = False
        for c in adj[b]:
            mark2[c] = 0

print(3 if c3 else 4 if c4 else 5)
