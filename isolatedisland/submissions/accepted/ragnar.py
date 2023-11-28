#!/usr/bin/env python3
from collections import Counter

ps = []
for _ in range(int(input())):
    a, b, c, d = map(int, input().split())
    ps.append((a, b))
    ps.append((c, d))
c = Counter(ps)
for v in c.values():
    if v % 2:
        print("yes")
        exit()
print("no")
