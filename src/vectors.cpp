#include <vector>

#include "vectors.h"

using namespace std;

vector<vector<long double>> zeroes(int row, int col)
{
    int i;
    vector<long double> temp;
    vector<vector<long double>> zeroed;

    for (i=0; i < col; i++)
    {
        temp.push_back(0.0);
    }
    for (i=0; i < row; i++)
    {
        zeroed.push_back(temp);
    }
    
    return zeroed;
}

vector<vector<long double>> vector_copy(vector<vector<long double>> old)
{
    int i,j;
    vector<vector<long double>> copied;

    copied = zeroes(old.size(), old[0].size());

    for (i=0; i < old.size(); i++)
    {
        for (j=0; j < old[i].size(); j++)
        {
            copied[i][j] = old[i][j];
        }
    }
    
    return copied;
}
