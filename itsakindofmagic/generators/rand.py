#!/usr/bin/env python3
import random
import sys

s = int(sys.argv[1])
random.seed(s)
n = int(eval(sys.argv[2]))

params = list(map(lambda x: int(eval(x)), sys.argv[3:]))
if len(params) == 0:
  params = [10**18]
if len(params) == 1:
  params = [1] + params

print(n)
print(*random.sample(range(*params), n), sep='\n')
