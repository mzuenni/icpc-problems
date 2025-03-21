#!/usr/bin/env python3
import sys

params = list(map(lambda x: int(eval(x)), sys.argv[1:]))
vals = [params[1]]*params[0]

print(len(vals))
print(*vals,sep='\n')
