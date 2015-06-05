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
double ran1(){
    return (double)((double)rand()/((double)RAND_MAX));
}

// Algorithm 2  (Very simple just for illustrating)
double ran2()
{
    long lim = 1234567898;
    static long a = (long)&random_seed_montecarlo;
    a = (a * 32719 + 3) % 32749;
    return (double)((a % lim) + 1)/(double)lim;
}

// Algorithm 3 (Very simple just for illustrating)
double ran3()
{
    long lim = 1234567898;
    static long a = (long)&random_seed_montecarlo;
    a = (a * 125) % 2796203;
    return ((double)(a % lim) + 1)/(double)lim;
}

// Algorithm 4 (Very simple just for illustrating)
double ran4()
{
    long lim = 1234567898;
    static long a = (long)&random_seed_montecarlo;
    a = (((a * 214013L + 2531011L) >> 16) & 32767);
    
    return (double)((a % lim) + 1)/(double)lim;
}


// Random functions wrapper (Change function calling here to use other random funtion)
double RandomRange(double inf , double sup){
    return (double)ran1()*(sup-inf)+inf;
}
