#ifndef FIND_PAIRS_H
#define FIND_PAIRS_H

#include "particle.h"

void Find_pairs(std::vector<Particle> particle_list, double smth_length, double kappa);
double *smoothing_kernel(double r, double h);

#endif
