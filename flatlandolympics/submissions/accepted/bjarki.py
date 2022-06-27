#!/usr/bin/env python3
import sys
from functools import cmp_to_key

xs, ys, xe, ye = map(int, sys.stdin.readline().split())
S = (xs,ys)
E = (xe,ye)
n = int(sys.stdin.readline())

pts = []
for i in range(n):
    x, y = map(int, sys.stdin.readline().split())
    pts.append((x,y))

def sign(x):
    if x > 0:
        return 1
    if x < 0:
        return -1
    return 0

def cross(u, v):
    return u[0]*v[1] - u[1]*v[0]
def sub(u, v):
    return (u[0]-v[0], u[1]-v[1])
def ccw(ref, p1, p2):
    return cross(sub(p1, ref), sub(p2, ref))
def side(u, v, p):
    if u[0] < v[0]:
        return sign(p[0] - u[0])
    if u[0] > v[0]:
        return -sign(p[0] - u[0])
    if u[1] < v[1]:
        return sign(p[1] - u[1])
    if u[1] > v[1]:
        return -sign(p[1] - u[1])
    assert False
def d2(u, v):
    return (u[0]-v[0])**2 + (u[1]-v[1])**2

def start_order(p1, p2):
    if sign(ccw(S, E, p1)) != sign(ccw(S, E, p2)):
        return sign(ccw(S, E, p1)) - sign(ccw(S, E, p2))
    if sign(ccw(S, E, p1)) == 0 and side(S, E, p1) != side(S, E, p2):
        return side(S, E, p1) - side(S, E, p2)

    det = ccw(S, p1, p2)
    if det == 0:
        if sign(ccw(S, E, p1)) > 0:
            return d2(S,p2) - d2(S,p1)
        else:
            return d2(S,p1) - d2(S,p2)
    return det

def end_order(p1, p2):
    if sign(ccw(S, E, p1)) != sign(ccw(S, E, p2)):
        return sign(ccw(S, E, p1)) - sign(ccw(S, E, p2))
    if sign(ccw(S, E, p1)) == 0 and side(S, E, p1) != side(S, E, p2):
        return side(S, E, p1) - side(S, E, p2)

    det = ccw(E, p1, p2)
    if det == 0:
        if sign(ccw(S, E, p1)) > 0:
            return d2(E,p1) - d2(E,p2)
        else:
            return d2(E,p2) - d2(E,p1)
    return det

order1 = sorted(pts, key=cmp_to_key(start_order))
num = { pt: i for i, pt in enumerate(order1) }
order2 = sorted(pts, key=cmp_to_key(end_order))
perm = [ num[pt] for pt in order2 ]

def invs(perm):
    if len(perm) <= 1:
        return 0, perm
    m = len(perm)//2
    c1, h1 = invs(perm[:m])
    c2, h2 = invs(perm[m:])
    res = []
    cnt = c1 + c2
    l = 0
    r = 0
    while l < len(h1) and r < len(h2):
        if h1[l] < h2[r]:
            res.append(h1[l])
            l += 1
        else:
            cnt += (len(h1) - l)
            res.append(h2[r])
            r += 1
    res += h1[l:]
    res += h2[r:]
    return cnt, res

cnt, res = invs(perm)
print(cnt)

