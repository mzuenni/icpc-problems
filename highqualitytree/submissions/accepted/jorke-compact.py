#!/usr/bin/env python3
n = int(input())
tree = [[] for i in range(n)]
for u,v in [[int(j)-1 for j in input().split()] for i in range(n-1)]:
    tree[u].append(v)
    tree[v].append(u)

stack = [(0,0)]
for i in range(n):
    p,v = stack[i]
    stack += [(v,c) for c in tree[v] if c != p]
d = [-1]*n
for p,v in reversed(stack):
    ds = sorted([-1,-1] + [d[c] for c in tree[v]])
    d[v] = min(ds[-1]+1,ds[-2]+2)
for p,v in stack[1:]:
    d[v] = min(d[v],d[p]-1)
print(sum([i<0 for i in d]))
