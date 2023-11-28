#!/usr/bin/env python3
# Simulate fully collapsing multiplications.
# Do some modular inverse math to answer queries.
from math import gcd

n, q = map(int, input().split())

s = n
offset = 0
delta = 1

# Who sits on each chair?
chairs = list(range(n))
chairs[0] = n
mul = 1
add = 0

for _ in range(q):
    op, x = input().split()
    x = int(x)
    if op == "?":
        # Simulated filled chairs are at
        #   offset + k * delta
        # Filled chairs are currently at
        #  (offset + k * delta) * mul + add
        # Queried chair is x
        # Solve for k:
        #  (offset + k * delta) * mul + add = x
        #  (offset + k * delta) * mul = x - add
        #  offset * mul + k * delta * mul = x - add mod n
        #  k * delta * mul = (x - add) - offset * mul =: y mod n
        # check y%delta = 0
        #  k * mul = y/delta mod s
        #  k = y/delta * (mul^-1 mod s)
        #
        # gcd(mul, s) = gcd(mul, n/delta) = 1
        y = x - add - offset * mul
        if y % delta != 0:
            print(-1)
            continue
        k = y // delta * pow(mul, -1, s) % s
        oldpos = (offset + k * delta) % n
        print(chairs[oldpos])
    elif op == "+":
        add += x
    elif op == "*":
        g = gcd(x, s)
        if g == 1:
            mul = mul * x % n
            add = add * x % n
        else:
            newchairs = [(2 * n, -1)] * n
            for i in range(n):
                if chairs[i] == -1:
                    continue
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
