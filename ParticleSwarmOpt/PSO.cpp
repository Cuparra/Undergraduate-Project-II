#include "PSO.h"

void PrintSolution(Swarm *S){

    int i;
    int nVariables = S->nVariables;
    Particle *p    = S->bestParticle;

    printf("Solution = %.15lf\n", p->bestFit);
    
    for(i=0;i<nVariables;i++)
        printf("x[%d] = %.15lf\n",i,p->bestPosition[i]);

}

void Minimum(Swarm *S){

    int i;
    int idx             = 0;
    Particle *p         = S->particle;
    int nVariables      = S->nVariables;
    int SizeOfSwarm     = S->SizeOfSwarm;

    for(i=1;i<SizeOfSwarm;i++){

        if(p[i].bestFit < p[idx].bestFit)
            idx = i;
    }

    S->bestParticle = &p[idx];
}

double Mean(Swarm *S){

    int i;
    double mean     = 0;
    Particle *p     = S->particle;
    int SizeOfSwarm = S->SizeOfSwarm;

    for(i=0;i<SizeOfSwarm;i++)
        mean += p[i].bestFit;
    
    return ( (1.0*mean)/SizeOfSwarm);
}

void ConstructRing(Swarm *S){

    int i;
    int SizeOfNeighbor  = 2;
    Particle *particle  = S->particle;
    int SizeOfSwarm     = S->SizeOfSwarm;
    S->SizeOfNeighbor   = SizeOfNeighbor;


    for(i=0; i<SizeOfSwarm;i++)
        particle[i].neighbor = (int*)malloc(SizeOfNeighbor*sizeof(int));

    for(i=1; i<SizeOfSwarm - 1; i++){

        particle[i].neighbor[0] = i - 1;
        particle[i].neighbor[1] = i + 1;

    }

    particle[0].neighbor[0] = SizeOfSwarm - 1;
    particle[0].neighbor[1] = 1;

    particle[SizeOfSwarm - 1].neighbor[0] = 0;
    particle[SizeOfSwarm - 1].neighbor[1] = SizeOfSwarm - 2;

}

Swarm *InicializeSwarm(int SizeOfSwarm, int nVariables, double weight, double h_num, double l_num,  int maxIteration){

    int i,j;
    Swarm *S         = (Swarm*)malloc(sizeof(Swarm));
    S->SizeOfSwarm   = SizeOfSwarm;
    S->maxIteration  = maxIteration;
    S->nVariables    = nVariables;
    S->acc1          = 2.0;
    S->acc2          = 2.0;
    S->weight        = weight;
    S->h_num         = h_num;
    S->l_num         = l_num;

    S->particle             = (Particle*)calloc(SizeOfSwarm,sizeof(Particle));

    Particle *particle      = S->particle;

    for(i=0;i<SizeOfSwarm;i++){

        particle[i].currPosition    = (double*)calloc(nVariables, sizeof(double));
        particle[i].bestPosition    = (double*)calloc(nVariables, sizeof(double));
        particle[i].localPosition   = (double*)calloc(nVariables, sizeof(double));
        particle[i].velocity        = (double*)calloc(nVariables, sizeof(double));
        
        for(j=0;j<nVariables;j++){
                
                particle[i].currPosition[j]    = ((double) rand() / RAND_MAX)*(h_num-l_num) + l_num;
                particle[i].bestPosition[j]    = particle[i].currPosition[j];
                particle[i].localPosition[j]   = particle[i].currPosition[j];
                
        }
    }

    //ConstructRing(S);
    return S;
}

static inline void CopyPosition(double *Pos1, double *Pos2, int Size){

    while(Size--)
        Pos1[Size] = Pos2[Size];

}


void InicialSwarm(Swarm *S){

    int i,j;
    int nVariables      = S->nVariables;
    int SizeOfSwarm     = S->SizeOfSwarm;
    Particle *p         = S->particle;

    for(i=0;i<SizeOfSwarm;i++){

        p[i].bestFit      = p[i].currFit;
        p[i].localFit     = p[i].currFit;
        CopyPosition(p[i].bestPosition, p[i].currPosition,nVariables);
    }

}

Particle *ExecuteSwarm(Swarm *S, void (*EvaluateParticles)(Swarm *)){

    int i,j;
    int count           = 1;


    Particle *p         = S->particle;
    int SizeOfNeighbor  = S->SizeOfNeighbor;
    double h_num        = S->h_num;
    double l_num        = S->l_num;
    double c1           = S->acc1;
    double c2           = S->acc2;
    double w            = S->weight;
    double SizeOfSwarm  = S->SizeOfSwarm;
    double nVariables   = S->nVariables;
    int maxIteration    = S->maxIteration;

    EvaluateParticles(S);
    InicialSwarm(S);

    do{

        /*Set particle best position*/
        for(i=0;i<SizeOfSwarm;i++){

            if(p[i].currFit < p[i].bestFit){
                 
                p[i].bestFit  = p[i].currFit;
                CopyPosition(p[i].bestPosition, p[i].currPosition,nVariables);
            }
        }

        Minimum(S);

     /* Update the velocity and position*/
        for(i=0;i<SizeOfSwarm;i++){

            double *velocity    = p[i].velocity;
            double *x           = p[i].currPosition;
            double *b           = p[i].bestPosition;
            double *best        = S->bestParticle->bestPosition;

            for(j=0;j<nVariables;j++){

                double r1      = ( (double) rand()/RAND_MAX );
                double r2      = ( (double) rand()/RAND_MAX );

                velocity[j]    = w*velocity[j] + c1*r1*(b[j] - x[j]) + c2*r2*(best[j] - x[j]);
                x[j]           = x[j] + velocity[j];

                if(x[j] > h_num)
                    x[j] = h_num;
                else if(x[j] < l_num)
                    x[j] = l_num;
            }
        }

        /*Update count*/
        count += 1;
        //printf("%d: %.15lf\n", count, S->bestParticle->bestFit);
        /*Set the fitness of all particle*/
        EvaluateParticles(S);

    }while( count <=  maxIteration && S->bestParticle->bestFit >= 0.000000000000001);

    return S->bestParticle;
}
