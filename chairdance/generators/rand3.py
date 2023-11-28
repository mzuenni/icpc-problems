#!/usr/bin/python3
import sys
import random
import math

def get_coprime(x):
    res = random.randint(1, x)
    while math.gcd(res, x) != 1:
        res = random.randint(1, x)
    return res

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
q = int(sys.argv[3]) # questions
a = int(sys.argv[4]) # additions
m = int(sys.argv[5]) # multiplications

# Like rand2 but prefers coprime multiplications

print(n, q+a+m)

kind = [0]*q + [1]*a + [2]*m
random.shuffle(kind)

s = ['?', '+', '*']

for i in range(q+a+m):
    if kind[i] <= 1:
        print(s[kind[i]], random.randint(1, n))
    else:
        if random.randint(1, (q+a+m) // 300) != 1:
            print("*", get_coprime(n))
        else:
            print("*", random.randint(1, n))

    
