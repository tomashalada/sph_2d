#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_acceleration(std::vector<Particle> &particle_list, double mass, double h){

		//acceleration = {0., 0.};
		std::array<double, 2> acc_help;
		std::array<double, 2> vel_temp;
		double p_temp;
		double dot;
		double ALPHA = 0.1;
		double SLEN = h;
		double DENS0 = 1000;
		double SND = 31.3; //31.3
		double VISC = ALPHA * SLEN * SND / DENS0;
		double av_temp;
		double neighbour_dist_kvadr;

		for(unsigned i = 0; i < num_of_neighbours; i++) {

				p_temp = p/pow(rho, 2) + particle_list[list_of_neighbours[i]].get_pressure()/pow(particle_list[list_of_neighbours[i]].get_density(),2);
				//p_temp = (p + particle_list[list_of_neighbours[i]].get_pressure())/(rho * particle_list[list_of_neighbours[i]].get_density());
				vel_temp[0] = velocity[0] - particle_list[list_of_neighbours[i]].get_velocity()[0];
				vel_temp[1] = velocity[1] - particle_list[list_of_neighbours[i]].get_velocity()[1];

				neighbour_dist_kvadr = pow(neighbour_dist[i][0],2) + pow(neighbour_dist[i][1], 2);

				dot = vel_temp[0]*neighbour_dist[i][0] + vel_temp[1] * neighbour_dist[i][1]; //KUK
				if(dot <= 0){
						av_temp = -VISC*dot/(neighbour_dist_kvadr + 0.01*h*h);

				}


				//------------------------------------------------------------------------------------------

				acceleration[0] = acceleration[0] - kernel_dW_x[i]*(p_temp + av_temp)*mass;
				acceleration[1] = acceleration[1] - kernel_dW_y[i]*(p_temp + av_temp)*mass;

				acc_help[0] = particle_list[list_of_neighbours[i]].get_acceleration()[0] + kernel_dW_x[i]*p_temp*mass;
				acc_help[1] = particle_list[list_of_neighbours[i]].get_acceleration()[1] + kernel_dW_y[i]*p_temp*mass;
				//particle_list[list_of_neighbours[i]].set_acceleration(acc_help);


				if(fabs(acceleration[0]) > 1 || fabs(acceleration[1]) > 1){
					//std::cout << "__compute_acceleration__ spravne zrychleni" << std::endl;
				}
		}

				acceleration[1] = acceleration[1] - 9.81;

}
