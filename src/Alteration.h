//
//  Alteration.h
//
//  2015 Abel Carreras.
//

#include "Montelib.h"

#ifndef MonteCarloLib_Alteration_h
#define MonteCarloLib_Alteration_h

// Alteration functions
double* AlterationFree(double* Coordinates, conditions Params);
double* AlterationOneByOne(double* Coordinates, conditions Params);
double* AlterationBox2D(double* Coordinates, conditions params);

#endif
