h=int(input().split()[1])
b,c=h,1
for i in input().split()+[h]:
	j=b-int(i)
	c&=j>=0
	b=min(h,b+1-2*j%4)
print("impossible"[2*c:])
