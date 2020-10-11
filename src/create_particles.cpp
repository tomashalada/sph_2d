#include "particle.h"
#include <iostream>
#include <vector>
#include <array>

//Toto neni pekne, ale w/e
void initialize_boundary(std::vector<Particle> &particle_list, int &particle_total, int &particle_boundary, int width_box, int height_box, double init_dist, double mass){

		std::array<double, 2> initial_position;
		std::array<double, 2> initial_velocity_boundary = {0., 0.};
		double initial_p = 1;
		double initial_rho = 0.09;

		// haha
		int number_bp = (width_box/init_dist) * 4;

		for(int j = 0; j < number_bp; j++){

				if ( j <= width_box/init_dist  ){
						initial_position[0] = 0 + j*init_dist;
						initial_position[1] = 0;
				}
				else if ((j > width_box/init_dist) && (j <= (width_box/init_dist + height_box/init_dist))){
						initial_position[0] = width_box;
						initial_position[1] = 0 + (j - width_box/init_dist)*init_dist;
				}
				else if ((j > (width_box/init_dist + height_box/init_dist)) && (j <= (2*width_box/init_dist + height_box/init_dist ))){
						initial_position[0] = width_box - (j - width_box/init_dist - height_box/init_dist)*init_dist;
						initial_position[1] = height_box;
				}
				else if ((j > (2*width_box/init_dist + height_box/init_dist)) && (j < (2*width_box/init_dist + 2*height_box/init_dist ))){
						initial_position[0] = 0;
						initial_position[1] = width_box - (j - 2*width_box/init_dist - height_box/init_dist)*init_dist;
				}
				else{
						std::cout << "Error in boundary initialization." << std::endl;
						exit(EXIT_FAILURE);
				}

				particle_total++;
				particle_boundary++;
				//Particle(int, int, double, double, std::array<double, 2>, std::array<double, 2>)

				particle_list.push_back(Particle(particle_total, 1, 1, initial_p, initial_rho, initial_position, initial_velocity_boundary));
		}

}


void initialize_fluid(std::vector<Particle> &particle_list, int &particle_total, int &particle_fluid, double width_fluid, double height_fluid, double init_dist, double mass){

		std::array<double, 2> initial_position;
		std::array<double, 2> initial_velocity_fluid = {0., 0.};
		double initial_p = 1;
		double initial_rho = 2;

		//int number_fluid = (width_fluid_cut/init_dist + 1)*(height_fluid_cut/init_dist + 1);

		//Cesta do pekla
		//double width_fluid_cut = width_fluid - init_dist;
		//double height_fluid_cut = height_fluid - init_dist;
		//int number_fluid = (width_fluid_cut/init_dist + 1)*(height_fluid_cut/init_dist + 1);

		for(int j = 0; j < (height_fluid/init_dist); j++){
				initial_position[1] = 0 + init_dist + j*init_dist;

				for(int i = 0; i < (width_fluid/init_dist); i++){
						initial_position[0] = 0 + init_dist + i*init_dist;

						particle_total++;
						particle_fluid++;
						//Particle(int, int, double, double, std::array<double, 2>, std::array<double, 2>)
						initial_p = 0.25 * i * i + 2. * i + 0.2;

						particle_list.push_back(Particle(particle_total, 0, mass, initial_p, initial_rho, initial_position, initial_velocity_fluid));
				}
		}

}

//test
void Create_particles(std::vector<Particle>){
		std::cout << "Create_particles" << std::endl;
}

