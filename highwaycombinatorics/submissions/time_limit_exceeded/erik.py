import random
mod, fib, n = 10**9 + 7, [2, 3], int(input())
if n == 0:
  print('.##\n##.\n')
  exit(0)
while len(fib) < 75:
  fib += [fib[-1] + fib[-2]]
for i in range(len(fib)):
  fib[i] = (fib[i], pow(fib[i], mod - 2, mod), i + 2)
a, b, l, msk, vis = 1, 1, 0, [], {n:[]}
while True:
  x = random.choice(fib)
  if l + x[2] + 1 > 100:
    a, b, l, msk = 1, 1, 0, []
  a, b = a * x[0] % mod, b * x[1] % mod
  l += x[2] + 1
  msk += [x[2]]
  vis[n * b % mod] = msk[:]
  if a in vis:
    print(('#'.join(["." * x for x in msk + vis[a]]) + "\n") * 2)
    break