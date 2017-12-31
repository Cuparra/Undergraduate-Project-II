__author__ = 'tiago'

import numpy as np
from topology import*
INF = 2147483647.0

class Swarm:

    def __init__(self,sizeOfSwarm,sizeOfDimension,h_num,l_num,maxInt):

        self.sizeOfDimension    = sizeOfDimension
        self.sizeOfSwarm        = sizeOfSwarm
        self.highestNumber      = h_num
        self.lowestNumber       = l_num
        self.accelaration1      = 2.0
        self.accelaration2      = 2.0
        self.maxInteraction     = maxInt
        self.weight             = 0.6
        self.particles          = Particles(self)
        Topology(self,'ring')


class Particles:

    def __init__(self,swarm):

        sizeofSwarm     = swarm.sizeOfSwarm
        l_num           = swarm.lowestNumber
        h_num           = swarm.highestNumber
        sizeOfDimension = swarm.sizeOfDimension

        self.currentFitness     = np.zeros( sizeofSwarm , np.float64)
        self.bestFitness        = np.full( sizeofSwarm, INF, np.float64)
        self.localFitness       = np.full( sizeofSwarm, INF, np.float64)

        self.localPosition      = np.zeros( (sizeofSwarm,sizeOfDimension), np.float64)
        self.bestPosition       = np.zeros( (sizeofSwarm,sizeOfDimension), np.float64)
        self.velocity           = np.zeros( (sizeofSwarm,sizeOfDimension), np.float64)
        self.currentPosition    = np.random.uniform(l_num,h_num,(sizeofSwarm,sizeOfDimension))

    def SetNeighboor(self,sizeOfSwarm,sizeOfNeighboor):

        self.neighbor = np.zeros( (sizeOfSwarm,sizeOfNeighboor), np.int32)





