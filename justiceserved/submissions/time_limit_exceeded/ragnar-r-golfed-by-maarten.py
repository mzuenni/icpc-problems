#!/usr/bin/env python3
from bisect import insort, bisect


class S:
    def __init__(self, l, r, i): self.l, self.r, self.i, self.ans = l, r + l, i, 0


# start -> max answer
n, best = int(input()), [(-1, 0)]
ps = sorted((S(*map(int, input().split()), i) for i in range(n)), key=lambda s: (-s.r, s.l))
for s in ps:
    # s.ans   = prev(best.upper_bound(s.l))->second + 1;
    it = bisect(best, (s.l, n))
    s.ans = best[it - 1][1] + 1
    # auto it = best.insert_or_assign(s.l, s.ans).first;
    if best[it - 1][0] == s.l:
        best[it - 1] = (s.l, s.ans)
    else:
        insort(best, (s.l, s.ans))
        it += 1
    # if(next(it) != best.end() && next(it)->second <= s.ans) best.erase(next(it));
    if it < len(best) and best[it][1] <= s.ans: best[it:it + 1] = []
print(*(s.ans - 1 for s in sorted(ps, key=lambda s: s.i)))
