#!/usr/bin/python3
import sys
import random
import math

n = int(sys.argv[1])
minx = int(sys.argv[2])
maxx = int(sys.argv[3])
ans = int(sys.argv[4])
random.seed(int(sys.argv[5]))

ds = [(0,1),(1,0),(0,-1),(-1,0)]

final_y = random.randint(minx, maxx);

prev_p = (random.randint(minx, maxx), random.randint(minx, maxx))
if (final_y < prev_p[1]):
	prev_d = (0, 1)
else:
	prev_d = (0, -1)

R = [[(prev_p[0], final_y), prev_p]]
for i in range(n-3-ans):
	d = random.choice(ds)
	s = random.randint(1, maxx - minx)
	p = (prev_p[0] + d[0]*s, prev_p[1] + d[1]*s)
	while ((d[0] == -prev_d[0] and d[1] == -prev_d[1])
			or p[0] < minx or p[1] < minx or p[0] > maxx or p[1] > maxx
			or (i == n-2-ans and ((d==(0,1) and final_y<p[1]) or (d==(0,-1) and final_y>p[1])))):
		d = random.choice(ds)
		s = random.randint(1, maxx-minx)
		p = (prev_p[0] + d[0]*s, prev_p[1]+d[1]*s)
	R.append([prev_p, p])
	prev_d = d
	prev_p = p
R.append([prev_p, (prev_p[0], final_y)])
R.append([(prev_p[0], final_y), R[0][0]])

if (ans):
	c = 0
	while c <= 1:
		c = 0
		ext_x = random.randint(minx, maxx)
		for r in R:
			if not ((r[0][0] < ext_x and r[1][0] < ext_x)
					or (r[0][0] > ext_x and r[1][0] > ext_x)):
				c += 1
	r1 = random.choice(R)
	while (r1[0][0] < ext_x and r1[1][0] < ext_x) or (r1[0][0] > ext_x and r1[1][0] > ext_x):
		r1 = random.choice(R)
	r2 = random.choice(R)
	while ((r2[0][0] < ext_x and r2[1][0] < ext_x) or (r2[0][0] > ext_x and r2[1][0] > ext_x)
		or r1[0][1]==r2[0][1]):
		r2 = random.choice(R)
	R.append([(ext_x, r1[0][1]), (ext_x, r2[0][1])])

for r in R:
	random.shuffle(r)
random.shuffle(R)

print(len(R))
for r in R:
	print(r[0][0], r[0][1], r[1][0], r[1][1])
