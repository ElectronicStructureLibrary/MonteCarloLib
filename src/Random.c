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
    return (float)rand();
}

// Algorithm 2
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

float ran2(){
    long* idum = &random_seed_montecarlo;
    long k;
    float ans;
    
    *idum ^= MASK;
    k = (*idum)/IQ;
    *idum =IA*(*idum-k*IQ)-IR*k;
    if (*idum < 0) *idum += IM;
    ans = AM*(*idum);
    *idum ^=MASK;
    return ans;
}


#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

// Algorithm 3
float ran3() {
    
    long* idum = &random_seed_montecarlo;
    static int inext,inextp; static long ma[56]; static int iff=0;
    long mj,mk;
    int i,ii,k;
    if (*idum < 0 || iff == 0) {
        iff=1;
        mj=labs(MSEED-labs(*idum));
        mj %= MBIG;
        ma[55]=mj;
        mk=1;
        for (i=1;i<=54;i++) { ii=(21*i) % 55;
            ma[ii]=mk;
            mk=mj-mk;
            if (mk < MZ) mk += MBIG; mj=ma[ii];
        }
        for (k=1;k<=4;k++)
            for (i=1;i<=55;i++) {
                ma[i] -= ma[1+(i+30) % 55];
                if (ma[i] < MZ) ma[i] += MBIG;
                }
        inext=0;
        inextp=31;
        *idum=1;
        }
    if (++inext == 56) inext=1;
    if (++inextp == 56) inextp=1;
    mj=ma[inext]-ma[inextp];
    if (mj < MZ) mj += MBIG;
    ma[inext]=mj;
    return mj*FAC;
}


// Random functions wrapper (Change function calling here to use other random funtion)
double RandomRange(double inf , double sup){
    return ran3()*(sup-inf)+inf;
}
