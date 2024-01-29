x=0
for _ in[1]*int(input()):
 a,b=map(int,input().split())
 x=max(x,a*b*min(a,b))
print(x)
