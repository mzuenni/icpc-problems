#!/usr/bin/env python3
from collections import Counter
import random

def is_forest(edges):
    par = dict()
    def get(x):
        while x in par: x = par[x]
        return x
    for a,b in edges:
        a = get(a)
        b = get(b)
        if a == b: return False
        a, b = random.sample([a,b], 2)
        par[a] = b
    return True

def is_path(n, edges):
    deg = Counter(sum(edges,[]))
    return len(edges) == n-1 and max(deg.values()) <= 2 and is_forest(edges)

def is_path_after_del(n, edges, k):
    def f(i): return i - (i > k)
    return is_path(n-1, [[f(i),f(j)] for i,j in edges if i != k and j != k])

def solve(n, edges):
    deg = Counter(sum(edges,[]))
    for i in range(1,n+1):
        if deg[i] >= 3 or deg[i] == 0:
            js = [i] + [i^j^k for j, k in edges if j == i or k == i][:3]
            return any(is_path_after_del(n, edges, j) for j in js)
    js = [i for i in range(1,n+1) if deg[i] == 1] + [1]
    return is_path_after_del(n, edges, js[0])

n, m = map(int, input().split())
edges = [list(map(int, input().split())) for _ in range(m)]
print('yes' if solve(n, edges) else 'no')
