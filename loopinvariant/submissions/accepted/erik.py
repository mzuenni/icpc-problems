s = input()
t, i, x = s, 0, 0
while i < len(s):
  x, i = x+1-2*(s[i]==')'), i+1
  if not x: t, i = s[i:]+s[:i], len(s)
print([t,"no"][t==s])
