#!/usr/bin/python3
import sys
import random as generator
from random import randrange as random

mod = 10**9+7
def powMod(x, exp):
	return pow(x, exp, mod)

def fib(x):
	if x < 2:
		return 1
	a = 1;
	b = 1;
	for i in range(x):
		a, b = b, a+b % mod
	return a

if len(sys.argv) > 2:
	generator.seed(sys.argv[2])

print(eval(sys.argv[1]) % mod)
