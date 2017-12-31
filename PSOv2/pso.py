__author__ = 'tiago'

from swarm import np
from numpy import argmin, random

def PSO(swarm,function):

    iteration       = 0
    maxInteraction  = swarm.maxInteraction
    #w               = swarm.weight
    particles       = swarm.particles
    sizeOfSwarm     = swarm.sizeOfSwarm
    l_num           = swarm.lowestNumber
    acc1            = swarm.accelaration1
    acc2            = swarm.accelaration2
    h_num           = swarm.highestNumber
    sizeOfDimension = swarm.sizeOfDimension

    neighbor        = particles.neighbor
    localFit        = particles.localFitness
    bestFit         = particles.bestFitness
    velocity        = particles.velocity
    best            = particles.bestPosition
    local           = particles.localPosition
    curr            = particles.currentPosition
    
    
    while(iteration < maxInteraction):
        
        w = 1.0*( 1.0*(1000 - iteration)/1000 ) + 0.2

        #Set the fitness of all particles
        currentFit = function( curr )

        #Set particle's best position
        for i in range(sizeOfSwarm):

            if currentFit[i] < bestFit[i]:
                bestFit[i]  = currentFit[i]
                best[i] = 0 + curr[i]

        #Set the neighborhood(local) best position
        for i in range(sizeOfSwarm):

            id = neighbor[i]
            bestId = id[np.argmin(bestFit[id])]
            localFit[i] = bestFit[bestId]
            local[i] = best[bestId]

        # Update the velocity and position of all particles
        r1 = np.random.rand(sizeOfSwarm,sizeOfDimension)
        r2 = np.random.rand(sizeOfSwarm,sizeOfDimension)

        velocity *= w
        velocity += acc1*r1*(best - curr) + acc2*r2*(local - curr)
        curr     += velocity

        curr[curr>h_num] = h_num
        curr[curr<l_num] = l_num

        iteration += 1

    # Return the best particle and its fitness    
    argmin  = np.argmin( bestFit )
    return ( bestFit[argmin], best[argmin])
