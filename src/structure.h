// Struct declarations

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

using namespace std;

// For box dimensions
struct dimensions
{
    long double x_min;
    long double x_max;
    long double y_min;
    long double y_max;
    long double z_min;
    long double z_max;
};

// For storing position, velocity, acceleration
struct pva
{
    vector<vector<long double>> pos;
    vector<vector<long double>> vel;
    vector<vector<long double>> acc;
};    

// For storing energy and pressure
struct tpe
{
    long double total;
    long double potential;
    long double kinetic;
};    

#endif
