#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))
maxn = int(sys.argv[2])
q = int(sys.argv[3])

# n = 2*3*5*7*..., and the multiplications go
# 2,2,2,2,3,3,3,3,3,3,5,5,5,5,7,7,7,7... (more or less).
# This is to create many merges.

primes = [2,3,5,7,11,13,17,19,23]
other_primes = [29,31,37,43,47,53]
n = 1
p = 0
while n*primes[p] <= maxn:
    n *= primes[p]
    p += 1
primes = primes[:p]

print(n, q)

good_chair = 0
n2 = n
for i in range(q):
    r = random.randint(1,3)
    if r == 1:
        x = (good_chair + (n // n2) * random.randrange(0, n2))%n
        if x == 0:
            x = n
        print("?", x)
    if r == 2:
        plus = random.randint(1,n)
        good_chair = (good_chair+plus)%n
        print("+", plus)
    if r == 3:
        lim = min(len(primes)-1, i // (q // len(primes)))
        p = primes[random.randint(0,lim)]
        if random.randint(1,3) == 1:
            p = random.choice(other_primes)
        n2 //= math.gcd(n2, p)
        good_chair = (good_chair * p)%n
        print("*", p)
    



