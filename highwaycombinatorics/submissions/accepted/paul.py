#!/usr/bin/env python3

N, p = 83, 10**9 + 7

fib = [1, 1]
while len(fib) < N:
  fib.append((fib[-1]+fib[-2]) % p)

values = set()
def gen_partitions(rem, amax, x):
  values.add(x)
  for a in range(2, min(amax+1, rem)):
    gen_partitions(rem-a-1, a, x*fib[a] % p)

gen_partitions(N, N, 1)

def reconstruct(rem, amax, x, y):
  if x == y:
    return []
  for a in range(2, min(amax+1, rem)):
    v = reconstruct(rem-a-1, a, x*fib[a] % p, y)
    if v is not None:
      return v + [a]

x = int(input())
if x == 0:
  print('.##\n##.')
else:
  for y in values:
    z = x * pow(y, p-2, p) % p
    if z in values:
      v = reconstruct(N, N, 1, y) + reconstruct(N, N, 1, z)
      res = '#'
      for k in v:
        res += '.' * k + '#'
      print(res)
      print(res)
      break
