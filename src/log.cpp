#include <iostream>
#include <iomanip>
#include <fstream>

#include "structure.h"

using namespace std;

void write_log(pva cur, int step, long double dt, tpe energy,
    long double temperature, tpe pressure)
{
    ofstream fout;

    if (step == 0)
    {
        fout.open("log.md");
        // Label
        fout << setw(10) << "Step";
        fout << setw(10) << "Time";
        fout << setw(18) << "Tot Energy";
        fout << setw(18) << "Pot Energy";
        fout << setw(18) << "Kin Energy";
        fout << setw(15) << "Temp";
        fout << setw(15) << "Tot Press";
        fout << setw(15) << "Pot Press";
        fout << setw(15) << "Kin Press" << endl;
        
        // Units
        fout << setw(10) << " ";
        fout << setw(10) << "(akma)";
        fout << setw(18) << "(kcal/mol)";
        fout << setw(18) << "(kcal/mol)";
        fout << setw(18) << "(kcal/mol)";
        fout << setw(15) << "(K)";
        fout << setw(15) << "(atm)";
        fout << setw(15) << "(atm)";
        fout << setw(15) << "(atm)" << endl;
    }
    else
        fout.open("log.md",ios::app);

    fout << setw(10) << step;
    fout << setw(10) << step * dt;
    fout << setw(18) << energy.total;
    fout << setw(18) << energy.potential;
    fout << setw(18) << energy.kinetic;
    fout << setw(15) << temperature;
    fout << setw(15) << pressure.total;
    fout << setw(15) << pressure.potential;
    fout << setw(15) << pressure.kinetic << endl;

    fout.close();

    return;
}
