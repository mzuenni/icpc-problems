#!/usr/bin/env python3
from functools import cmp_to_key

sx, sy, tx, ty = map(int, input().split())
s, t = (sx, sy), (tx, ty)
n = int(input())
ps = [list(map(int, input().split())) for _ in range(n)]

def det(p, q, r): return (p[0] - r[0]) * (q[1] - r[1]) - (p[1] - r[1]) * (q[0] - r[0])
def dist(p, q): return (p[0] - q[0]) ** 2 + (p[1] - q[1]) ** 2

pn = [[], []]

for p in ps:
    d = det(p, t, s)
    if d == 0: idx = dist(p, s) < dist(p, t)
    else: idx = d > 0
    pn[idx].append(p)

ans = 0

def make_cmp(s, t, reverse=1):
    def cmp(p1, p2):
        a = det(p1[1], p2[1], s)
        if a != 0: return a * reverse
        a = det(p1[1], p2[1], t)
        return -a * reverse

    return cmp


# Compute the number of inversions using a Fenwick tree, counting how many
# larger elements we've seen.
def inversions(p):
    n = len(p)
    cnt = [0] * (n + 1)

    def add(i):
        while i <= n:
            cnt[i] += 1
            i += i & -i

    def get(i):
        r = 0
        while i:
            r += cnt[i]
            i -= i & -i
        return r

    a = 0
    for x in p:
        a += get(n) - get(x)
        add(x + 1)
    return a


for ps in pn:
    a, b = list(enumerate(ps)), list(enumerate(ps))
    a.sort(key=cmp_to_key(make_cmp(s, t)))
    b.sort(key=cmp_to_key(make_cmp(t, s, reverse=-1)))
    b.reverse()

    bidx = [0] * len(ps)
    for i, (j, _) in enumerate(b):
        bidx[j] = i
    p = [bidx[x[0]] for x in a]
    ans += inversions(p)

print(ans)
