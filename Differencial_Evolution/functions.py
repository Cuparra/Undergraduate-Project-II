import numpy as np


n = 40     # number of variables
d = 1./n

def ackley(x):
	
	arg0 = np.sum(x**2, axis = 1)
	arg1 = -0.2 * np.sqrt(d * arg0)
	arg2 = d * np.sum( np.cos(2.0*np.pi*x), axis = 1 )

	return -20. * np.exp(arg1) - np.exp(arg2) + 20. + np.e


def schwefel(x):

	arg0 = np.sin( np.sqrt( np.absolute(x) ) )
	return 418.9829*n - np.sum( x*arg0, axis = 1)


def drop_wave(x):

	arg0 = 1 + np.cos(12*np.sqrt(x[:,0]**2 + x[:,1]**2))
	arg1 = 0.5*(x[:,0]**2 + x[:,1]**2) + 2
	return -(arg0/arg1)

def rastrigin(x):

	arg0 = 10*np.cos(2*np.pi*x)
	return 10*n + np.sum(x**2 - arg0, axis = 1)