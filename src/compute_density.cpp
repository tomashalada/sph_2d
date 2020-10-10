#include "particle.h"
#include <iostream>
#include <vector>

void Particle::Compute_density(double mass){

		rho = 0;
		for(auto &kernel : kernel_W ){

				rho = rho + kernel*mass;

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
