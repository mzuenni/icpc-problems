#!/usr/bin/env python3

import math

### from pyrival
def extended_gcd(a, b):
    """returns gcd(a, b), s, r s.t. a * s + b * r == gcd(a, b)"""
    s, old_s = 0, 1
    r, old_r = b, a
    while r:
        q = old_r // r
        old_r, r = r, old_r - q * r
        old_s, s = s, old_s - q * s
    return old_r, old_s, (old_r - old_s * a) // b if b else 0


def modinv(a, m):
    """returns the modular inverse of a w.r.t. to m, works when a and m are coprime"""
    g, x, _ = extended_gcd(a % m, m)
    return x % m if g == 1 else None
###

n,q = map(int,input().split())

owner = list(range(n))
owner[0] = n
k = 1
m = 0
np = n

for _ in range(q):
    ch, x = input().split()
    x = int(x)%n
    if ch == '?':
        x2 = (x+n-m)%n
        if x2%(n//np) != 0:
            print(-1)
        else:
            x2 //= (n//np)
            xp = (modinv(k,np)*x2)%np
            print(owner[(n//np)*xp])
    elif ch == '+':
        m = (m+x)%n
    else:
        g = math.gcd(x, np)
        if g == 1:
            k = (k*x)%n
            m = (m*x)%n
        else:
            owner2 = [-1]*n
            for i in range(n):
                if owner[i] != -1:
                    owner2[(k*i+m)%n] = owner[i]
            owner = owner2

            owner3 = [-1]*n
            counter_dist = [n+1]*n
            for i in range(n):
                if owner[i] != -1:
                    j = (x*i)%n
                    cd = (j-i+n)%n
                    if cd < counter_dist[j]:
                        counter_dist[j] = cd
                        owner3[j] = owner[i]
            k = 1
            for i in range(n):
                if owner3[i] != -1:
                    m = i
                    break
            for i in range(n):
                owner[i] = owner3[(i+m)%n]
            np //= g

