#ifndef FIND_PAIRS_H
#define FIND_PAIRS_H

#include "particle.h"

void Find_pairs(std::vector<Particle> &particle_list, double smth_length, double kappa, double &W0);
double *smoothing_kernel(double r, double dx, double dy, double h);
double *smoothing_kernel2(double r, double dx, double dy, double h);

#endif
