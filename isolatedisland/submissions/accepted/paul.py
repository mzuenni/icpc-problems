#!/usr/bin/env python3
from collections import Counter

n = int(input())

points = []
for _ in range(n):
  a, b, c, d = map(int, input().split())
  points += [(a,b), (c,d)]

c = Counter(points)
print('yes' if any(x%2 == 1 for x in c.values()) else 'no')
