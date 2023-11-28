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
ans = 2

sum_len = 0
r1, r2 = 0, 0

for len in w:
    sum_len += len
    if len % 3 == 1:
        r1 += 1
    if len % 3 == 2:
        r2 += 1
    total_len = sum_len
    matching = min(r1, r2)
    if r1 > matching:
        total_len += (r1 - matching) // 2
        total_len += 2 * ((r1 - matching) % 2)
    if r2 > matching:
        total_len += r2 - matching
    if total_len <= 3 * s:
        ans += 1
print(ans)
