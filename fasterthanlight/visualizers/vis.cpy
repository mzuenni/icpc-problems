#!/usr/bin/env python3

import sys
import matplotlib.pyplot as plt
from math import sin, cos, pi
from pathlib import Path

name = sys.argv[1]
f = Path(name).with_suffix(".in").read_text().splitlines()
n = int(f[0])

if n > 10000:
    exit(0)

fig, ax = plt.subplots()
ax.set_aspect("equal", adjustable="box")
xl, xh, yl, yh = 1e9, 0, 1e9, 0

for line in f[1:]:
    x0, y0, x1, y1 = map(int, line.split())
    xl = min(xl, x0, x1)
    yl = min(yl, y0, y1)
    xh = max(xh, x0, x1)
    yh = max(yh, y0, y1)
    ax.add_patch(
        plt.Rectangle((x0, y0), x1 - x0, y1 - y0, fc="black", color="red", linewidth=0)
    )
plt.xlim(xl, xh)
plt.ylim(yl, yh)
fig.savefig(f"{name}.pdf")
