#!/usr/bin/python3

import sys

n, s = [int(x) for x in input().split()]
w = sorted([int(x) for x in input().split()])

if s == 1 or n == 1:
    print(1)
    sys.exit()

lo = 2
hi = n + 1

while hi - lo > 1:
    mid = (lo + hi) // 2

    full_space = sum([x // 3 for x in w[:mid-2]])
    short_extra = len([x for x in w[:mid-2] if x % 3 == 1])
    long_extra = len([x for x in w[:mid-2] if x % 3 == 2])

    if 2 + full_space + long_extra + max((short_extra - long_extra + 1) // 2, 0) <= s:
        lo = mid
    else:
        hi = mid

print(lo)
