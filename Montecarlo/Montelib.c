//
//  Montelib.c
//  Copyright (C) 2015 Abel Carreras
//

#include "Montelib.h"
// Montecarlo library

results MonteCarlo(double(*PotentialFunction)(double *Coordinates),
                   conditions Conditions,
                   FILE *LogFile) {
    

    //Choosing Alteration function
    double*(*AlterationFunction)(double *Coordinates, conditions) = Alteration1;
    
    //Initializing Random function
    double RandomNumber;
    time_t t;
    srand((unsigned) time(&t));

    //Declarating & initaializating
    double* NewCoordinates;
    double NewEnergy;
    double Ratio;
    
    //Initial conditions
    double Acceptation = 0;
    double Cv = 0;
    double* Coordinates = Conditions.coordinates;
    double Energy = (*PotentialFunction)(Coordinates);

    
    printf("Start Montecarlo loop\n");

    for (int i = 0; i<Conditions.numberofcycles ; i++) {

        if (i % Conditions.takesample == 0) {
            // Statistical information
            Cv = Fluctuation(Energy)/(Conditions.kb*pow(Conditions.temperature,2));

            //Write in log file
            fprintf(LogFile, "%20.10f %20.10f %20.10f %20.10f", Energy, Acceptation, Cv, Conditions.factor);
            for (int i =0; i< Conditions.dimensions; i++) {
                fprintf(LogFile, " %20.10f",Coordinates[i]);
            }
            fprintf(LogFile,"\n");
        }
        
        // Acceptation Regulator
        Conditions.factor = RegulatorAcceptation(Acceptation, Conditions);
    
  
        // Metropolis algorithm
        NewCoordinates = (*AlterationFunction)(Coordinates, Conditions);
        NewEnergy = (*PotentialFunction)(NewCoordinates);

        if (Energy < NewEnergy) {
            Ratio = exp((Energy - NewEnergy)/(Conditions.temperature * Conditions.kb));
            RandomNumber = Random(0,1);

            if (Ratio < RandomNumber){
                free(NewCoordinates);
                Acceptation = AcceptationAverage(0);
                continue;
            }

        }
        free(Coordinates);
        Coordinates = NewCoordinates;
        Energy = NewEnergy;
        Acceptation = AcceptationAverage(1);
    }
    
    // Setting final results
    results Final = {Conditions.coordinates, Energy, Acceptation};
    Final.coordinates = Coordinates;
    Final.Cv = Cv;
    
    return Final;
}

// Acceptation
double AcceptationAverage(int item) {
    static int AcceptationVector[SIZEAVERAGE]={0};
    static int front=-1,rear=-1;
    static int Sum=0;
    if(front ==(rear+1)%SIZEAVERAGE) {
        
        Sum-=AcceptationVector[front];

        if(front==rear)
            front=rear=-1;
        else
            front = (front+1)%SIZEAVERAGE;
    }
    if(front==-1)
        front=rear=0;
    else
        rear=(rear+1)%SIZEAVERAGE;
    AcceptationVector[rear]=item;
    Sum+=AcceptationVector[rear];
    return ((double)Sum/SIZEAVERAGE);
}


// Acceptation Regulator
double RegulatorAcceptation(double acceptation, conditions Conditions) {
    return Conditions.factor * exp(( acceptation - 0.5)*Conditions.regulator);
}

// Specific heat at constant volume
double Fluctuation(double Energy) {
    static double EnergyVector[SIZEAVERAGE]={0};
    static int front=-1,rear=-1;
    static double Sum=0.0, Sum2=0.0;
    int Denominator;
    
    Denominator = rear+2;
    if(front ==(rear+1)%SIZEAVERAGE) {
        Denominator = SIZEAVERAGE;

        Sum-=EnergyVector[front];
        Sum2-=pow(EnergyVector[front],2);
        
        if(front==rear)
            front=rear=-1;
        else
            front = (front+1)%SIZEAVERAGE;
 
    }
    if(front==-1)
        front=rear=0;
    else
        rear=(rear+1)%SIZEAVERAGE;
    
    EnergyVector[rear]=Energy;
    Sum+=EnergyVector[rear];
    Sum2+=pow(EnergyVector[rear],2);

    return (((double)Sum2/Denominator) - pow((double)Sum/SIZEAVERAGE,2));
}


double Random(double inf , double sup){
    return ((double)rand()/((double)RAND_MAX))*(sup-inf)+inf ;
}


//////////////////////////////// Alteration functions //////////////////////////////

double* Alteration1(double* Coordinates, conditions params) {
    
    double RandomNumber;
    double *NewCoordinates = malloc(params.dimensions * sizeof(double));

    for (int i = 0; i < params.dimensions; i++){
        RandomNumber = Random(-1, 1);
        NewCoordinates[i] =  Coordinates[i] + (params.factor * RandomNumber);
    }
    return NewCoordinates;
}

double* Alteration2(double* Coordinates, conditions params) {
    
    double RandomNumber;
    double *NewCoordinates = malloc(params.dimensions * sizeof(double));
    
    for (int i = 0; i < params.dimensions; i++){
        RandomNumber = Random(-1, 1);
        NewCoordinates[i] =  Coordinates[i] + (params.factor * RandomNumber);
    }
    return NewCoordinates;
}