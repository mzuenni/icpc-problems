#!/usr/bin/python3
import svgwrite
import sys
import math

size = 1000
border = 10

with open(sys.argv[1]+'.in') as reader:
    line = [int(i) for i in reader.readline().split()]
    n = int(reader.readline())
    points = [tuple(map(int, line.split())) for line in reader]

    l = min(line[0], line[2], min(points, key = lambda p : p[0])[0])
    r = max(line[0], line[2], max(points, key = lambda p : p[0])[0])
    u = max(-line[1], -line[3], -max(points, key = lambda p : -p[1])[1])
    d = min(-line[1], -line[3], -min(points, key = lambda p : -p[1])[1])

    #(r-l)*zoom<=size-2*border
    zoom = (size-2*border)/max(r-l, u-d)
    stroke = math.log(zoom+2,2)

    fixPrecision = lambda x : round(x, 5)
    dx = lambda x : fixPrecision((x - l) * zoom + border)
    dy = lambda y : fixPrecision((-y - d) * zoom + border)
    dxy = lambda xy : (dx(xy[0]), dy(xy[1]))
    
    document = svgwrite.Drawing(filename = sys.argv[1]+".svg", size=(size, size))
    document.add(document.line(dxy((line[0], line[1])), dxy((line[2], line[3])), stroke="red", stroke_width=fixPrecision(1.1*stroke)))
    for pos in points:
        document.add(document.circle(dxy(pos), r=fixPrecision(0.5*stroke), fill="black"))
    document.save()
