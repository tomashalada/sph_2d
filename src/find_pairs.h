#ifndef FIND_PAIRS_H
#define FIND_PAIRS_H

#include "particle.h"
#include "cell_ll.h"
//#include "define_options.h"

void Find_pairs(std::vector<Particle> &particle_list, double smth_length, double kappa);
void Find_pairs_linked_list(std::vector<Particle> &particle_list, double smth_length, double kappa);
double *smoothing_kernel(double r, double dx, double dy, double h);
double *smoothing_kernel2(double r, double dx, double dy, double h);
double *smoothing_kernel_fix(double r, double h);
double *smoothing_kernel_fix2(double r, double h);
double *smoothing_kernel_fix_Wendland(double r, double h);

#endif
