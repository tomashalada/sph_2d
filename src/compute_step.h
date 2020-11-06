#ifndef COMPUTE_STEP_H
#define COMPUTE_STEP_H

#include "particle.h"

void compute_step(std::vector<Particle> particle_list, std::vector<Particle> particle_list_boundary, int &particle_total, int &particle_fluid, int &particle_boundary, int &particle_dynamic, int &step, const int &steps, int &step_f);

#endif
