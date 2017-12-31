
#ifndef POPULATION_H
#define POPULATION_H

typedef struct PARTICLE{
    int *neighbor;
    double *velocity;
 
    double currFit;
    double localFit;
    double bestFit;

    double *currPosition;
    double *localPosition;
    double *bestPosition;
}Particle;

typedef struct SWARM{
    Particle *particle;
    Particle *bestParticle;
    int SizeOfNeighbor;
    int nVariables;
    int SizeOfSwarm;
    double acc1;
    double acc2;
    int maxIteration;
    double weight;
    double h_num;
    double l_num;
}Swarm;

#endif
