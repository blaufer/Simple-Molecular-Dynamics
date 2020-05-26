#include <vector>
#include <cmath>
#include <random>
#include <functional>

#include "structure.h"

using namespace std;

pva zero_velocity(int natoms, pva cur)
{
    int i;
    vector<long double> temp;
    vector<vector<long double>> vel;

    for (i=0; i < 3; i++)
    {
        temp.push_back(0.0);
    }
    for (i=0; i < natoms; i++)
    {
        vel.push_back(temp);
    }
    
    cur.vel = vel;

    return cur;
}

pva temp_velocity(int natoms, long double boltz, long double temp_vel, 
    long double mass, pva cur)
{
    int i;
    long double vel_atom, vx, vy, vz;
    long double total, high;
    vector<long double> temp;
    vector<vector<long double>> vel;

    mt19937_64::result_type seed = time(0);
    auto real_rand = bind(uniform_real_distribution<long double>(0,1),
        mt19937_64(seed));

    for (i=0; i < 3; i++)
    {
        temp.push_back(0.0);
    }
    for (i=0; i < natoms; i++)
    {
        vel.push_back(temp);
    }
    
    vel_atom = sqrt(3 * boltz * temp_vel / mass);
    
    for (i=0; i < natoms; i++)
    {
        while (true)
        {
            // Get vx
            total = vel_atom * 2;
            high = vel_atom;
            vx = real_rand() * total - high;

            // Get vy
            total = (vel_atom - vx) * 2;
            high = vel_atom - vx;
            vy = real_rand() * total - high;

            // Get vz
            vz = sqrt(pow(vel_atom,2) - pow(vx,2) - pow(vy,2));

            // Check to make sure total velocity is created
            if (vel_atom == sqrt(pow(vx,2) + pow(vy,2) + pow(vz,2)))
                break;
        }
        vel[i][0] = vx;
        vel[i][1] = vy;
        vel[i][2] = vz;
    }

    cur.vel = vel;

    return cur;
}
