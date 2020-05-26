#include <vector>
#include <cmath>
#include <iostream>

#include "structure.h"
#include "lj.h"

using namespace std;

pva vverlet(int natoms, long double dt, long double sigma,
    long double epsilon, long double mass, long double cutoff, dimensions box,
    pva prev, pva cur)
{
    int i, j;
    long double dt2 = pow(dt,2);

    for (i=0; i < natoms; i++)
    {
        for (j=0; j < 3; j++)
        {
            cur.pos[i][j] = prev.pos[i][j] + prev.vel[i][j] * dt + 0.5 * prev.acc[i][j] * dt2;
        }
    }

    cur = lj_acc(natoms, sigma, epsilon, mass, cutoff, box, cur);

    for (i=0; i < natoms; i++)
    {
        for (j=0; j < 3; j++)
        {
            cur.vel[i][j] = prev.vel[i][j] + 0.5 * (prev.acc[i][j] + cur.acc[i][j]) * dt;
        }
    }

    return cur;
}
