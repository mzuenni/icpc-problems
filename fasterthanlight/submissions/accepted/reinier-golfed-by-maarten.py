#!/usr/bin/env python3

# Check whether p2 lies below p1p3
def lies_below(p1, p2, p3): return (p1[0] - p2[0]) * (p3[1] - p2[1]) - (p1[1] - p2[1]) * (p3[0] - p2[0]) <= 0


def getC(A):
    R = []
    for p in A:
        while len(R) >= 2 and lies_below(R[len(R) - 2], R[len(R) - 1], p): R.pop()
        R.append(p)
    return R


def flip(A): return [(x, -y) for x, y in A]


def f(L, U):
    L, U, i, j = getC(sorted(L)), flip(getC(sorted(flip(U)))), 0, 0
    while i < len(L) or j < len(U):
        if j == len(U) or i < len(L) and L[i][0] < U[j][0]:
            if 0 < j < len(U) and not lies_below(U[j - 1], L[i], U[j]): return "impossible"
            i += 1
        else:
            if 0 < i < len(L) and not lies_below(L[i], U[j], L[i - 1]): return "impossible"
            j += 1


n = int(input())
A, B, C, D = (list(L) for L in zip(*(
    tuple((a(x1, x2), b(y1, y2)) for a, b in ((min, min), (max, min), (min, max), (max, max)))
    for x1, y1, x2, y2 in (map(int, input().split()) for _ in range(n)))))
print(f(A, D) and f(B, C) or "possible")
