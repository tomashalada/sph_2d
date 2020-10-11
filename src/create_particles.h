#ifndef CREATE_PARTICLE_H
#define CREATE_PARTICLE_H

#include "particle.h"

void initialize_boundary(std::vector<Particle> &particle_list, int &particle_total, int &particle_boundary, int width_box, int height_box, double init_dist, double mass);
void initialize_fluid(std::vector<Particle> &particle_list, int &particle_total, int &particle_fluid, double width_fluid, double height_fluid, double init_dist, double mass);

//test
void Create_particles(std::vector<Particle>);

#endif
