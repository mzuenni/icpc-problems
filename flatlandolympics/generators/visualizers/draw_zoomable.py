#!/usr/bin/python3
import sys
import math

minSize = 1000
border = 10

with open(sys.argv[1]+'.in') as reader:
    line = [int(i) for i in reader.readline().split()]
    n = int(reader.readline())
    points = [tuple(map(int, line.split())) for line in reader]

    l = min(line[0], line[2], min(points, key = lambda p : p[0])[0])
    r = max(line[0], line[2], max(points, key = lambda p : p[0])[0])
    u = max(-line[1], -line[3], -max(points, key = lambda p : -p[1])[1])
    d = min(-line[1], -line[3], -min(points, key = lambda p : -p[1])[1])

    zoom = 1
    if r != l: zoom = max(zoom, minSize/(r-l))
    if u != d: zoom = max(zoom, minSize/(u-d))

    fixPrecision = lambda x : round(x, 5)
    dx = lambda x : fixPrecision((x - l) * zoom + border)
    dy = lambda y : fixPrecision((-y - d) * zoom + border)
    dxy = lambda xy : (dx(xy[0]), dy(xy[1]))

    with open(sys.argv[1]+".svg", 'w') as svg:
        svg.write(f'<svg version="1.1" height="{fixPrecision((u-d)*zoom+2*border)}" width="{fixPrecision((r-l)*zoom+2*border)}" xmlns="http://www.w3.org/2000/svg">');
        svg.write(f'  <line x1="{dx(line[0])}" x2="{dx(line[2])}" y1= "{dy(line[1])}" y2="{dy(line[3])}" stroke-linecap="round" stroke="red" stroke-width="7" vector-effect="non-scaling-stroke" />')
        for pos in points:
            svg.write(f'  <line x1="{dx(pos[0])}" x2="{dx(pos[0])+0.00001}" y1= "{dy(pos[1])}" y2="{dy(pos[1])}" stroke-linecap="round" stroke="black" stroke-width="5" vector-effect="non-scaling-stroke" />')
        svg.write(f'</svg>');
