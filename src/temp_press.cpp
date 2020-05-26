#include <vector>
#include <cmath>

#include "structure.h"

long double calc_temperature(tpe energy, int natoms, long double boltz)
{
    long double temperature;

    temperature = 2 * energy.kinetic / ((3 * natoms - 3) * boltz);

    return temperature;
}

tpe calc_pressure(int natoms, long double sigma, long double epsilon,
    long double mass, long double cutoff, dimensions box, pva cur, tpe energy)
{
    int i, j, k;
    long double x, y, z, r, pp, kp, conv;
    tpe pressure;

    float s6 = pow(sigma, 6);
    float s12 = pow(s6, 2);

    // Box dimensions
    long double x_dim = box.x_max - box.x_min;
    long double y_dim = box.y_max - box.y_min;
    long double z_dim = box.z_max - box.z_min;
    long double volume = x_dim * y_dim * z_dim;

    pp = 0.0;
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

             r = sqrt(pow(x,2) + pow(y,2) + pow(z,2));

             if (r < cutoff)
             {
                 pp += 24*epsilon*(2*s12/pow(r,12) - s6/pow(r,6));
             }
         }
     }

    pp *= 1/(3 * volume);
    kp = 2 * energy.kinetic / (3 * volume);

    // Convert to atmosphere
    conv = pow(1e10,3) * 4184 / (6.022e23 * 101325);
    pp *= conv;
    kp *= conv;

    pressure.total = pp + kp;
    pressure.potential = pp;
    pressure.kinetic = kp;

    return pressure;
}
