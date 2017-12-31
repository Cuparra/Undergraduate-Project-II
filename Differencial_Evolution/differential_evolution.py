import numpy as np
from numpy import copy, greater_equal , less, mean, std, where, amin, argmin
from numpy.random import rand, randint


# Each variable will have Cx, Cy, r.
# Where C = (Cx,C,y) is the coordenate of item's center and r its radius

class Population:
	def __init__(self,nVariables,maxIteration,rc,weight,h_num,l_num):

		self.nIndividuals	= 5*nVariables	# number of individuals
		self.nVariables		= nVariables    # number of variables
		self.h_num 			= h_num 		# highest number
		self.l_num 			= l_num         # lowest number
		self.weight 		= weight		# differential weight (mutation)
		self.rc 			= rc 			# recombination probability
		self.maxIteration	= maxIteration

		# Create randomly a list of individuals
		self.individuals 	= np.random.rand(self.nIndividuals,nVariables)*(h_num-l_num) + l_num



def diff_evolution(pop,function):

	maxIteration = pop.maxIteration
	nIndividuals = pop.nIndividuals
	nVariables   = pop.nVariables
	h_num  	     = pop.h_num
	l_num 		 = pop.l_num
	rc 		 	 = pop.rc
	w 			 = pop.weight
	x 			 = pop.individuals


	# Evaluate fathers' fitness
	fit = function(x)
	
	# counter
	count = 0

	best  = argmin(fit)

	while fit[best] != 0:
		
		# Create trial vectors
		#p1 = randint( nIndividuals, size = nIndividuals)
		best 	= argmin(fit)
		p2 		= randint( nIndividuals, size = nIndividuals)
		p3 		= randint( nIndividuals, size = nIndividuals)
		trial  	= x[best] + w*(x[p2] - x[p3])
	
		# Produce offsprings.
		# Each offspring's variable has rc% to be igual to its trial vector
		prob 		= rand(nIndividuals, nVariables)
		res  		= greater_equal(rc,prob)
		_res  		= less(rc,prob)
		offspring 	= res*trial + _res*x
		
		# Variables must be between h_num and l_num
		offspring[offspring > h_num] = h_num
		offspring[offspring < l_num] = l_num
		
		# Evaluate offsprings' fitness
		offFit = function(offspring)
		
 		# If fitness of offspring is lower than of its father, it becames its offspring.
		z 			= where(offFit<fit)
		x[z[0]] 	= offspring[z[0]]
		fit[z[0]]  	= offFit[z[0]]
		count = count + 1

	# Return the local minimim and its variables.
	best = np.argmin(fit)
	return (x[best],fit[best])