(l, r) = map(int, input().split())
n = l + r
if l == 1:
	print(2 * n)
elif (2 * l) % n in [0, 2]:
	print(n + n // 2)
elif (2 * l) % n == 1:
	print(n)
else:
	print(2 * n)
