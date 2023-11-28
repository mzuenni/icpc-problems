#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
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
                    if v == 0 and a[pos] == "0":
                        break
                    v = v * 10 + int(a[pos])
            if v != 0:
                if dropcnt not in map:
                    map[dropcnt] = set()
                map[dropcnt].add(v)
    return map


top = cancels(va)
bot = cancels(vb)
for adrop in top:
    if adrop in bot:
        for va in top[adrop]:
            # This is relatively slow because instead of computing vb and
            # checking if it's possible, it checks for all of them if they
            # result in the right value.
            for vb in bot[adrop]:
                if va * d == vb * c:
                    print("possible")
                    print(va, vb)
                    exit()
print("impossible")
