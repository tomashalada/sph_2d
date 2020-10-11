#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_acceleration(std::vector<Particle> &particle_list, double mass){

		//acceleration = {0., 0.};
		std::array<double, 2> acc_help;
		double p_temp;

		// Na pak
		//for (auto& [a, b] : zip(list_of_neighbours, kernel_dW)) {
		//		a = b;
		//}


		for(unsigned i = 0; i < num_of_neighbours; i++) {

				p_temp = p/pow(rho, 2) + particle_list[list_of_neighbours[i]].get_pressure()/pow(particle_list[list_of_neighbours[i]].get_density(),2);
				//std::cout << "__compute_acceleration__ dens_own = " << rho << std::endl;
				//std::cout << "__compute_acceleration__ dens_host = " <<  particle_list[list_of_neighbours[i]].get_density() << std::endl;
				//std::cout << "__compute_acceleration__ p_temp = " << p_temp << std::endl;
				if(rho == 0){
								std::cout << "__compute_acceleration__ PROBLEM - density own" << std::endl;
				}
				if( particle_list[list_of_neighbours[i]].get_density() == 0){
						std::cout << "__compute_acceleration__ PROBLEM - density host: " << particle_list[list_of_neighbours[i]].get_density() << std::endl;
						std::cout << "__compute_acceleration__ PROBLEM - particleID " << list_of_neighbours[i] << std::endl;

						std::cout << "__compute_acceleration__ spatna castice density: " << particle_list[899].get_density() <<std::endl;
						std::cout << "__compute_acceleration__ spatna castice ID: " << particle_list[899].get_ID_of_particle() <<std::endl;
				}

				acceleration[0] = acceleration[0] + kernel_dW_x[i]*p_temp*mass;
				acceleration[1] = acceleration[1] + kernel_dW_y[i]*p_temp*mass;

				acc_help[0] = particle_list[list_of_neighbours[i]].get_acceleration()[0] - kernel_dW_x[i]*p_temp*mass;
				acc_help[1] = particle_list[list_of_neighbours[i]].get_acceleration()[1] - kernel_dW_y[i]*p_temp*mass;
				particle_list[list_of_neighbours[i]].set_acceleration(acc_help);
				//std::cout << "__compute_acceleration__ acceleration: " << acceleration[0] <<","<< acceleration[1] << std::endl;

				if(abs(acc_help[0]) > 1 || abs(acc_help[1]) > 1){
					//std::cout << "__compute_acceleration__ spravne zrychleni HOST" << std::endl;
				}

		}

				//std::cout << "__compute_acceleration__ acceleration: " << acceleration[0] <<","<< acceleration[1] << std::endl;
				//if(abs(part.get_acceleration()[0]) > 1 || abs(part.get_acceleration()[1]) > 1){
				if(abs(acceleration[0]) > 1 || abs(acceleration[1]) > 1){
					//std::cout << "__compute_acceleration__ spravne zrychleni" << std::endl;
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
