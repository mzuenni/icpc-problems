#!/usr/bin/env python3
from collections import deque

lim = 300007
dp = [0] * (lim // 64 + 7)

(_, w), ws = [map(int, input().split()) for _ in ".."]
ws = sorted(set(ws))
n = len(ws)

dp[0] = 1
for x in ws:
    if (dp[w // 64] >> (w & 63)) & 1: break  # = getDp
    neq = False
    for i in range(x, w + 1, x):
        neq |= (dp[i // 64] >> (i & 63)) & 1  # = getDp
    if x < 64:  # multiple set operations for same ull
        for i in range(x, w):
            i1 = i - x
            value = (dp[i1 // 64] >> (i1 & 63)) & 1  # = getDp
            dp[i // 64] |= value << (i & 63)  # = orDp
    else:
        ia = x // 64
        ib = x & 63
        i = 0
        for i in range(0, (w - x) // 64 + 1):
            dp[i + ia] |= dp[i] << ib
            if ib != 0: dp[i + ia + 1] |= dp[i] >> (64 - ib)
        # we know it wasnt set before
        dp[w // 64] &= ~(1 << (w & 63))  # = clearDp
    if x == w or w % x != 0 or neq:
        i2 = w - x
        value1 = (dp[i2 // 64] >> (i2 & 63)) & 1  # = getDp
        dp[w // 64] |= value1 << (w & 63) # = orDp

divs = 0
for x in ws:
    if w % x == 0: divs += 1


def reconstruct(first):
    res = [first]
    remains = w - first
    for j in range(n - 1, -1, -1):
        i = remains - ws[j]
        while remains >= ws[j] and (dp[i // 64] >> (i & 63)) & 1:  # = getDp
            remains -= ws[j]
            res.append(ws[j])
    return deque(sorted(res))


if not (dp[w // 64] >> (w & 63)) & 1 and divs < 2:  # = getDp
    exit(print("impossible"))

print("possible")
rows = []
for x in ws:
    i3 = w - x
    if (dp[i3 // 64] >> (i3 & 63)) & 1:  # = getDp
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
            row.popleft()
            rows.append(row)
            rows.append(deque([]))
            for i in range(0, w, ma):
                rows[-1].append(ma)
            break
        else:
            row = reconstruct(ma)
            mi = row[0]
            rows.append(deque(row))
            while row[0] == mi:
                row.append(mi)
                row.popleft()
            rows.append(row)
            break
assert len(rows) == 2
for row in rows:
    print(len(row), *row)
