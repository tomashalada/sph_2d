#include "particle.h"
#include <iostream>
#include <vector>

#include "zip.h"
#include "range.h"

// -----------------------------------------------------------------------------------
// VYPOCET HUSTOTY SUMACI

void Particle::Compute_density(std::vector<Particle> &particle_list, double mass){

		//double dens_help;

		for (std::vector<int>::size_type i = 0; i < list_of_neighbours.size(); i++){
				rho = rho + kernel_W[i]*mass;

				// ..eh?
				//dens_help = particle_list[list_of_neighbours[i]].get_density() + kernel_W[i]*mass;
				//particle_list[list_of_neighbours[i]].set_density(dens_help);
		}
		if(rho == 0){
				std::cout << "__compute_density__ PROBLEM, NULOVA HUSTOTA!" << std::endl;
				std::cout << "__compute_density__ particle ID: " << particleID << " position: " << position[0] << \
				"," << position[1] << std::endl;
		}
}

// -----------------------------------------------------------------------------------
// VYPOCET HUSTOTY Z RK

void Particle::Compute_density_change(std::vector<Particle> &particle_list, double mass){

		std::array<double, 2> vel_temp;
		double d_temp;

		for(unsigned i = 0; i < num_of_neighbours; i++) {

				vel_temp[0] = velocity[0] - particle_list[list_of_neighbours[i]].get_velocity()[0];
				vel_temp[1] = velocity[1] - particle_list[list_of_neighbours[i]].get_velocity()[1];
				d_temp = vel_temp[0]*kernel_dW_x[i] + vel_temp[1]*kernel_dW_y[i];
				drho = drho + d_temp*mass/particle_list[list_of_neighbours[i]].get_density();

				if(drho != 0){
				//std::cout << "__compute_density__ drho: " << drho << std::endl;
				}
		}

		drho = drho*rho;
}



