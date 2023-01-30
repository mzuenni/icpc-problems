#!/usr/bin/python3
w=int(input().split()[1])
import re
print(*re.findall(f'.{{1,{w}}}',input()),sep='\n')
