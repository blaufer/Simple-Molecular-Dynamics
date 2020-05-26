#include <cmath>
#include <vector>
#include <iostream>
#include <string>

// My modules
#include "structure.h"
#include "lattice.h"

using namespace std;

vector<vector<long double>> from_basis(vector<vector<long double>> basis, dimensions box)
{
    int i,j,k,l;
    vector<vector<long double>> pos;

    int x_units = box.x_max - box.x_min;
    int y_units = box.y_max - box.y_min;
    int z_units = box.z_max - box.z_min;

    for (i = 0; i < x_units; i++)
    {
        for (j = 0; j < y_units; j++)
        {
            for (k = 0; k < z_units; k++)
            {
                for (l = 0; l < basis.size(); l++)
                {
                    vector<long double> temp{basis[l][0]+i,
                                        basis[l][1]+j,
                                        basis[l][2]+k};
                    pos.push_back(temp);
                }
            }
        }
    }

    return pos;
}


pva lattices(const string latt, dimensions box, long double a, pva cur)
{
    vector<vector<long double>> pos;

    if (latt == "sc")
    {
        vector<vector<long double>> basis{{0.0,0.0,0.0}};
        pos = from_basis(basis,box);
    }
    else if (latt == "bcc")
    {
        vector<vector<long double>> basis{{0.0,0.0,0.0},
                                    {0.5,0.5,0.5}};
        pos = from_basis(basis,box);
    }
    else if (latt == "fcc")
    {
        vector<vector<long double>> basis{{0.0,0.0,0.0},
                                    {0.5,0.5,0.0},
                                    {0.5,0.0,0.5},
                                    {0.0,0.5,0.5}};
        pos = from_basis(basis,box);
    }

    for (int i=0; i < pos.size(); i++)
    {
        pos[i][0] += box.x_min;
        pos[i][1] += box.y_min;
        pos[i][2] += box.z_min;
        
        pos[i][0] *= a;
        pos[i][1] *= a;
        pos[i][2] *= a;
    }

    cur.pos = pos;

    return cur;
}

pva center_of_mass(int natoms, dimensions box, pva cur)
{
    int i, j;
    
    // Find center of the box
    vector<long double> box_center;
    box_center.push_back((box.x_max + box.x_min) / 2);
    box_center.push_back((box.y_max + box.y_min) / 2);
    box_center.push_back((box.z_max + box.z_min) / 2);
    
    // Calculate center of mass
    vector<long double> com = {0.0,0.0,0.0};
    for (i=0; i < natoms; i++)
    {
        for (j=0; j < 3; j++)
        {
            com[j] += cur.pos[i][j];
        }
    }
    
    for (i=0; i < 3; i++)
        com[i] /= natoms;

    // Remove center of mass
    for (i=0; i < natoms; i++)
    {
        for (j=0; j < 3; j++)
        {
            cur.pos[i][j] -= com[j];
        }
    } 
    
    return cur;
}
