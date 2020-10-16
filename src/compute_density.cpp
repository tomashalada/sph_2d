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
