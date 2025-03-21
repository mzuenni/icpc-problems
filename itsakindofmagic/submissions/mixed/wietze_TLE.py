#!/usr/bin/env python3
# @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED

# time limit exceeded
import math

lim = 10**6+1
factors = [[] for _ in range(lim)]
for p in range(2,1000):
    if factors[p] != []:
        continue
    for q in range(p, lim, p):
        factors[q].append(1)
    p_pow = p**2
    while p_pow < lim:
        for q in range(p_pow, lim, p_pow):
            factors[q][-1] += 1
        p_pow *= p
factors = [tuple(sorted(x)) for x in factors]
factor_set = set(factors) # 289 elements

nsol = dict()
for tup in factor_set:
    a_tups = [()]
    ans = 0
    tuplen = len(tup)
    for i in tup:
        a_tups = [(*t, j) for t in a_tups for j in range(2*i+1)]
    for a_tup in a_tups:
        c_tups = [()]
        for idx, i in enumerate(tup):
            c_tups = [(*t, j) for t in c_tups for j in range(abs(i-a_tup[idx]), min(3*i-a_tup[idx], i+a_tup[idx])+1)]
        for c_tup in c_tups:
            b_tup = tuple([3*tup[i]-a_tup[i]-c_tup[i] for i in range(tuplen)])
            d_tup = tuple([tup[i]-a_tup[i]+c_tup[i] for i in range(tuplen)])
            tups = [a_tup, c_tup, b_tup, d_tup]
            tups.extend([tuple([2*tup[i]-x[i] for i in range(tuplen)]) for x in tups])
            tups.append(tup)
            if len(set(tups)) == 9:
                ans += 1
    nsol[tup] = ans

answers = [nsol[tup] for tup in factors]
cumans = [0]*(lim+1)
for i in range(lim-1):
    cumans[i+1] = cumans[i] + answers[i+1]

for q in range(int(input())):
    n = int(input())
    x = int(n**(1/3))
    if (x+1)**3 <= n:
        x += 1
    if x**3 > n:
        x -= 1
    print(cumans[x])
