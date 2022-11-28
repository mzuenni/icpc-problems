#!/usr/bin/env python3
n = int(input())
tree = [[] for i in range(n+1)]
tree[1].append(0)
for i in range(n-1):
    u,v = [int(i) for i in input().split()]
    tree[u].append(v)
    tree[v].append(u)

DFS = []
stack = [(0,1)]
while stack:
    p,v = stack.pop()
    DFS.append(v)
    tree[v].remove(p)
    for w in tree[v]:
        stack.append((v,w))

d = [0]*(n+1)
for i in reversed(DFS):
    left = d[tree[i][0]] if tree[i] else -1
    right = d[tree[i][1]] if len(tree[i]) > 1 else -1
    d[i] = left+1 if left == right else min(left,right)+2

ans = 0
for i in DFS:
    for j in tree[i]:
        if d[j] >= d[i]:
            d[j] = d[i]-1
        if d[j] < 0:
            ans += 1
print(ans)
