x=0
for a in zip(*[iter(open(0).read().split()[1:])]*2):x^=hash(a)
print('yneos'[x==0::2])
