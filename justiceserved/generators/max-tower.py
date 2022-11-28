#!/usr/bin/env python3

import sys
import random

tp = sys.argv[1]
n = int(sys.argv[2])
x = int(sys.argv[3])
t = int(sys.argv[4])

print(n)
if tp == "left":
    for i in range(n):
        print(x, t - i)
if tp == "left-shuffle":
    random.seed(int(sys.argv[5]))
    l = list(range(n))
    random.shuffle(l)
    for i in l:
        print(x, t - i)
if tp == "right":
    for i in range(n):
        print(x + i, t - i)
