'''
Just to explain newton method.

f(xn+delta) = f(xn) + f'(xn)delta + (1/2)f''(xn)*delta^2 + ...

keep first order, f(xn+delta) = f(xn) + f'(xn)*delta = 0

delta = - f(xn)/f'(xn)

so Xn+1 = Xn - f(Xn)/f'(Xn), if f(Xn) = X^2 - n, f'(x)=2x

Xn+1 = Xn - (Xn^2 - n)/2Xn = Xn/2 + n/2Xn
'''
#http://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi

def sq(x):
	z = 1
	y = 0
	while int(y) != int(z):
		y = z
		z = float(x)/2/y + y/2
	return y
