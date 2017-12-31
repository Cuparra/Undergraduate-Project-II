import differential_evolution
from differential_evolution import Population, diff_evolution, np, randint
import functions as fc

# variable: Cx,Cy of the n itens and R

LIMIT   = 0.000000000000001

class Packing:
	def __init__(self,nItens,maxIteration, rc,weight,radius):
		
		self.nIndividual    = 10*nItens
		self.nItens			= nItens    			# number of variables. The last variable is the R
		self.fit 			= np.zeros(10*nItens)	# array of individuals' fitness
		self.R 				= radius

		pop = Population(2*nItens, maxIteration, rc, weight, 10**(99), -10**(99) )
		(x,sol) = diff_evolution(pop,self.function)
		
		print sol, '\n'
		print x

	def function(self,x):

		R    	= self.R

		for i in range(self.nIndividual):

			total   = 0

			for j in range(self.nItens):

				k 		= 2*j
				force_x = 0
				force_y = 0
				dist  	= np.sqrt(x[i][k]**2 + x[i][k+1]**2) 
				temp 	= dist + 1 - R

				if(temp > 0):
					force_x = force_x - (x[i][k]/(dist+LIMIT))*temp
					force_y = force_y - (x[i][k+1]/(dist+LIMIT))*temp
				
				for t in range(self.nItens):

					l = 2*t
					dist_kt	= np.sqrt( (x[i][k] - x[i][l])**2 + (x[i][k+1]-x[i][l+1])**2 )
					temp	= 2 - dist_kt

					if(temp > 0 and j!=t ):
						#print 'ok!',
						force_x = force_x + ((x[i][k] - x[i][l] + LIMIT)/(dist_kt+LIMIT))*temp
						force_y = force_y + ((x[i][k+1] - x[i][l+1] + LIMIT)/(dist_kt+LIMIT))*temp
		
				x[i][k]		= x[i][k]   + force_x
				x[i][k+1]	= x[i][k+1] + force_y


			for j in range(self.nItens):

				k 		= 2*j
				temp 	= np.sqrt(x[i][k]**2 + x[i][k+1]**2) + 1 - R
				total 	= total + (0 if temp < 0 else temp)

				for t in range(j+1, self.nItens):

					l 		= 2*t
					temp	= 2 - np.sqrt( (x[i][k] - x[i][l])**2 + (x[i][k+1]-x[i][l+1])**2 )
					total 	= total + (0 if temp < 0 else temp)


			self.fit[i] = total

		return np.fabs(self.fit)

def main():

	P = Packing(10, 100, 0.6, 0.5,5)

if __name__ == "__main__": main()
