#!/usr/bin/env python3

w, h, q = map(int, input().split())

def mul(a, b):
  return [b[a[k]] for k in range(w)]

seg = [list(range(w)) for _ in range(2*h)]

def update(i, k):
  i += h
  seg[i][k], seg[i][k+1] = seg[i][k+1], seg[i][k]
  while i >= 1:
    i //= 2
    for k in range(w):
      seg[i][k] = seg[2*i+1][seg[2*i][k]]

def query(i, j):
  i += h
  j += h
  a, b = [list(range(w)) for _ in range(2)]
  while i < j:
    if i%2 == 1:
      a = mul(a, seg[i])
      i += 1
    if j%2 == 1:
      j -= 1
      b = mul(seg[j], b)
    i //= 2
    j //= 2
  return mul(a, b)

def cycle_count(a):
  mark = [False] * w
  res = 0
  for i in range(w):
    if not mark[i]:
      j = i
      while not mark[j]:
        mark[j] = True
        j = a[j]
      res += 1
  return res

for _ in range(q):
  y, x1, x2 = map(int, input().split())
  x = min(x1, x2) 
  update(y-1, x-1)
  print(w - cycle_count(query(0, h)))
