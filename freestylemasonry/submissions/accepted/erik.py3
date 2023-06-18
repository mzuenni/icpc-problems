h = int(input().split()[1])
b, c = h, 1
for i in map(int, input().split() + [h]):
  c &= i <= b
  b = min(h, b + 1 - 2 * ((b - i) % 2))
print("impossible"[2 * c:])