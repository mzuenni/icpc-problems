#!/usr/bin/env python3
import itertools

class BIT:
  def __init__(self, n):
    self.n = n
    self.a = [0] * (n+2)

  def get(self, k):
    res = 0
    k += 1
    while k <= self.n:
      res += self.a[k]
      k += k & -k
    return res

  def add(self, k, x):
    while k > 0:
      self.a[k] += x
      k -= k & -k

  def add_range(self, l, r, x):
    self.add(r, x)
    self.add(l, -x)

MOD = 10**9+7

l = input().split()
n, m = map(int, l[:2])
p = (1 - round(float(l[2])*1e6) * pow(10, -6, MOD)) % MOD
q = pow(p, -1, MOD)

powp = list(itertools.accumulate([1] + [p]*n, lambda x, y: x*y % MOD))
powq = list(itertools.accumulate([1] + [q]*n, lambda x, y: x*y % MOD))

a = BIT(n+1)
c = BIT(n+1)
for _ in range(m):
  l = input().split()
  if len(l) == 3:
    x, k = map(int, l[1:])
    x = x if l[0] == '+' else -x
    a.add_range(k, n+1, x * powq[k])
    c.add(k, x * powp[k])
  else:
    k = int(l[1])
    res = a.get(k) * powp[k] + c.get(k) * powq[k]
    print(res % MOD)
