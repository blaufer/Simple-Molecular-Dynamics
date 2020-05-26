#include "structure.h"

pva zero_velocity(int natoms, pva cur);

pva temp_velocity(int natoms, long double boltz, long double temp_vel,
    long double mass, pva cur);
