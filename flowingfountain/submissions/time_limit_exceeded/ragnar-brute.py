#!/usr/bin/env python3
n, q = map(int, input().split())
cs = list(map(int, input().split()))
vals = [0] * n

next = [n] * n
tmp = []
for i in range(n - 1, -1, -1):
    while tmp and cs[tmp[-1]] <= cs[i]:
        tmp.pop()
    if tmp:
        next[i] = tmp[-1]
    tmp.append(i)

for _ in range(q):
    args = list(input().split())
    for i in range(1, len(args)):
        args[i] = int(args[i])
    l = args[1] - 1
    if args[0] == '?':
        print(vals[l])
        continue
    x = args[2]
    while True:
        if l == n:
            break
        if vals[l] == cs[l]:
            l = next[l]
            continue
        add = min(x, cs[l] - vals[l])
        vals[l] += add
        x -= add
        if x == 0:
            break
        l = next[l]
