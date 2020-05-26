#include "structure.h"

long double calc_temperature(tpe energy, int natoms, long double boltz);

tpe calc_pressure(int natoms, long double sigma, long double epsilon,
    long double mass, long double cutoff, dimensions box, pva cur, tpe energy);
