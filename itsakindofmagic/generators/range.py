#!/usr/bin/env python3
import sys

params = list(map(lambda x: int(eval(x)), sys.argv[1:]))
if len(params) == 1:
  params = [1] + params
vals = [*range(*params)]

print(len(vals))
print(*vals,sep='\n')
