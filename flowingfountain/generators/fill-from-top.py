#!/usr/bin/env python3
n = q = 300_000

# Levels of size 1,2,3,4,...
#
# If 'stagger':
#
# Add 1+2 to level 1, query level 2
# Add 3+4 to level 2, query level 4
# Add 5+6 to level 3, query level 6
# ...
#
# Else, always add to level 1.

print(n, q)
print(*range(1, n + 1))
x = 1_000_000_000

import sys

stagger = "stagger" in sys.argv

for i in range(1, q // 2 + 1):
    addto = i if stagger else 1
    print("+", addto, i + (i + 1))
    print("?", 2 * i)
