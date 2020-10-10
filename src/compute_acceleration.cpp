#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_acceleration(std::vector<Particle> particle_list){

		acceleration = {0., 0.};
		double p_temp;

		// Na pak
		//for (auto& [a, b] : zip(list_of_neighbours, kernel_dW)) {
		//		a = b;
		//}

		for(unsigned i = 0; i < num_of_neighbours; i++) {
			p_temp = p/pow(rho, 2) + particle_list[list_of_neighbours[i]].get_pressure()/pow(particle_list[list_of_neighbours[i]].get_density(),2);


		}
}


//Momentova rovnice
//void acceleration(particle particleList[n], int pairs, std::vector<int> i_ptcs, std::vector<int> j_ptcs, std::vector<double> dW){
//
//	for (int i = 0; i < n; i++){
//		particleList[i].set_acc(0);
//	}
//	for (int q = 0; q < pairs; q++){
//		int i = i_ptcs[q];
//		int j = j_ptcs[q];
//		double p_help = (particleList[i].get_pressure()/(pow(particleList[i].get_dens(),2))+ particleList[j].get_pressure()/(pow(particleList[j].get_dens(),2)));
//		particleList[i].set_acc(particleList[i].get_acc() + dW[q]*p_help*m);
//		particleList[j].set_acc(particleList[j].get_acc() - dW[q]*p_help*m);
//	}
//}
