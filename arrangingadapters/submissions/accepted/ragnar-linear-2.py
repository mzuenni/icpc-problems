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
    if r1 > 0 and r2 > 0:
        r1 -= 1
        r2 -= 1
    ans += sum_len + r1 // 2 + 2 * (r1 % 2) + r2 <= 3 * s
print(ans)
