#!/usr/bin/env python3
print(150_000, 300_000)
print(*range(1, 150_001))
for i in range(1, 150_001):
    print('+', i, i)
for i in range(1, 150_000):
    print('+', i, 1)
print('?', 150_000)
