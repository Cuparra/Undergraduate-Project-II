#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "PSO.h"

#define LIMIT           0.000000000000001

#define P_SIZE          50
#define RADIUS          1.0
#define MAX(var)        var < 0 ? 0: var
#define ADJ(var)        var < LIMIT ? .001 : var


double R;
double conf = 0.5;
int n_itens     = 0;

double Fx[50];
double Fy[50];

void EvaluateParticles(Swarm *S){

    int i,j,t;
    Particle *p = S->particle;

    for(i=0;i<P_SIZE;i++){

        double total    = 0;
        double *x       = p[i].currPosition;

        for(j=0;j<n_itens;j++){

            Fx[j] = 0;
            Fy[j] = 0;

        }

        for(j=0;j<n_itens;j++){

            int k           = 2*j;
            double force_x  = 0;
            double force_y  = 0;
            double dist     =  sqrt(x[k]*x[k] + x[k+1]*x[k+1]);
            double temp     =  dist + RADIUS - R;

            if(temp > 0){

                Fx[j] += -conf*(x[k]/(dist+LIMIT))*temp;
                Fy[j] += -conf*(x[k+1]/(dist+LIMIT))*temp;
            }

            for(t=j+1; t<n_itens ;t++){

                int l = 2*t;
                double dist_kt  = sqrt( (x[k] - x[l])*(x[k] - x[l]) + (x[k+1]-x[l+1])*(x[k+1]-x[l+1]) );
                double temp1    = 2*RADIUS - dist_kt;
                
                if(temp1 > 0 && t!=j){
                
                    Fx[j]       += conf*((x[k] - x[l] + LIMIT)/(dist_kt+LIMIT))*temp1;
                    Fy[j]       += conf*((x[k+1] - x[l+1] + LIMIT)/(dist_kt+LIMIT))*temp1;
                    Fx[t]       -= Fx[j];
                    Fy[t]       -= Fy[j];
                }

            }
        }

        //Adjust the disk due to the forces
        for(j=0;j<n_itens;j++){
            
            int k   = 2*j;
            x[k]    = x[k]   + Fx[j];
            x[k+1]  = x[k+1] + Fy[j];
        }

        for(j=0;j<n_itens;j++){
            int k           = 2*j;
            total += MAX(sqrt(x[k]*x[k] + x[k+1]*x[k+1]) + RADIUS - R);

            for(t=j+1; t<n_itens ;t++){
                int l = 2*t;
                if(j!=t){
                    total += MAX(2*RADIUS - sqrt( (x[k] - x[l])*(x[k] - x[l]) + (x[k+1]-x[l+1])*(x[k+1]-x[l+1]) ));
                }
            }
        }

        p[i].currFit    = total;
    }

}


double get_mean(double *v){

    int i;
    double mean = 0;

    for(i=0;i<30;i++)
        mean += v[i];


    return (1.0*mean)/30;
}


double get_std_dev(double *v, double mean){

    int i;
    double std = 0;

    for(i=0;i<30;i++)
        std += (v[i] - mean)*(v[i] - mean);


    return sqrt( (1.0*std)/30 );
}


void create_stat(){

    int j;

    FILE *fptr = fopen("Result_PSO.txt","w");

    clock_t t;
    double Time[30];
    double err[30];
    double vec[30];
    double trial[30];

    for(n_itens=1; n_itens<51; n_itens++){
       
        time_t t;
        srand((unsigned) time(&t));

        printf("Number of Itens %d:\n", n_itens);
        fprintf(fptr, "Number of Itens %d:\n", n_itens);

        for(j=1;j<31;j++){

            trial[j-1]      = 0;
            Time[j-1]       = 0;
            double local_R  = sqrt(n_itens);
            Swarm *S        = InicializeSwarm(P_SIZE,2*n_itens,0.3,pow(10,99),-pow(10,99), 80*n_itens);

            R               = local_R + 0.05*local_R;

            do{
                
                vec[j-1]        = R;
                trial[j-1]      += 1;
                t = clock();
                err[j-1]        = ExecuteSwarm(S,EvaluateParticles)->bestFit;
                Time[j-1]       += ( (double) clock() - t)/CLOCKS_PER_SEC;
                double adjust   = ADJ(0.01*err[j-1]*local_R);
                //R               = R + adjust;
                R               = R + 0.05*local_R;
        
            }while(err[j-1] > 0.000000000000001 && trial[j-1] <= 1000);

            printf("Iteration[%d]: %.15lf, error: %.15lf, trials: %.1lf, time: %.15lf\n", j, vec[j-1], err[j-1], trial[j-1], Time[j-1]);
            fprintf(fptr, "Iteration[%d]: %.15lf, error: %.15lf, trials: %.1lf, time: %.15lf\n", j, vec[j-1], err[j-1], trial[j-1], Time[j-1]);
        }

        double mean     = get_mean(vec);
        double std_dev  = get_std_dev(vec,mean);

        fprintf(fptr, "R\n");
        fprintf(fptr, "Mean: %.15lf\n", mean);
        fprintf(fptr, "Std_dev: %.15lf\n", std_dev);
        printf("R: MEAN = %.15lf STD_DEV = %.15lf\n ",mean,std_dev);

        mean     = get_mean(err);
        std_dev  = get_std_dev(err,mean);

        fprintf(fptr, "ERROR\n");
        fprintf(fptr, "Mean: %.15lf\n", mean);
        fprintf(fptr, "Std_dev: %.15lf\n", std_dev);
        printf("ERROR: MEAN = %.15lf STD_DEV = %.15lf\n",mean,std_dev);

        mean     = get_mean(trial);
        std_dev  = get_std_dev(trial,mean);

        fprintf(fptr, "TRIAL\n");
        fprintf(fptr, "Mean: %.15lf\n", mean);
        fprintf(fptr, "Std_dev: %.15lf\n", std_dev);
        printf("TRIAL: MEAN = %.15lf STD_DEV = %.15lf\n",mean,std_dev);

        mean     = get_mean(Time);
        std_dev  = get_std_dev(Time,mean);

        fprintf(fptr, "TIME\n");
        fprintf(fptr, "Mean: %.15lf\n", mean);
        fprintf(fptr, "Std_dev: %.15lf\n\n", std_dev);
        printf("TIME: MEAN = %.15lf STD_DEV = %.15lf\n\n",mean,std_dev);

    }


}

int main(){

    create_stat();

    return 0;
}
