#!/usr/bin/python3
import random
import sys

random.seed(int(sys.argv[1]))
p = int(sys.argv[2])
mod = (random.randrange(2**p, 2**(p+1)) | 1) - 1

print(mod)
