#!/usr/bin/python3
n, w = map(int, input().split())
line = input()
for i, c in enumerate(line):
	if i != 0 and i % w == 0:
		print()
	print(c, end = '')
