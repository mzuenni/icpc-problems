#!/usr/bin/env python3
import sys
import graphviz
from pathlib import Path

name = sys.argv[1]

with Path(name).with_suffix(".in").open() as f:
    n = int(f.readline())
    if n < 2000:
        t = [[] for i in range(n)]
        for i in range(n - 1):
            u, v = map(int, f.readline().split())
            t[u-1].append(v - 1)
            t[v-1].append(u - 1)

        dot = graphviz.Digraph()
        for i in range(n):
            dot.node(str(i+1))

        s = [(-1,0)]
        order = []
        while s:
            p, c = s.pop()
            order.append(c)
            if p >= 0:
                t[c].remove(p)
            for x in t[c]:
                dot.edge(str(c+1), str(x+1))
                s.append((c, x))

        res = [[]] * n
        for c in reversed(order):
            left = [] if len(t[c]) < 1 else res[t[c][0]]
            right = [] if len(t[c]) < 2 else res[t[c][1]]
            if len(left) > len(right):
                left,right = right,left
            while len(right) > len(left) + 1:
                for x in right[-1]:
                    pass
                del right[-1]
            for i, x in enumerate(left):
                right[i] += x
            res[c] = [[c]] + right

        keep = {x for tmp in res[0] for x in tmp}
        for i in range(n):
            if i not in keep:
                dot.node(str(i+1), fillcolor='lightpink', color='red', style='filled')

        dot.render(cleanup=True, outfile=Path(name).with_suffix(".pdf"));
