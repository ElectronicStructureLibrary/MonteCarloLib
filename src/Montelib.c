//
//  Montelib.c
//  Copyright (C) 2015 Abel Carreras
//

#include "Montelib.h"

results MonteCarlo(double(*PotentialFunction)(double *Coordinates),
                   double*(*AlterationFunction)(double *Coordinates, conditions),
                   conditions Params,
                   FILE *LogFile) {
    
    //Random initaialization
    random_seed();
    
    //Initializing Random function
    double RandomNumber;
    
    //Declarating & initaializating
    double* NewCoordinates;
    double NewEnergy;
    double Ratio;
    
    //Initial conditions
    double Acceptation = 0;
    double Cv = 0;
    double* Coordinates = Params.coordinates;
    double Energy = (*PotentialFunction)(Coordinates);

    
    fprintf(LogFile,"Starting Monte Carlo\n");
    fprintf(LogFile,"Temperature: %f\n", Params.temperature);
    fprintf(LogFile,"Number of cycles: %d\n", Params.numberofcycles);

    for (int i = 0; i<Params.numberofcycles ; i++) {

        if (i % Params.takesample == 0) {
            // Statistical information
            Cv = Fluctuation(Energy)/(Params.kb*pow(Params.temperature,2));

            // Write to file (if exist)

            if (Params.coordinatesfile != NULL) {
                for (int i =0; i< Params.dimensions; i++) {
                    fprintf(Params.coordinatesfile, " %20.10f",Coordinates[i]);
                }
                fprintf(Params.coordinatesfile, "\n");
            }
            
            if (Params.energyfile != NULL) {
                fprintf(Params.energyfile, "%20.10f %20.10f %20.10f %20.10f\n", Energy, Acceptation, Cv, Params.factor);
            }
        }
        
        
        // Acceptation Regulator
        Params.factor = RegulatorAcceptation(Acceptation, Params);
    
  
        // Metropolis algorithm
        NewCoordinates = (*AlterationFunction)(Coordinates, Params);
        NewEnergy = (*PotentialFunction)(NewCoordinates);

        if (Energy < NewEnergy) {
            Ratio = exp((Energy - NewEnergy)/(Params.temperature * Params.kb));
            RandomNumber = RandomRange(0,1);

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
    results Final = {Params.coordinates, Energy, Acceptation};
    Final.coordinates = Coordinates;
    Final.Cv = Cv;
 
    fprintf(LogFile,"Monte Carlo finished\n");

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
