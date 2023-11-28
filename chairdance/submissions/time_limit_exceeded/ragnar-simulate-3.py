#!/usr/bin/env python3
# Only simulate non-empty positions at collapsing multiplications and queries.
from math import gcd

n, q = map(int, input().split())

s = n
offset = 0
delta = 1

# Who sits on each chair?
chairs = list(range(n))
mul = 1
add = 0

for _ in range(q):
    op, x = input().split()
    x = int(x)
    if op == "?":
        newchairs = [-1] * n
        for i in range(offset, offset + s * delta, delta):
            newpos = (i * mul + add) % n
            newchairs[newpos] = chairs[i % n]
        chairs = newchairs
        offset = (offset * mul + add) % n
        mul = 1
        add = 0

        p = chairs[x % n]
        if p == -1:
            print(-1)
        elif p == 0:
            print(n)
        else:
            print(p)
    elif op == "+":
        add += x
    elif op == "*":
        g = gcd(x, s)
        if g == 1:
            mul = mul * x % n
            add = add * x % n
        else:
            newchairs = [(2 * n, -1)] * n
            for i in range(offset, offset + s * delta, delta):
                oldpos = (i * mul + add) % n
                newpos = oldpos * x % n
                steps = (newpos - oldpos) % n
                if steps < newchairs[newpos][0]:
                    newchairs[newpos] = (steps, chairs[i % n])
            chairs = [x[1] for x in newchairs]
            s //= g
            delta *= g
            offset = (offset * mul + add) * x % n
            mul = 1
            add = 0
