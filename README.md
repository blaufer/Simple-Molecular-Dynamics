# Simple-Molecular-Dynamics

Here is a very basic molecular dynamics program written in C++. This was initialy
done for a class but is occasionally expanded upon.

As stated, this is very basic. No thermostats or barostats are implemented but
velocities can be set using a specified temperature in Kelvin. The output can
include total energy, potential energy, kinetic energy, temperature, and pressure.

There is also the ability to remove center of mass velocities so the system does
"float" away.

Thus far, the crystal types that can be used are simple cubic, body-centered cubic,
and face-centered cubic. The only implemented potential is the 6-12 Lennard Jones
potential.

Atomic positions are output in [LAMMPS](https://lammps.sandia.gov/) dump format and
can be viewed with any program that can handle this dump format, i.e. [OVITO](https://www.ovito.org/).

## Building the program

A makefile is included to build the program. It has not been extensively tested and looks for
mpi versions of the C++ compiler because the author had planned on adding MPI cababilites but
has not as of this time.
