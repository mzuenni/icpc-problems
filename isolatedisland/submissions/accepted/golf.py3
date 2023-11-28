x=[]
for _ in range(int(input())):
 x+=list(zip(*[iter(input().split())]*2))
print(['no','yes'][any(a!=b for a,b in zip(*[iter(sorted(x)+[()])]*2))])
