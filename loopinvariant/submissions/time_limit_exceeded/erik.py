s, x = input(), 0
for i,c in enumerate(s):
  x += 1-2*(c==')')
  if x == 0 and s[i+1:]+s[:i+1] != s:
    print(s[i+1:]+s[:i+1])
    exit(0)
print("no")
