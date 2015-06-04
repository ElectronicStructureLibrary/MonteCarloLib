//
//  main.c
//  Copyright (C) 2015 Abel Carreras
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Montelib.h"


// Potential Functions declarations
double FakePotential(double* coordinates);
double FakePotential2(double* coordinates);


// main code
int main(int argc, const char *argv[]) {
    
    
///////////////////////// Initial conditions ////////////////////////
    int dimensions = 2;
    double *coordinates = malloc(dimensions * sizeof(double));
    
    //Initial coodinates
    for (int i =0; i<dimensions; i++) {
        coordinates[i] = 5.7;
    }
    
    conditions InitialConditions;
    InitialConditions.coordinates = coordinates;
    InitialConditions.dimensions = dimensions;
    InitialConditions.factor = 0.1;
    InitialConditions.numberofcycles = 500000;
    InitialConditions.kb = 0.0019872041; // kcal/(mol·K)
    InitialConditions.temperature = 100; // K
    InitialConditions.takesample = 20;
    InitialConditions.regulator = 0.001;
    
    
    //Print initial coodinates
    printf ("Initial Coordinates:");
    for (int i =0; i< InitialConditions.dimensions; i++) {
        printf (" %f",InitialConditions.coordinates[i]);
    }
    printf ("\n");

    
    //Opening log file
    FILE *LogFile;
    LogFile=fopen("/Users/abel/Programes/Montecarlo/Montecarlo/test.log", "w");
    
//////////////// Call Monte Carlo Function //////////////////////
    results Res = MonteCarlo(FakePotential, InitialConditions, LogFile);
    
    
///////////////////// Print final results ///////////////////////
    printf("Final energy %f\n",Res.energy);
    
    printf ("Final coordinates:");
    for (int i =0; i< InitialConditions.dimensions; i++) {
        printf (" %f",Res.coordinates[i]);
    }
    printf ("\n");
    
    printf("Specific heat (Cv): %f\n",Res.Cv);
    printf ("\n");

    
//////////////////////// Testing the potential in a file  ////////////////////
    FILE *fpot;
    fpot=fopen("/Users/abel/Programes/Montecarlo/Montecarlo/potenctial", "w");
    double x, y, Energy;
    for (int i =0; i< 100; i++) {
        for (int j =0; j< 100; j++) {
            x = i * 0.1 -5;
            y = j * 0.1 -5;
            coordinates[0] = x;
            coordinates[1] = y;
            Energy = FakePotential(coordinates);
            fprintf(fpot, "%20.10f %20.10f %20.10f\n", coordinates[0], coordinates[1], Energy);
        }
        fprintf(fpot, "\n");
    }
    printf ("\n");
    
    fclose(fpot);
//////////////////////////////////////////////////////////////////////////////
    
    return 0;
}


/////////////////////// Potential functions definitions ////////////////////////

double FakePotential(double* coordinates) {
    double total = 0.0;
    for (int i =0; i < 2; i++) {
        total += pow(coordinates[i],2);
    }
    return total;
}

double FakePotential2(double* coordinates) {
    double total = 0.0;
    for (int i =0; i < 3; i++) {
        total += pow(coordinates[i],2);
    }
    return total;
}

