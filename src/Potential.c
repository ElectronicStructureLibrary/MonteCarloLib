//
//  Potential.c
//
//  2015 Abel Carreras
//

#include "Potential.h"
#include <math.h>


double HarmonicPotential2D(double* coordinates) {
    double k = 1;
    
    double Energy = 0.0;
    for (int i =0; i < 2; i++) {
        Energy += k * pow(coordinates[i],2);
    }
    return Energy;
}

double Sinusoidal3D(double* coordinates) {
    double Lenght= 1;
    double Hight = 20;
    
    double Energy = 0.0;
    for (int i =0; i < 3; i++) {
        Energy += Hight*sin(coordinates[i]/Lenght);
    }
    return Energy;
}

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
double LennarJonnes2D(double* coordinates) {
    
    // Box size
    double nx = 10;
    double ny = 10;
    
    int natoms = 10;
    double cutoff = 10;
    
    //LJ Parameters
    double eps = 0.2;
    double sigma = 3;
    
    double Energy = 0.0;
    for (int i=0; i<natoms; i++){
        for (int j =0; j<i; j++){

            double xdis = MIN(pow(MAX(coordinates[i],coordinates[j])- MIN(coordinates[i],coordinates[j]),2),pow(MAX(coordinates[i],coordinates[j]) - MIN(coordinates[i],coordinates[j]) +nx,2));
            double ydis = MIN(pow(MAX(coordinates[i+natoms],coordinates[j+natoms]) - MIN(coordinates[i+natoms],coordinates[j+natoms]),2),pow(MAX(coordinates[i+natoms],coordinates[j+natoms]) - MIN(coordinates[i+natoms],coordinates[j+natoms]) +ny,2));
            
            double distance = sqrt(xdis*ydis);
            
            if (distance < cutoff)
                Energy += 4.0*eps*(pow(sigma/distance,12) - pow(sigma/distance,6));
        }
    }
    return Energy;
}
