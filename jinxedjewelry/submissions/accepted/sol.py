#!/usr/bin/python3
t = int(input())
for i in range(t):
	n = int(input())
	todo = list(map(int, input().split()))
	todo.sort()
	res = n
	sum = 0
	for j, x in enumerate(todo):
			remain = n-j-1;
			sum += x;
			if sum <= remain:
				res = min(res, remain);
			else:
				res = min(res, remain + 1);
				break
	print(res)
