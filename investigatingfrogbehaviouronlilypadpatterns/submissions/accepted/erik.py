n, a, m, seg = int(input()), list(map(int, input().split())), 2**21, [1] * 2**22
def g(i):
  seg[i] ^= 1
  while i > 1:
    seg[i // 2] = seg[i] + seg[i ^ 1]
    i //= 2
for i in range(m)[::-1]:
  seg[i] = 2 * seg[i * 2]
for i in a:
  g(i + m)
for _ in range(int(input())):
  i = int(input()) - 1
  j = a[i] + m
  g(j)
  j += 1
  while j > 1 and seg[j] == 0:
    j = (j + 1) // 2
  while j < m:
    j *= 2; j += not seg[j]
  a[i] = j - m
  g(j)
  print(a[i])