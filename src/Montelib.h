//
//  Montelib.h
//  Copyright (c) 2015 Abel Carreras.
//

#ifndef __Montecarlo__Montelib__
#define __Montecarlo__Montelib__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Random.h"

// Define Size vectors used to do average
#define SIZEAVERAGE 1000


// Define conditions structure
typedef struct {
    double *coordinates;
    int dimensions;
    double factor;
    int numberofcycles;
    double temperature;
    double kb;
    int averagevalues;
    int takesample;
    double regulator;
    FILE* coordinatesfile;
    FILE* energyfile;
}conditions;


//Define results structure
typedef struct {
    double *coordinates;
    double energy;
    double Cv;
    double AcceptationRatio;
}results;


//Main MC function
results MonteCarlo(double(*PotentialFunction)(double *Coordinates),
                   double*(*AlterationFunction)(double *Coordinates, conditions),
                   conditions Params,
                   FILE*LogFile);

//Acceptation functions
double AcceptationAverage(int item);
double RegulatorAcceptation(double acceptation, conditions Conditions);


//Properties functions
double Fluctuation(double Energy);



#endif /* defined(__Montecarlo__Montelib__) */
