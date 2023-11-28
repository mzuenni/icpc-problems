#!/usr/bin/python3
import sys
import random

random.seed(int(sys.argv[-1]))
a = random.randint(1, 10**18)
b = random.randint(1, 10**18)
c = random.randint(1, 10**18)
d = random.randint(1, 10**18)
print(a, b, c, d)
