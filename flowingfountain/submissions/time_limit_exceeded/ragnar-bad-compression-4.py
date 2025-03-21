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

first = list(range(n + 1))

for _ in range(q):
    args = list(input().split())
    for i in range(1, len(args)):
        args[i] = int(args[i])
    l0 = args[1] - 1

    if args[0] == "?":
        print(vals[l0])
        continue
    l = first[l0]
    x = args[2]
    stack = [l]
    while True:
        if l == n:
            break
        if vals[l] == cs[l]:
            l = first[max(next[l], first[l])]
            stack.append(l)
            first[l0] = l
            continue
        # BUG: The stack should only be updated after the while loop.
        for ll in stack:
            first[ll] = l
        stack = []
        add = min(x, cs[l] - vals[l])
        vals[l] += add
        x -= add
        if x == 0:
            break
        l = first[next[l]]
        first[l0] = l
