#!/usr/bin/env python3
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
            if va * d % c == 0:
                vb = va * d // c
                if vb in bot[adrop]:
                    print("possible")
                    print(va, vb)
                    exit()
print("impossible")
