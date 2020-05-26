#include "structure.h"

pva vverlet(int natoms, long double dt, long double sigma,
    long double epsilon, long double mass, long double cutoff, dimensions box,
    pva prev, pva cur);
