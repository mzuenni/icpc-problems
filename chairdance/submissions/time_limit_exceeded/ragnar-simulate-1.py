#!/usr/bin/env python3
from math import gcd

n, q = map(int, input().split())

s = n

# Who sits on each chair?
chairs = list(range(n))

for _ in range(q):
    op, x = input().split()
    x = int(x)
    if op == "?":
        p = chairs[x % n]
        if p == -1:
            print(-1)
        elif p == 0:
            print(n)
        else:
            print(p)
    elif op == "+":
        chairs = chairs[-x:] + chairs[:-x]
    elif op == "*":
        if gcd(x, s) == 1:
            newchairs = [-1] * n
            for i in range(n):
                if chairs[i] == -1:
                    continue
                newpos = i * x % n
                newchairs[newpos] = chairs[i]
            chairs = newchairs
        else:
            s //= gcd(x, s)
            newchairs = [(2 * n, -1)] * n
            for i in range(n):
                if chairs[i] == -1:
                    continue
                newpos = i * x % n
                steps = (newpos - i) % n
                if steps < newchairs[newpos][0]:
                    newchairs[newpos] = (steps, chairs[i])
            chairs = [x[1] for x in newchairs]
