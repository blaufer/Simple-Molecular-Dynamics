#include <vector>

#include "structure.h"

pva lj_acc(int natoms, long double sigma, long double epsilon, 
    long double mass, long double cutoff, dimensions box, pva cur);

tpe lj_energy(int natoms, long double sigma, long double epsilon, 
    long double mass, long double cutoff, dimensions box, pva cur);
