#include <iostream>
#include <cmath>
#include <vector>

#include "particle.h"
#include "find_pairs.h"
#include "define_options.h"
#include "output_to_vtk.h"

void compute_step(std::vector<Particle> particle_list, std::vector<Particle> particle_list_boundary, int &particle_total, int &particle_fluid, int &particle_boundary, int &particle_dynamic, int &step, const int &steps, int &step_f){

// -----------------------------------------------------------------------------------
// POMOCNE, tohle pryc

	std::array<double, 2> help; //help pro integracni algoritmus
	std::array<double, 2> help_pos; //help pro integracni algoritmus
	std::array<double, 2> help_vel; //help pro integracni algoritmus
	std::array<double, 2> help_acc; //help pro integracni algoritmus

// -----------------------------------------------------------------------------------
// VYPOCET

	while (step < steps){

		/* Nastaveni casu pro dany krok, vypis, etc. */
		step++;
		step_f = step;
		std::cout << "Aktualne probiha krok: " << step << " v case: " << step*dt << std::endl;

		/* Prvni cast Leap-frog integrace */
		if (step > 1){
				for(int i = 0; i < particle_fluid; i++){
						particle_list[i].set_velocity_last(particle_list[i].get_velocity()); // --tohle tady asi byt nemusi

						help_vel[0] = particle_list[i].get_velocity()[0] + 0.5*dt*particle_list[i].get_acceleration()[0];
						help_vel[1] = particle_list[i].get_velocity()[1] + 0.5*dt*particle_list[i].get_acceleration()[1];
						particle_list[i].set_velocity(help_vel);
				}
		}


		/* Vypocet velicin */
		for(auto &part : particle_list){
				//part.set_density(0);
				part.set_density_change(0.);
				part.set_acceleration({0.,0.});

				part.finish_step();
		}

		/* Priprava kroku a nalezeni sousedu */
		//Find_pairs(particle_list, h, kappa); // --kazdy s kazdym
		Find_pairs_linked_list(particle_list, h, kappa); // --linked list

		for(auto &part : particle_list){
				//part.Compute_density(particle_list, mass, W0);
		}

		for(auto &part : particle_list){
				part.Compute_density_change(particle_list, mass);
				part.set_density(part.get_density() + part.get_density_change()*dt);
				part.Compute_pressure();
		}

		for(int i = 0; i < particle_fluid; i++){
				particle_list[i].Compute_acceleration(particle_list, mass, h);
		}

		/* Kontrolni vypis pro kontrolu */
		//Fnc_check_values(particle_list);

		/* Druha cast LF integrace */
		for(int i = 0; i < particle_fluid; i++){
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

						help_pos[0] = particle_list[i].get_position()[0] + dt*help[0];
						help_pos[1] = particle_list[i].get_position()[1] + dt*help[1];
						particle_list[i].set_position(help_pos);

						//std::cout << "__main__ help pos: " << help_pos[0] <<","<< help_pos[1] << std::endl;
						//std::cout << "__main__ velocity: " << particle_list[i].get_velocity()[0] <<","<< particle_list[i].get_velocity()[1] << std::endl;
						//std::cout << "__main__ position: " << particle_list[i].get_position()[0] <<","<< particle_list[i].get_position()[1] << std::endl;
				}
		}

		/* Vypis dat */
		if(step%20 == 0){
				std::string name = "./vystup_testovaci_4/output";
				name = name + std::to_string(step_f) + ".vtk";
				write_to_ASCII_VTK(particle_list,particle_total, name);
		}
	}
}
