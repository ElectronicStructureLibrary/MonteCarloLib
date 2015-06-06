//
//  example2.c
//  MonteCarloLib
//  Copyright (C) 2015 Abel Carreras
//
//   This is an example to how to run the MonteLib library for a simple case
//   This example runs a MC simulation of three independent rotors rotating along
//   a hindered axis simulated by a sinusoidal potential. 
//
//   Potential : 3D Sinusoidal
//   Alteration: One rotor each time alteration


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Load library header files
#include "Montelib.h"
#include "Random.h"
#include "Alteration.h"
#include "Potential.h"


// main code
int main(int argc, const char *argv[]) {
    
    ///////////////////////// Initial conditions ////////////////////////
    int dimensions = 2;
    
    random_seed();
    //Initial coodinates (Random)
    double *coordinates = malloc(dimensions * sizeof(double));
    for (int i =0; i<dimensions; i++) {
        coordinates[i] = i*M_PI+RandomRange(-0.1, 0.1) ;
    }
    
    //Opening log file
    FILE *LogFile, *Energyfile, *CoordinateFile;
    LogFile=fopen("/Users/abel/Programes/MonteCarloLib/example/test.log", "w");
    CoordinateFile=fopen("/Users/abel/Programes/MonteCarloLib/example/coordinates.out", "w");
    Energyfile=fopen("/Users/abel/Programes/MonteCarloLib/example/energy.out", "w");
    
    
    conditions InitialConditions;
    InitialConditions.coordinates = coordinates;
    InitialConditions.dimensions = dimensions;
    InitialConditions.factor = 0.1;
    InitialConditions.numberofcycles = 1000000;
    InitialConditions.kb = 0.0019872041; // kcal/(mol·K)
    InitialConditions.temperature = 1000; // K
    InitialConditions.takesample = 50;
    InitialConditions.regulator = 0.001;
    
    InitialConditions.coordinatesfile = CoordinateFile;
    InitialConditions.energyfile = Energyfile;
    
    
    //Print initial coodinates
    printf ("Initial Coordinates:");
    for (int i =0; i< InitialConditions.dimensions; i++) {
        printf (" %f",InitialConditions.coordinates[i]);
    }
    printf ("\n");
    
    
    printf("Initial energy: %f\n",Sinusoidal3D(InitialConditions.coordinates));
    
    //////////////// Call Monte Carlo Function //////////////////////
    
    
    results Res = MonteCarlo(Sinusoidal3D, AlterationOneByOne, InitialConditions, LogFile);
    
    
    ///////////////////// Print final results ///////////////////////
    
    fclose(CoordinateFile);
    fclose(Energyfile);
    fclose(LogFile);
    
    
    printf("Final energy %f\n",Res.energy);
    
    printf ("Final coordinates:");
    for (int i =0; i< InitialConditions.dimensions; i++) {
        printf (" %f",Res.coordinates[i]);
    }
    printf ("\n");
    
    printf("Final specific heat (Cv): %f\n",Res.Cv);
    printf ("\n");
    
    
    return 0;
}