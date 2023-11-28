#!/usr/bin/env python3
n, s = map(int, input().split())
w = list(map(int, input().split()))
w.sort()
if min(s, n) <= 2:
    print(min(s, n))
    exit()

# The two outer plugs
w = w[:-2]
s -= 2
n -= 2

l = 0
h = min(n, s)
while l < h:
    m = (l + h + 1) // 2
    r1, r2 = 0, 0
    total_len = sum(w[:m])
    for len in w[:m]:
        if len % 3 == 1:
            r1 += 1
        if len % 3 == 2:
            r2 += 1
    matching = min(r1, r2)
    r1 -= matching
    r2 -= matching
    if r1 > 0:
        total_len += r1 // 2
        total_len += 2 * (r1 % 2)
    if r2 > 0:
        total_len += r2
    if total_len <= 3 * s:
        l = m
    else:
        h = m - 1
print(l + 2)
