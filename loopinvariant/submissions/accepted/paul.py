#!/usr/bin/env python3

s = input()

d = 0
for i, c in enumerate(s):
  d += 1 if c == '(' else -1
  if d == 0:
    break

t = s[i+1:] + s[:i+1]
print(t if s != t else 'no')
