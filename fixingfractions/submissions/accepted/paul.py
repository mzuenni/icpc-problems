#!/usr/bin/env python3
from collections import Counter

def subseq(s, t):
  i = 0
  for c in s:
    while i < len(t) and t[i] != c:
      i += 1
    if i == len(t):
      return False
    i += 1
  return True

a, b, c, d = input().split()
c, d = int(c), int(d)

n = len(b)
for mask in range(1, 1 << n):
  y = ''.join(b[i] for i in range(n) if mask & (1 << i))
  if y[0] == '0':
    continue
  x = str(int(y)*c//d)
  if int(x)*d == int(y)*c and subseq(x, a) and Counter(a)-Counter(x) == Counter(b)-Counter(y):
    print('possible')
    print(x, y)
    exit(0)

print('impossible')
