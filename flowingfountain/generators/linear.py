#!/usr/bin/env python3
import sys
import random

seed = int(sys.argv[1])
random.seed(seed)

n = q = 300_000

# increasing, decreasing, random
add = sys.argv[2]
# increasing, decreasing, random
query = sys.argv[3]

print(n, q)
print(*range(1, n + 1))
x = 1_000_000_000

if add == "increasing":
    adds = list(range(1, n + 1, 2))
elif add == "decreasing":
    adds = list(reversed(range(1, n + 1, 2)))
else:
    adds = [random.randint(1, n) for _ in range(q // 2)]

if query == "increasing":
    querys = list(range(1, n + 1, 2))
elif query == "decreasing":
    querys = list(reversed(range(1, n + 1, 2)))
else:
    querys = [random.randint(1, n) for _ in range(q // 2)]

for i in range(q // 2):
    print("+", adds[i], x)
    print("?", querys[i])
