#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "particle.h"
#include "define_options.h"

#include <iostream>
#include <vector>
#include <cmath>

void Fnc_check_values(std::vector<Particle> &particle_list){
				/* Kontrolni vypis pro kontrolu */

				for(int i = 0; i < particle_list.size(); i++){
				//std::cout << "__main__ acceleration: " << particle_list[i].get_acceleration()[0] <<","<< particle_list[i].get_acceleration()[1] << std::endl;
				//std::cout << "__main__ velocity: " << particle_list[i].get_velocity()[0] <<","<< particle_list[i].get_velocity()[1] << std::endl;
				//std::cout << "__main__ pressure: " << particle_list[i].get_pressure() << std::endl;
				//std::cout << "__main__ density: " << particle_list[i].get_density() << std::endl;
				//std::cout << "__main__ av acceleration: " << particle_list[i].get_artif_acc()[0] <<","<< particle_list[i].get_artif_acc()[1] << std::endl;
				if(particle_list[i].get_density() == 0){
					//std::cout << "__main__ PROBLEM S HUSTOTOU!" << std::endl;
				}
				if(fabs(particle_list[i].get_acceleration()[0]) > 1 || fabs(particle_list[i].get_acceleration()[1]) > 1){
					//std::cout << "__main__ spravne zrychleni" << std::endl;
					}
				}
}

void Odpadky(std::vector<Particle>  &particle_list){
						/* Silna parodia na OP */

				std::array<double, 2> help_pos; //help pro integracni algoritmus
				std::array<double, 2> help_vel; //help pro integracni algoritmus

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
}

#endif
