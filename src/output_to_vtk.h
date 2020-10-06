#ifndef OUTUP_TO_VTK_H
#define OUTUP_TO_VTK_H

#include "particle.h"
#include <fstream>

void Output_to_VTK(std::vector<Particle> particles);
void write_to_CSV(std::vector<Particle> particle_list, int &particle_total);


#endif
