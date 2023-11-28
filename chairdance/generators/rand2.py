#!/usr/bin/python3
import sys
import random
import math

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
q = int(sys.argv[3]) # questions
a = int(sys.argv[4]) # additions
m = int(sys.argv[5]) # multiplications

print(n, q+a+m)

kind = [0]*q + [1]*a + [2]*m
random.shuffle(kind)

s = ['?', '+', '*']

for i in range(q+a+m):
    print(s[kind[i]], random.randint(1, n))
    
