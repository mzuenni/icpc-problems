import sys
inp = lambda: map(int, sys.stdin.buffer.readline().split())
w, h, q = inp()
h2 = 1
while h2 < h: h2 *= 2
arr = [list(range(w)) for i in range(2 * h2)]
for _ in range(q):
  a, b, c = inp()
  a += h2 - 1
  arr[a][b - 1], arr[a][c - 1] = arr[a][c - 1], arr[a][b - 1]
  while a > 1:
    a //= 2
    arr[a] = [arr[2 * a + 1][arr[2 * a][i]] for i in range(w)]
  c, vis = w, [1] * w
  for i in range(w):
    c -= vis[i]
    while vis[i]:
      vis[i], i = 0, arr[1][i]
  print(c)