#######################################################################################

def get_factors_recv(n, cur_ret, ret):
	for i in range(2, int(ceil(sqrt(n)))):
		if n%i == 0:
			fact_arr = [i, n/i]
			# add the current value to current result
			cur_ret.extend(fact_arr)
			if sorted(cur_ret) not in ret:
				ret.append(sorted(cur_ret))
				# backtracking
				cur_ret = cur_ret[:-2]
				get_factors_recv(n/i, cur_ret + [i], ret)
			
	
def get_all_factors_product(n):
	if n == 0:
		return '';
	
	result = []
	# push the simple factor multiplier
	result.append([1, n])
	
	get_factors_recv(n, [], result)
	
	return result
	
###############################################################################################################

from math import sqrt
from math import ceil

def get_prime_factors(n):
	factors = []
	if n == 0:
		return factors
	
	# Get the number of 2s that divide n
	while n%2 == 0:
		factors.append(2)
		n /= 2
	
	# n must be odd
	for i in range(3, int(ceil(sqrt(n))), 2):
		while n%i == 0:
			factors.append(i)
			n /= i
	
	# handle the case n is prime number greater than 2s
	if n > 2:
		factors.append(n)

	return factors
	
def factor_combine(factors):
	reduce(lambda x, y: x*y, factors[1:])

def get_factors_product(n):
	factors = get_prime_factors(n)
	
	# return empty for no factors
	if not factors:
		return '';
	
	result = set()
	# push the simple factor multiplier
	result.add("1*{0}".format(n))
	result.add('*'.join(str(e) for e in factors))
