def get_prime_factors(n):
	factors = []
	if n == 0:
		return factors
	
	# Get the number of 2s that divide n
	while n%2 == 0:
		factors.append(2)
		n /= 2
	
	# n must be odd
	for i in range(3, int(sqrt(n)), 2):
		while n%i == 0:
			factors.append(i)
			n /= i
	
	# handle the case n is prime number greater than 2s
	if n > 2:
		factors.append(n)

	return factors
