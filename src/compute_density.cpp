#include "particle.h"
#include <iostream>
#include <vector>

#include "zip.h"
#include "range.h"

void Particle::Compute_density(std::vector<Particle> &particle_list, double mass, double W0){

		double dens_help;


		for (std::vector<int>::size_type i = 0; i < list_of_neighbours.size(); i++){

				//if(particleID == particle_list[list_of_neighbours[i]].get_ID_of_particle()){std::cout <<"xxxxxxxxxxxxxxxxxxxxxx"<<std::endl;}

				rho = rho + kernel_W[i]*mass;

				dens_help = particle_list[list_of_neighbours[i]].get_density() + kernel_W[i]*mass;
				//particle_list[list_of_neighbours[i]].set_density(dens_help);

		}
				if(rho == 0){
						std::cout << "__compute_density__ PROBLEM, NULOVA HUSTOTA!" << std::endl;
						std::cout << "__compute_density__ particle ID: " << particleID << " position: " << position[0] << \
								"," << position[1] << std::endl;
				}
}

void Particle::Compute_density_change(std::vector<Particle> &particle_list, double mass, double W0){

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
				if(particle_list[list_of_neighbours[i]].get_type_of_particle() == 1){
		//				std::cout << "Interaciton with boundary particle: " << std::endl;
				}

		}

		drho = drho*rho;
}



//Vypocet hustoty
//void density(particle particleList[n], std::vector<int> i_ptcs, std::vector<int> j_ptcs, std::vector<double> W, int pairs, double W0){
//
//	for(int i = 0; i < n; i++){
//		particleList[i].set_dens(m*W0);
//	}
//	for(int i = 0; i < pairs; i++){
//		int a = i_ptcs[i];
//		int b = j_ptcs[i];
//		//double dv = partliceList[i].get_vel() - particleList[j].get_vel();
//		particleList[a].set_dens(particleList[a].get_dens() + m*W[i]);
//		particleList[b].set_dens(particleList[b].get_dens() + m*W[i]);
//	}
//}
