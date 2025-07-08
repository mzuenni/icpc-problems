#!/usr/bin/env python3

a, b = map(int, input().split())
print((a+b) * len(set(x % (a+b) for x in [a, -a, b+1, -b-1])) // 2)
