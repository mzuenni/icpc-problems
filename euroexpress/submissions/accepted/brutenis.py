#!/usr/bin/python3
n, *nums = map(int, open(0).read().split())
pairs = list(zip(nums[::2], nums[1::2]))
third = max(map(min, pairs))
best = 0
for a, b in pairs:
    lo, hi = sorted([a,b])
    best = max(best, lo*hi*min(lo, third))
print(best)
