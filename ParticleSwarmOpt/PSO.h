#ifndef PARTICLESWARMOPT_H
#define PARTICLESWARMOPT_H

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "Population.h"

#define NOTCHANGED      -1

#define MINIMIZATION     1
#define MAXIMAZATION     0

Particle *ExecuteSwarm(Swarm *, void (*)(Swarm *));

Particle *BestGlobalParticle(Swarm *);

//Population Size, Dimension Size, aceleration 1, aceleration 2, Highest Number, Lowerst Number, Number of Sessions
Swarm *InicializeSwarm(int , int, double, double , double , int );

void PrintSolution(Swarm *);

#endif
