//
//  Random.c
//
//  2015 Abel Carreras
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initaialize random seed
static long random_seed_montecarlo;
void random_seed() {
    random_seed_montecarlo = clock();
    srand((int)random_seed_montecarlo);
}


// Algorithm 1  (Standard c random algorithm)
float ran1(){
    return (float)((double)rand()/((double)RAND_MAX));
}


// Random functions wrapper (Change function calling here to use other random funtion)
double RandomRange(double inf , double sup){
    return (double)ran1()*(sup-inf)+inf;
}
