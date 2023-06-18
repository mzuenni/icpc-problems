#!/usr/bin/env python3

n = int(input())
pos = list(map(int, input().split()))
q = int(input())

N = 1 << 21
seg = [0] * (2*N)

def add(i, x):
  i += N
  seg[i] += x
  while i > 0:
    i >>= 1
    seg[i] = seg[2*i] + seg[2*i+1]

def find_one(i):
  i += N
  while i%2 == 1 or seg[i+1] == 0:
    i >>= 1
  i += 1
  while i < N:
    i = 2*i + (seg[2*i] == 0)
  return i-N

for i in set(range(N)) - set(pos):
  add(i, 1)

for _ in range(q):
  k = int(input()) - 1
  i = pos[k]
  j = find_one(i)
  add(i, 1)
  add(j, -1)
  pos[k] = j
  print(j)
