#!/usr/bin/env python3

w, h, q = map(int, input().split())

class Perm:
  def __init__(self, p=None):
    self.p = p if p else list(range(w))

  def __mul__(self, other):
    return Perm([other.p[self.p[i]] for i in range(w)])

  def cycle_count(self):
    mark = [False] * w
    res = 0
    for i in range(w):
      if not mark[i]:
        j = i
        while not mark[j]:
          mark[j] = True
          j = self.p[j]
        res += 1
    return res

swaps = [Perm() for _ in range(w-1)]
for k in range(w-1):
  swaps[k].p[k] = k+1
  swaps[k].p[k+1] = k

seg = [Perm() for _ in range(2*h)]

def update(i, k):
  i += h
  seg[i] = seg[i] * swaps[k]
  while i >= 1:
    i //= 2
    seg[i] = seg[2*i] * seg[2*i+1]

def query(i, j):
  i += h
  j += h
  a, b = Perm(), Perm()
  while i < j:
    if i%2 == 1:
      a = a * seg[i]
      i += 1
    if j%2 == 1:
      j -= 1
      b = seg[j] * b
    i //= 2
    j //= 2
  return a * b

for _ in range(q):
  y, x1, x2 = map(int, input().split())
  x = min(x1, x2) 
  update(y-1, x-1)
  print(w - query(0, h).cycle_count())
