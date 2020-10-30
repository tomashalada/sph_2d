#include "particle.h"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

//Toto neni pekne, ale w/e
void initialize_boundary(std::vector<Particle> &particle_list, int &particle_total, int &particle_boundary, int width_box, int height_box, double init_dist, double mass){

		std::array<double, 2> initial_position;
		std::array<double, 2> initial_velocity_boundary = {0., 0.};
		double initial_p = 1;
		double initial_rho = 1000;

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
		double initial_rho = 1000;

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


//Toto neni pekne, ale w/e
void initialize_dynamic_boundary(std::vector<Particle> &particle_list, int &particle_total, int &particle_boundary, float width_box, float height_box, double init_dist, double mass){

		int num_of_layers = 5;
		// Layer 1
		float x_min_d = -1.;
		float x_max_d = 1.3;
		float y_min_d = 0.;
		float y_max_d = 1.;
		int num_layer1;

		float x_min;
		float x_max;
		float y_min;
		float y_max;

		std::array<double, 2> initial_position;
		std::array<double, 2> initial_velocity_boundary = {0., 0.};
		double initial_p = 0;
		double initial_rho = 1000;


		for (int k = 0; k < num_of_layers; k++){
		// Layer 2
		x_min = x_min_d - init_dist*k;
		x_max = x_max_d + init_dist*k;
		y_min = y_min_d - init_dist*k;
		y_max = y_max_d + init_dist*k;

		num_layer1 = ((fabs(x_min) + fabs(x_max))*2 + (fabs(y_min) + fabs(y_max))*2)/init_dist + 1;

		float box_width = fabs(x_min) + fabs(x_max);
		float box_height = fabs(y_min) + fabs(y_max);

		for(int j = 0; j < num_layer1; j++){

				if ( j <= box_width/init_dist  ){
						initial_position[0] = x_min + j*init_dist;
						initial_position[1] = y_min;
				}
				else if ((j > box_width/init_dist) && (j <= (box_width/init_dist + box_height/init_dist))){
						initial_position[0] = x_max;
						initial_position[1] = y_min + (j - box_width/init_dist)*init_dist;
				}
				else if ((j > (box_width/init_dist + box_height/init_dist)) && (j <= (2*box_width/init_dist + box_height/init_dist ))){
						initial_position[0] = x_max - (j - box_width/init_dist - box_height/init_dist)*init_dist;
						initial_position[1] = y_max;
				}
				else if ((j > (2*box_width/init_dist + box_height/init_dist)) && (j < (2*box_width/init_dist + 2*box_height/init_dist ))){
						initial_position[0] = x_min;
						initial_position[1] = y_max - (j - 2*box_width/init_dist - box_height/init_dist)*init_dist;
				}
				else{
						std::cout << "Error in boundary initialization." << std::endl;
						exit(EXIT_FAILURE);
				}


				particle_boundary++;
				particle_total++;
				particle_list.push_back(Particle(particle_total, 1, 1, initial_p, initial_rho, initial_position, initial_velocity_boundary));

		}

		}
}
