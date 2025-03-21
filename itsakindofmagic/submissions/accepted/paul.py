#!/usr/bin/env python3
import itertools
import math
from collections import Counter
from functools import cache

m = 10**6 + 10
spf = list(range(m))
for i in range(2, m):
  if spf[i] == i:
    for j in range(i*i, m, i):
      spf[j] = min(spf[j], i)

def factorize(n):
  fac = Counter()
  while n > 1:
    fac[spf[n]] += 1
    n //= spf[n]
  return fac

count = [Counter() for _ in range(25)]
for c in range(25):
  for a in range(-c, c+1):
    for b in range(-c, c+1):
      if abs(a) + abs(b) > c:
        continue
      g = max(math.gcd(a, b), 1)
      x, y = a//g, b//g
      if (x, y) < (0, 0):
        x, y = -x, -y
      if max(abs(x), abs(y)) > 2:
        x, y = 1, 3
      count[c][(x, y)] += 1

def combine(u, v):
  if u == (0, 0):
    return v
  if v == (0, 0):
    return u
  if u == v:
    return u
  return (1, 3)

@cache
def solve_from_exponents(a):
  dp = Counter()
  dp[(0, 0)] = 1
  for k in a:
    ndp = Counter()
    for a, x in dp.items():
      for b, y in count[k].items():
        ndp[combine(a, b)] += x*y
    dp = ndp
  return dp[(1, 3)]

# Finds the number of 3x3 multiplicative magic squares with product `n**3`.
def solve(n):
  a = tuple(sorted(factorize(n).values()))
  return solve_from_exponents(a)

pref = [0] + [solve(n) for n in range(1, m)]
pref = list(itertools.accumulate(pref))

tc = int(input())
for _ in range(tc):
  n = int(input())
  r = round(n**(1/3) + 1)
  while r**3 > n:
    r -= 1
  print(pref[r])
