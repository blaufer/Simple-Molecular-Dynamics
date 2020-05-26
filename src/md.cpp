#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

// My modules
#include "structure.h"
#include "vectors.h"
#include "lattice.h"
#include "lj.h"
#include "verlet.h"
#include "dump.h"
#include "log.h"
#include "temp_press.h"
#include "velocity.h"

using namespace std;

//---------------------------------------------------------

int main(int argc, char **argv)
{
    /* 
    // Typically use this one (remember to uncomment line 53,
    // and change 59 to the correct number of steps)
    // Get command line argument
    if (argc != 2)
    {
        cout << "You need to give a temperature" << endl;
        exit(1);
    }

    long double vel_temperature = atof(argv[1]);
    */

    // Used for question 11
    if (argc != 3)
    {
        cout << "You need to give a temperature and lattice parameter" << endl;
        exit(1);
    }

    long double vel_temperature = atof(argv[1]);
    long double a = atof(argv[2]);

    // Constants
    long double epsilon = 1.650e-21;
    long double sigma = 0.3400; // nanometers
    long double mass = 39.948; // amu
    long double boltz = 1.987204e-3; // Boltzmann constant in kcal/(mol*K)
    long double cutoff = 4 * sigma;
    //long double a = 2.0*pow(2.0,1.0/6.0)*0.34/sqrt(2.0) * 10.0;

    // Other
    const long double dim = 3; // 3-dimensional
    int step = 0;
    long double dt = 10.0; // Femtoseconds
    int steps = 0; // Number of steps to run
    int output = 100;
    
    //long double vel_temperature = 40.0;
    dimensions box = {-3.5, 3.5, -3.5, 3.5, -3.5, 3.5};
    const string latt = "fcc"; // Lattice to create

    // Create vectors to hold positions, velocities, accelerations
    pva prev, cur;

    // Create holder for energy, pressure, temperature
    tpe energy, pressure;
    long double temperature;

    // For loop
    int i;

    //----- Create positions ------------------------------
    cur = lattices(latt, box, a, cur);
    // Small 2 atom sim
    //cur.pos = {{0.0,0.0,0.0},{a,0.0,0.0}};
    
    // Get number of atoms
    int natoms = cur.pos.size();

    // Remove center of mass
    cur = center_of_mass(natoms, box, cur);

    //----- Convert to lj units ---------------------------
    epsilon *= 6.022e23 / 4184.0;
    sigma *= 10.0;
    dt /= (1.0e-10 * sqrt(1.66054e-27 * 6.022e23 / 4184.0) * 1.0e15);
    cutoff *= 10.0;
    
    // Update box dimensions to be in angstroms instead of lattice units
    box = {box.x_min*a, box.x_max*a, box.y_min*a, box.y_max*a, 
        box.z_min*a, box.z_max*a};

    //----- Initial acceleration --------------------------
    cur = lj_acc(natoms, sigma, epsilon, mass, cutoff, box, cur);

    //----- Initial velocities ----------------------------
    if (vel_temperature == 0.0)
        cur = zero_velocity(natoms, cur);
    else
        cur = temp_velocity(natoms, boltz, vel_temperature, mass, cur);

    //----- Initial energies ------------------------------
    energy = lj_energy(natoms, sigma, epsilon, mass, cutoff, box, cur);

    //----- Initial temp and press ------------------------
    temperature = calc_temperature(energy, natoms, boltz);
    pressure = calc_pressure(natoms, sigma, epsilon, mass, cutoff, box,
        cur, energy);

    //----- Write dump/log --------------------------------
    write_dump(cur, natoms, step, box);
    write_log(cur, step, dt, energy, temperature, pressure);

    //----- Integrate -------------------------------------
    for (i=1; i < steps+1; i++)
    {
        // Copy arrays
        prev.pos = vector_copy(cur.pos);
        prev.vel = vector_copy(cur.vel);
        prev.acc = vector_copy(cur.acc);
        
        // Zero cur arrays
        cur.pos = zeroes(natoms, 3);
        cur.vel = zeroes(natoms, 3);
        cur.acc = zeroes(natoms, 3);

        cur = vverlet(natoms, dt, sigma, epsilon, mass, cutoff, box,
            prev, cur);
    
        // Remove center of mass
        cur = center_of_mass(natoms, box, cur);
        
        if (i % output == 0)
        {
            energy = lj_energy(natoms, sigma, epsilon, mass, cutoff, box, cur);
            temperature = calc_temperature(energy, natoms, boltz);
            pressure = calc_pressure(natoms, sigma, epsilon, mass, cutoff, box,
                cur, energy);
            write_dump(cur, natoms, i, box);
            write_log(cur, i, dt, energy, temperature, pressure);
        }
    }

    //----- End Program -----------------------------------
    return 0;
}
