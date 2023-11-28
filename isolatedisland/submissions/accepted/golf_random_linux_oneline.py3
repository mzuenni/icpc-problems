print('yneos'[__import__('functools').reduce(lambda x,a:x^hash(a),zip(*[iter(open(0).read().split()[1:])]*2),0)==0::2])
