__author__ = 'tiago'

from swarm import Swarm, np
from pso import*

class Packing:
	def __init__(self,sizeOfSwarm,sizeOfDimension,maxInt):
		
		self.nIndividuals	= sizeOfSwarm					# number of individuals
		self.nVariables		= sizeOfDimension    			# number of variables. The last variable is the R
		self.fit 			= np.zeros(self.nIndividuals)	# array of individuals' fitness
		self.lamb			= 10
		self.mult			= (10**(20))**(1.0/maxInt)

		nItens		= (sizeOfDimension-1)/2
		limit		= 4*np.ceil(np.sqrt(nItens))

		swarm 		= Swarm(sizeOfSwarm,sizeOfDimension,limit,-limit,maxInt)
		(x,fitness) = PSO( swarm ,self.function)
		
		print fitness
		print x


	def function(self,x):

		r    	= 1.0
		lamb	= self.lamb
		loop 	= (self.nVariables-1)/2

		for i in range(self.nIndividuals):

			total = 0

			for j in range(loop):

				k = 2*j
				result = np.sqrt(x[i][k]**2 + x[i][k+1]**2) + r - np.fabs(x[i][self.nVariables-1])

				if result > 0:
					total += result

				for t in range(loop-j-1):

					l = 2*(t+j+1)
					result = 4*r*r - (x[i][k] - x[i][l])**2 - (x[i][k+1]-x[i][l+1])**2
			
					if result > 0:
						total += result

			self.fit[i] = np.fabs(x[i][self.nVariables-1]) + self.lamb*total;

		self.lamb = self.mult*lamb;

		return np.fabs(self.fit)

def main():

    Packing(50,21,1000)

if __name__ == "__main__": main()
