//
//  Random.c
//
//  2015 Abel Carreras
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initaialize random seed
static int random_seed_montecarlo;
const long key2;

void random_seed() {
    random_seed_montecarlo = (int)clock();
    srand((int)random_seed_montecarlo);
}


// Algorithm 1  (Standard c random algorithm)
float ran1(){
    return (float)((double)rand()/((double)RAND_MAX));
}

// Algorithm 2  (Very simple just for illustrating)
float ran2()
{
    long lim = 1234567898;
    static long a = 1;
    a = (a * 32719 + 3) % 32749;
    return (float)((a % lim) + 1)/(float)lim;
}

// Algorithm 3 (Very simple just for illustrating)
float ran3()
{
    long lim = 1234567898;
    static long a = 100001;
    a = (a * 125) % 2796203;
    return ((float)(a % lim) + 1)/(float)lim;
}


// Random functions wrapper (Change function calling here to use other random funtion)
double RandomRange(double inf , double sup){
    return (double)ran1()*(sup-inf)+inf;
}
