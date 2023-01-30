#!/usr/bin/python3
import functools
n, m = map(int, input().split())
todo = []
for i in range(n):
	a, b = map(int, input().split())
	todo.append((a, b))
todo.sort(key=functools.cmp_to_key(lambda a, b: a[1]*b[0] - b[1]*a[0]))
cost = 1
res = 0
for e in todo:
	res += cost * e[0];
	cost += e[1];
print(res)
