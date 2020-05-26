#include <iostream>
#include <fstream>
#include <algorithm>

#include "structure.h"
#include "dump.h"

using namespace std;

void write_dump(pva cur, int natoms, int step, dimensions box)
{
    int i, j;
    dimensions ubox;
    ofstream fout;

    if (step == 0)
        fout.open("dump.md");
    else
        fout.open("dump.md",ios::app);

    // Get box dimensions for unwrapped coordinates
    ubox = unwrapped_box(natoms, cur);

    fout << "ITEM: TIMESTEP" << endl;
    fout << step << endl;
    fout << "ITEM: NUMBER OF ATOMS" << endl;
    fout << natoms << endl;
    fout << "ITEM: BOX BOUNDS pp pp pp" << endl;
    fout << ubox.x_min/10 << " " << ubox.x_max/10 << endl;
    fout << ubox.y_min/10 << " " << ubox.y_max/10 << endl;
    fout << ubox.z_min/10 << " " << ubox.z_max/10 << endl;
    //fout << box.x_min/10 << " " << box.x_max/10 << endl;
    //fout << box.y_min/10 << " " << box.y_max/10 << endl;
    //fout << box.z_min/10 << " " << box.z_max/10 << endl;

    fout << "ITEM: ATOMS id type x y z vx vy vz" << endl;
    for (i=0; i < natoms; i++)
    {
        fout << i+1 << " 1";
        
        for (j=0; j < 3; j++)
        {
            fout << " " << cur.pos[i][j]/10;
        }
        for (j=0; j < 3; j++)
        {
            fout << " " << cur.vel[i][j]/10;
        }
        fout << endl;
    }

    fout.close();

    return;
}

dimensions unwrapped_box(int natoms, pva cur)
{
    dimensions ubox;
    vector<long double> x, y, z;

    for (int i=0; i < natoms; i++)
    {
        x.push_back(cur.pos[i][0]);
        y.push_back(cur.pos[i][1]);
        z.push_back(cur.pos[i][2]);
    }

    ubox.x_min = *min_element(x.begin(), x.end());
    ubox.x_max = *max_element(x.begin(), x.end());
    ubox.y_min = *min_element(y.begin(), y.end());
    ubox.y_max = *max_element(y.begin(), y.end());
    ubox.z_min = *min_element(z.begin(), z.end());
    ubox.z_max = *max_element(z.begin(), z.end());

    return ubox;
}
