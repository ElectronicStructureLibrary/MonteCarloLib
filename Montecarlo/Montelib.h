//
//  Montelib.h
//  Montecarlo
//
//  Created by Abel Carreras on 2/6/15.
//  Copyright (c) 2015 Abel Carreras. All rights reserved.
//

#ifndef __Montecarlo__Montelib__
#define __Montecarlo__Montelib__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SIZEAVERAGE 200

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
}conditions;


//Define results structure
typedef struct {
    double *coordinates;
    double energy;
    double Cv;
    double AcceptationRatio;
}results;


//Function declaration
results MonteCarlo(double(*PotentialFunction)(double *Coordinates), conditions Conditions, FILE *LogFile);

double AcceptationAverage(int item);
double Random(double inf , double sup);
double RegulatorAcceptation(double acceptation, conditions Conditions);


//Properties functions
double Fluctuation(double Energy);

// Alteration functions definitions
double* Alteration1(double*, conditions);
double* Alteration2(double*, conditions);

#endif /* defined(__Montecarlo__Montelib__) */
