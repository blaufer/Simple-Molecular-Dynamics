#include <vector>
#include <string>

#include "structure.h"

pva lattices(const string latt, dimensions box, long double a, pva cur);

vector<vector<long double>> from_basis(vector<vector<long double>>, dimensions box);

pva center_of_mass(int natoms, dimensions box, pva cur);
