//
//  Alteration.c
//
//  2015 Abel Carreras
//

#include "Alteration.h"

// All coordinates at the same time
double* AlterationFree(double* Coordinates, conditions params) {
    
    double RandomNumber;
    double *NewCoordinates = malloc(params.dimensions * sizeof(double));
    
    for (int i = 0; i < params.dimensions; i++){
        RandomNumber = RandomRange(-1, 1);
        NewCoordinates[i] =  Coordinates[i] + (params.factor * RandomNumber);
    }
    return NewCoordinates;
}

// Just one random coordinate each time
double* AlterationOneByOne(double* Coordinates, conditions params) {
    
    double RandomNumber;
    double *NewCoordinates = malloc(params.dimensions * sizeof(double));
    
    int choose = (int)RandomRange(0, params.dimensions);
    RandomNumber = RandomRange(-1, 1);
    NewCoordinates[choose] =  Coordinates[choose] + (params.factor * RandomNumber);
    
    return NewCoordinates;
}

// Just one random coordinate each time
double* AlterationBox2D(double* Coordinates, conditions params) {
    
    double nx = 10;
    double ny = 10;
    int natoms = 10;
    
    double RandomNumber;
    double *NewCoordinates = malloc(params.dimensions * sizeof(double));
    
    for (int i = 0; i < params.dimensions; i++){
        RandomNumber = RandomRange(-1, 1);
        NewCoordinates[i] =  Coordinates[i] + (params.factor * RandomNumber);
    }
    
    for (int i=0; i<natoms; i++){
        if (NewCoordinates[i] < 0)  NewCoordinates[i] += nx;
        if (NewCoordinates[i] > nx) NewCoordinates[i] -= nx;
        if (NewCoordinates[i+natoms] < 0)  NewCoordinates[i+natoms] += ny;
        if (NewCoordinates[i+natoms] > ny) NewCoordinates[i+natoms] -= ny;
    }
    
    return NewCoordinates;
}