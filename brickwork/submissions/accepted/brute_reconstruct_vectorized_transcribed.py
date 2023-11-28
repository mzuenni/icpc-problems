#!/usr/bin/env python3
from collections import deque

bits = 32
shiftIndex = bits.bit_length() - 1
maskIndex = bits - 1
maskValue = (1 << bits) - 1

lim = 300007
dp = [0] * ((lim >> shiftIndex) + 6)

def getDp(i):
    return (dp[i >> shiftIndex] >> (i & maskIndex)) & 1

def clearDp(i):
    dp[i >> shiftIndex] &= ~(1 << (i & maskIndex))

def orDp(i, value):
    dp[i >> shiftIndex] |= value << (i & maskIndex)

n, w = map(int, input().split())
ws = map(int, input().split())
ws = sorted(set(ws))
n = len(ws)

dp[0] = 1
for x in ws:
    if getDp(w):
        break
    neq = 0
    for i in range(x, w+1, x):
        neq |= getDp(i)
    if x < bits:
        for i in range(x, w):
            orDp(i, getDp(i - x))
    else:
        ia = x >> shiftIndex
        ib = x & maskIndex
        for i in range(0, w - x, bits):
            i = i >> shiftIndex
            dp[i + ia] |= (dp[i] << ib) & maskValue
            dp[i + ia + 1] |= dp[i] >> (bits - ib)
        clearDp(w)
    if x == w or w % x != 0 or neq:
        orDp(w, getDp(w - x))

divs = 0
for x in ws:
    if w % x == 0:
        divs += 1

def reconstruct(first):
    res = [first]
    remains = w - first
    for j in range(n - 1, -1, -1):
        while remains >= ws[j] and getDp(remains - ws[j]):
            remains -= ws[j]
            res.append(ws[j])
    return sorted(res)

if not getDp(w) and divs < 2:
    print("impossible")
else:
    print("possible")
    rows = []
    for x in ws:
        if getDp(w - x):
            row = reconstruct(x)
            mi = row[0]
            ma = row[-1]
            rows.append(row)
            if len(row) == 1:
                rows = [row, row]
            if len(rows) == 2:
                break
            if mi == ma:
                continue
            rows.pop()
            if w % ma == 0:
                row.append(mi)
                row.pop(0)
                rows.append(row)
                rows.append([])
                for i in range(0, w, ma):
                    rows[-1].append(ma)
                break
            else:
                row = reconstruct(ma)
                mi = row[0]
                rows.append(row.copy())
                while row[0] == mi:
                    row.append(mi)
                    row.pop(0)
                rows.append(row)
                break
    assert len(rows) == 2
    for row in rows:
        print(len(row), *row)
