__author__ = 'tiago'

from math import sqrt


def Topology(swarm, topology):
    if topology == 'mesh':
        Mesh(swarm)
    elif topology == 'ring':
        Ring(swarm)
    else:
        Mesh(swarm)


def Mesh(swarm):

    side = int(sqrt(swarm.sizeOfSwarm))

    swarm.particles.SetNeighboor(swarm.sizeOfSwarm, 4)
    neighbor = swarm.particles.neighbor

    for i in range(side):
        for j in range(side):

            pos = i * side + j

            if i - 1 < 0:
                neighbor[pos][0] = (side - 1) * side + j
            else:
                neighbor[pos][0] = (i - 1) * side + j

            if i + 1 > side - 1:
                neighbor[pos][1] = j
            else:
                neighbor[pos][1] = (i + 1) * side + j

            if pos - 1 < i * side:
                neighbor[pos][2] = (i + 1) * side - 1
            else:
                neighbor[pos][2] = pos - 1

            if pos + 1 > (i + 1) * side - 1:
                neighbor[pos][3] = i * side
            else:
                neighbor[pos][3] = pos + 1


def Ring(swarm):

    swarm.particles.SetNeighboor(swarm.sizeOfSwarm, 2)

    neighbor = swarm.particles.neighbor

    for i in range(swarm.sizeOfSwarm):
        neighbor[i][0] = i - 1
        neighbor[i][1] = i + 1

    neighbor[0][0] = swarm.sizeOfSwarm - 1
    neighbor[0][1] = 1

    neighbor[swarm.sizeOfSwarm - 1][0] = 0
    neighbor[swarm.sizeOfSwarm - 1][1] = swarm.sizeOfSwarm - 2