n,h=input().split()
hs=input().split()
hs+=[h]
j=0
o=2
for x in hs:
	c=int(h)-int(x)-j
	if c<0:
		o=0
	j=max(0,j+1 if c%2 else j-1)
print('impossible'[o:])
