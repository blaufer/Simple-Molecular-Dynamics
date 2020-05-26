#include <vector>
#include <cmath>
#include <iostream>

#include "structure.h"
#include "vectors.h"

using namespace std;

pva lj_acc(int natoms, long double sigma, long double epsilon,
    long double mass, long double cutoff, dimensions box, pva cur)
{
    int i, j, k;
    long double x, y, z, r, f, or14, or8; // f_c;
    vector<long double> temp;
    vector<vector<long double>> acc, force;

    // Box dimensions
    long double x_dim = box.x_max - box.x_min;
    long double y_dim = box.y_max - box.y_min;
    long double z_dim = box.z_max - box.z_min;

    // Initialize force and acc to zero
    force = zeroes(natoms, 3);
    acc = zeroes(natoms, 3);
    /*
    for (i=0; i < 3; i++)
    {
        temp.push_back(0.0);
    }
    for (i=0; i < natoms; i++)
    {
        force.push_back(temp);
        acc.push_back(temp);
    }
    */

    // Constants
    long double aa1 = 4.0 * epsilon * pow(sigma,12);
    long double bb1 = 4.0 * epsilon * pow(sigma,6);
    long double csq = pow(cutoff,2);

    for (i=0; i < natoms-1; i++)
    {
        for (j=i+1; j < natoms; j++)
        {
            x = cur.pos[i][0] - cur.pos[j][0];
            y = cur.pos[i][1] - cur.pos[j][1];
            z = cur.pos[i][2] - cur.pos[j][2];

            x -= (x_dim * roundf(x/x_dim));
            y -= (y_dim * roundf(y/y_dim));
            z -= (z_dim * roundf(z/z_dim));

            r = pow(x,2) + pow(y,2) + pow(z,2);

            if (r < csq)
            {
                or14 = 1.0 / pow(r,7);
                or8 = 1.0 / pow(r,4);
                f = -12 * aa1 * or14 + 6.0 * bb1 * or8;

                force[i][0] -= f*x;
                force[j][0] += f*x;
                force[i][1] -= f*y;
                force[j][1] += f*y;
                force[i][2] -= f*z;
                force[j][2] += f*z;
            }
        }
    }
   
    for (i=0; i < natoms; i++)
    {
        for (j=0; j < 3; j++)
        {
            acc[i][j] = force[i][j] / mass;
        }
    }
    
    cur.acc = acc;

    return cur;
}

tpe lj_energy(int natoms, long double sigma, long double epsilon,
    long double mass, long double cutoff, dimensions box, pva cur)
{
    int i, j, k;
    long double x, y, z, r, pe, ke;
    tpe energy;

    // Box dimensions
    long double x_dim = box.x_max - box.x_min;
    long double y_dim = box.y_max - box.y_min;
    long double z_dim = box.z_max - box.z_min;

    // Constants
    long double s6 = pow(sigma,6);
    long double s12 = pow(sigma,12);
    long double csq = pow(cutoff,2);

    pe = 0.0;
    for (i=0; i < natoms-1; i++)
    {
        for (j=i+1; j < natoms; j++)
        {
            x = cur.pos[i][0] - cur.pos[j][0];
            y = cur.pos[i][1] - cur.pos[j][1];
            z = cur.pos[i][2] - cur.pos[j][2];

            x -= (x_dim * roundf(x/x_dim));
            y -= (y_dim * roundf(y/y_dim));
            z -= (z_dim * roundf(z/z_dim));

            r = pow(x,2) + pow(y,2) + pow(z,2);

            if (r < csq)
            {
                pe += 4 * epsilon * ((s12/pow(r,6)) -(s6/pow(r,3)));
            }
        }
    }

    ke = 0.0;
    for (i=0; i < natoms; i++)
    {
        ke += 0.5 * mass * (pow(cur.vel[i][0],2) + pow(cur.vel[i][1],2) 
            + pow(cur.vel[i][2],2));
    }
    
    energy.total = pe + ke;
    energy.potential = pe;
    energy.kinetic = ke;

    return energy;
}
