#!/usr/bin/env python3
n, q = map(int, input().split())
c = [1e18] + list(map(int, input().split()))
t, p, f = [0], [0]*(n+1), [0]*(n+1)
for i in range(n,0,-1):
    while c[t[-1]] < c[i]:
        t.pop()
    p[i] = t[-1]
    t.append(i)
for i in range(q):
  a = input().split()
  if a[0] == '?':
    print(f[int(a[1])])
  else:
    x,q = int(a[1]), int(a[2])
    while q+f[x] > c[x]:
      q -= c[x]-f[x]
      f[x] = c[x]
      if f[p[x]]==c[p[x]]:
        p[x] = p[p[x]]
      x = p[x]
    f[x] += q
