x=0
for _ in range(int(input())):
 a,b,c,d=input().split()
 #hash is salted => randomly map points to integers
 #=> xor is 0 iff all points appear even number of times
 x^=hash((a,b))^hash((c,d))
print(['no','yes'][x!=0])
