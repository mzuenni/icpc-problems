#!/usr/bin/env python3
# @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
import itertools

va, vb, c, d = input().split()
c, d = int(c), int(d)


def cancels(a):
    l = len(a)
    map = {}
    for i in range(l + 1):
        for drop in itertools.combinations(range(l), i):
            dropcnt = [0] * 10
            for pos in drop:
                dropcnt[int(a[pos])] += 1
            dropcnt = tuple(dropcnt)
            v = 0
            for pos in range(l):
                if pos not in drop:
                    v = v * 10 + int(a[pos])
            if dropcnt not in map:
                map[dropcnt] = set()
            map[dropcnt].add(v)
    return map


top = cancels(va)
bot = cancels(vb)
for adrop in top:
    if adrop in bot:
        for va in top[adrop]:
            for vb in bot[adrop]:
                if va * d == vb * c:
                    print("possible")
                    print(va, vb)
                    exit()
print("impossible")
