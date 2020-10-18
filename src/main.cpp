// c++ 17
// pouzivat iteratory

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <iterator>
#include <fstream>
#include <cmath>
#include <eigen3/Eigen/Dense>

#include "particle.h"
#include "create_particles.h"
#include "find_pairs.h"
#include "output_to_vtk.h"



// -----------------------------------------------------------------------------------
// Vstupni parametry

const static Eigen::Vector2d gravity = {0, -9.81};
const static double h = 0.02; // kernel constant
const static double mass = 0.4; // mass
const static double visco = 1; //visco
const static double dt = 0.0005; // time-step
const static double t_max = 1.0; // koncovy cas
const static double init_dist = 0.02; //referencni pocet castic pro inicializaci
const static double kappa = 1.5;
const static Eigen::Vector2d test;
const static double eps = h;
const static double damp = -0.8;

//Oblast - tohle aktualne nefunguje
const static int height_domain = 2; //rozmery pripustneho oboru
const static int width_domain = 2;
const static int height_box = 1; //rozmer hranic
const static int width_box = 1;
const static double height_fluid = 0.6; //rozmer uvodniho boxiku tekutiny
const static double width_fluid = 0.6;


// -----------------------------------------------------------------------------------

int main(int argc, char **argv){

		int particle_boundary = 0;
		int particle_fluid = 0;
		int particle_total = 0;
		std::vector<Particle> particle_list;
		std::vector<Particle> particle_list_boundary;
		double W0 = 5/(14*M_PI*pow(h,2));

// -----------------------------------------------------------------------------------
		//Inicializace castic
		int particle_boundary_total = 0;
		initialize_fluid(particle_list, particle_total, particle_fluid, width_fluid, height_fluid, init_dist, mass);
		//initialize_boundary(particle_list_boundary, particle_boundary, particle_boundary, width_box, height_box, init_dist, mass);

		//Integractni loop - asi Leap frog
		double time;
		int step = 0;
		int step_f;
		int steps = t_max / dt;
		Eigen::Vector2d help; //help pro integracni algoritmus
		Eigen::Vector2d help_pos; //help pro integracni algoritmus
		Eigen::Vector2d help_vel; //help pro integracni algoritmus
		Eigen::Vector2d help_acc; //help pro integracni algoritmus
		Eigen::Vector2d av_help;

		std::vector<Particle> testvector;

		while (step < steps){

				step++;
				step_f = step;
				std::cout << "Aktualne probiha krok: " << step << " v case: " << step*dt << std::endl;


				if (step > 1){

						//prvni cast leapfrog intergrace
						for(int i = 0; i < particle_total; i++){

								particle_list[i].set_velocity_last(particle_list[i].get_velocity());

								help[0] = particle_list[i].get_velocity()[0] + 0.5*dt*particle_list[i].get_acceleration()[0];
								help[1] = particle_list[i].get_velocity()[1] + 0.5*dt*particle_list[i].get_acceleration()[1];
								particle_list[i].set_velocity(help);

						}
				}

						Find_pairs(particle_list, h, kappa, W0);

						for(auto &part : particle_list){

							part.set_density(0);
							part.set_acceleration({0.,0.});
							//part.size_of_vectors();
						}

						for(auto &part : particle_list){
						//for(int i = 0; i < particle_total; i++){

								part.Compute_density(particle_list, mass, W0);
								//particle_list[i].Compute_density(particle_list, mass);
						}
						for(int i = 0; i < particle_total; i++){
						//std::cout << "__main__ acceleration: " << particle_list[i].get_acceleration()[0] <<","<< particle_list[i].get_acceleration()[1] << std::endl;
						//std::cout << "__main__ density: " << particle_list[i].get_density() << std::endl;
						}


						for(int i = 0; i < particle_total; i++){

								particle_list[i].Compute_pressure();
						}

						for(int i = 0; i < particle_total; i++){
								particle_list[i].Compute_acceleration(particle_list, mass, h);

										if(abs(particle_list[i].get_acceleration()[0]) > 1 || abs(particle_list[i].get_acceleration()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni IN FUNCTION" << std::endl;
										}
						}


						for(int i = 0; i < particle_total; i++){

								//std::cout << "__main__ acceleration: " << particle_list[i].get_acceleration()[0] <<","<< particle_list[i].get_acceleration()[1] << std::endl;
								//std::cout << "__main__ velocity: " << particle_list[i].get_velocity()[0] <<","<< particle_list[i].get_velocity()[1] << std::endl;
								//std::cout << "__main__ pressure: " << particle_list[i].get_pressure() << std::endl;
								//std::cout << "__main__ density: " << particle_list[i].get_density() << std::endl;
								//std::cout << "__main__ av acceleration: " << particle_list[i].get_artif_acc()[0] <<","<< particle_list[i].get_artif_acc()[1] << std::endl;

								if(particle_list[i].get_density() == 0){
										//std::cout << "__main__ PROBLEM S HUSTOTOU!" << std::endl;
								}
								if(abs(particle_list[i].get_acceleration()[0]) > 1 || abs(particle_list[i].get_acceleration()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni" << std::endl;
								}

						}



						for(int i = 0; i < particle_total; i++){
										particle_list[i].finish_step();
						}

						for(int i = 0; i < particle_total; i++){
								if(step == 1){
										help[0] = particle_list[i].get_velocity()[0] + 0.5*dt*particle_list[i].get_acceleration()[0];
										help[1] = particle_list[i].get_velocity()[1] + 0.5*dt*particle_list[i].get_acceleration()[1];
										particle_list[i].set_velocity(help);

										help_pos[0] = particle_list[i].get_position()[0] + dt*particle_list[i].get_velocity()[0];
										help_pos[1] = particle_list[i].get_position()[1] + dt*particle_list[i].get_velocity()[1];
										particle_list[i].set_position(help_pos);
										//std::cout << "__main__ help pos: " << help_pos[0] <<","<< help_pos[1] << std::endl;
										//std::cout << "__main__ velocity: " << particle_list[i].get_velocity()[0] <<","<< particle_list[i].get_velocity()[1] << std::endl;
										//std::cout << "__main__ position: " << particle_list[i].get_position()[0] <<","<< particle_list[i].get_position()[1] << std::endl;
								}
								else{

										help[0] = particle_list[i].get_velocity_last()[0] + dt*particle_list[i].get_acceleration()[0];
										help[1] = particle_list[i].get_velocity_last()[1] + dt*particle_list[i].get_acceleration()[1];
										particle_list[i].set_velocity(help);
										//std::cout << "__main__ help: " << help[0] << "," << help[1] << std::endl;

										//help_pos[0] = particle_list[i].get_position()[0] + dt*particle_list[i].get_velocity()[0];
										help_pos[0] = particle_list[i].get_position()[0] + dt*help[0];
										//help_pos[1] = particle_list[i].get_position()[1] + dt*particle_list[i].get_velocity()[1];
										help_pos[1] = particle_list[i].get_position()[1] + dt*help[1];
										particle_list[i].set_position(help_pos);
										//std::cout << "__main__ help pos: " << help_pos[0] <<","<< help_pos[1] << std::endl;
										//std::cout << "__main__ velocity: " << particle_list[i].get_velocity()[0] <<","<< particle_list[i].get_velocity()[1] << std::endl;
										//std::cout << "__main__ position: " << particle_list[i].get_position()[0] <<","<< particle_list[i].get_position()[1] << std::endl;

										}
						}

						//Silna parodie na OP
						for(auto &part : particle_list){

						if(part.get_position()[0] - eps < -1){

								help_vel[0] = part.get_velocity()[0]*damp;
								help_vel[1] = part.get_velocity()[1];
								part.set_velocity(help_vel);

								help_pos[0] = -0.5 + eps;
								help_pos[1] = part.get_position()[1];
								part.set_position(help_pos);
						}
						if(part.get_position()[0] + eps > 1){

								help_vel[0] = part.get_velocity()[0]*damp;
								help_vel[1] = part.get_velocity()[1];
								part.set_velocity(help_vel);

								help_pos[0] = 1- eps;
								help_pos[1] = part.get_position()[1];
								part.set_position(help_pos);
						}
						if(part.get_position()[1] - eps < 0){

								help_vel[0] = part.get_velocity()[0];
								help_vel[1] = part.get_velocity()[1]*damp;
								part.set_velocity(help_vel);

								help_pos[0] = part.get_position()[0];
								help_pos[1] = eps;
								part.set_position(help_pos);
						}
						if(part.get_position()[1] + eps > 1.3){

								help_vel[0] = part.get_velocity()[0];
								help_vel[1] = part.get_velocity()[1]*damp;
								part.set_velocity(help_vel);

								help_pos[0] = part.get_position()[0];
								help_pos[1] = 1- eps;
								part.set_position(help_pos);
						}
						}



		std::string name = "output";
		name = name + std::to_string(step_f) + ".vtk";
		write_to_ASCII_VTK(particle_list,particle_total, name);

		}




// -----------------------------------------------------------------------------------

		//write_to_CSV(particle_list,particle_total);
		//write_to_ASCII_VTK(particle_list,particle_total, "output_finalni.vtk");

		return EXIT_SUCCESS;
}
