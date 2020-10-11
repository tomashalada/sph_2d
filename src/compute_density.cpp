#include "particle.h"
#include <iostream>
#include <vector>

void Particle::Compute_density(std::vector<Particle> &particle_list, double mass){

		//rho = 0;
		double dens_help;
		//for(auto &kernel : kernel_W ){
		//
		//		rho = rho + kernel*mass;

		//}
		//std::cout << "__compute_density__ num of neighbour " << num_of_neighbours << std::endl;

		for(int i = 0; i < num_of_neighbours; i++){
				rho = rho + kernel_W[i]*mass;
				dens_help = particle_list[list_of_neighbours[i]].get_density() + kernel_W[i]*mass;

				//particle_list[list_of_neighbours[i]].set_density(dens_help);
				//std::cout << "__compute_density__ kernel " << kernel_W[i] << std::endl;
		}
		//std::cout << "__compute_density__ density " << rho << std::endl;
		if(rho == 0){
				std::cout << "__compute_density__ PROBLEM!" << std::endl;
		}

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
