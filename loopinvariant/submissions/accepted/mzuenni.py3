s=input()
i=d=0
for c in s:
	d+=c<')'
	i+=1
	if 2*d==i:
		break
t=s[i:]+s[:i]
print(t if s!=t else'no')
