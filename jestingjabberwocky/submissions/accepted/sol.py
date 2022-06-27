#!/usr/bin/python3

from itertools import permutations

s = input()
n = len(s)
suits = {x for x in s}
k = len(suits)

mini = 10000000
perms = list(permutations(list(suits)))
for p in perms:
    dp = [[0] * (k + 1) if i == 0 else [10000000] * (k + 1) for i in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, k + 1):
            dp[i][j] = min(dp[i - 1][j] + (s[i - 1] != p[j- 1]), dp[i][j - 1])
    mini = min(mini, dp[n][k])

print(mini)
