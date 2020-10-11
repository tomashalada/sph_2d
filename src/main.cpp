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

#include "particle.h"
#include "create_particles.h"
#include "find_pairs.h"
#include "output_to_vtk.h"


// -----------------------------------------------------------------------------------
// Vstupni parametry

const static std::array<double, 2> gravity{0, -9.81};
const static double h = 0.015; // kernel constant
const static double mass = 0.0008; // mass
const static double visco = 1; //visco
const static double dt = 0.2; // time-step
const static double t_max = 0.8; // koncovy cas
const static double init_dist = 0.02; //referencni pocet castic pro inicializaci
const static double kappa = 4;

//Oblast
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

// -----------------------------------------------------------------------------------
		//Inicializace castic
		//initialize_boundary(particle_list, particle_total, particle_boundary, width_box, height_box, init_dist, mass);
		initialize_fluid(particle_list, particle_total, particle_fluid, width_fluid, height_fluid, init_dist, mass);

		//Integractni loop - asi Leap frog
		double time;
		int step = 0;
		int steps = t_max / dt;
		std::array<double, 2> help; //help pro integracni algoritmus
		std::array<double, 2> help_pos; //help pro integracni algoritmus
		std::array<double, 2> av_help;

		std::vector<Particle> testvector;

		while (step < steps){

				step++;
				std::cout << "Aktualne probiha krok: " << step << " v case: " << step*dt << std::endl;


				if (step > 1){

						//prvni cast leapfrog intergrace
						for(Particle &part : particle_list){

								part.set_velocity_last(part.get_velocity());

								help[0] = part.get_velocity()[0] + 0.5*dt*part.get_acceleration()[0];
								help[1] = part.get_velocity()[1] + 0.5*dt*part.get_acceleration()[1];
								part.set_velocity(help);

						}
				}

						Find_pairs(particle_list, h, kappa);

						//for(Particle &prt : particle_list){

						//		//std::cout << "number of neighbours = " << prt.get_num_of_neighbours() << std::endl;

						//}

						//for(Particle &part : particle_list){

						//		//std::cout << "__main__ num of neighbours: " << part.get_num_of_neighbours() << std::endl;

						//}
						for(Particle &part : particle_list){

								part.set_density(0);
								part.set_acceleration({0.,0.});
						}

						for(Particle &part : particle_list){

								part.Compute_density(particle_list, mass);
						}

						//std::cout << "__main__ spatna castice density: " << particle_list[899].get_density() <<std::endl;
						//std::cout << "__main__ spatna castice ID: " << particle_list[899].get_ID_of_particle() <<std::endl;

						for(Particle &part : particle_list){

								part.Compute_pressure();
						}

						for(Particle part : particle_list){
								part.Compute_acceleration(particle_list, mass);

								if(abs(part.get_acceleration()[0]) > 1 || abs(part.get_acceleration()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni IN FUNCTION" << std::endl;
								}
						}

						for(Particle &part : particle_list){

								//std::cout << "__main__ acceleration: " << part.get_acceleration()[0] <<","<< part.get_acceleration()[1] << std::endl;
								//std::cout << "__main__ velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;
								//std::cout << " __matin__ pressure: " << part.get_pressure() << std::endl;
								if(part.get_density() == 0){
										std::cout << "__main__ PROBLEM!" << std::endl;
								}
								if(abs(part.get_acceleration()[0]) > 1 || abs(part.get_acceleration()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni OUT FUNCTION" << std::endl;
								}

						}

						for(Particle &part : particle_list){
								part.Compute_artificial_viscosity(particle_list, h, mass, gravity);

								if(abs(part.get_artif_acc()[0]) > 1 || abs(part.get_artif_acc()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni IN FUNCTION" << std::endl;

						}
						}


								//std::cout << "__main__ density: " << part.get_density() << std::endl;
						for(Particle &part : particle_list){

								//std::cout << "__main__ acceleration: " << part.get_acceleration()[0] <<","<< part.get_acceleration()[1] << std::endl;
								//std::cout << "__main__ velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;
								//std::cout << " __matin__ pressure: " << part.get_pressure() << std::endl;
								if(part.get_density() == 0){
										//std::cout << "__main__ PROBLEM!" << std::endl;
								}
								if(abs(part.get_acceleration()[0]) > 1 || abs(part.get_acceleration()[1]) > 1){
										//std::cout << "__main__ spravne zrychleni" << std::endl;
								}

						}

						//	write_to_ASCII_VTK(particle_list,particle_total);
						for(Particle &part : particle_list){
								av_help[0] = part.get_acceleration()[0] - part.get_artif_acc()[0];
								av_help[1] = part.get_acceleration()[1] - part.get_artif_acc()[1];
								part.set_acceleration(av_help);

						}

						for(Particle &part : particle_list){

								std::cout << "__main__ acceleration: " << part.get_acceleration()[0] <<","<< part.get_acceleration()[1] << std::endl;
								std::cout << "__main__ velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;
								//std::cout << " __matin__ pressure: " << part.get_pressure() << std::endl;
								if(part.get_density() == 0){
										std::cout << "__main__ PROBLEM!" << std::endl;
								}
								if(abs(part.get_acceleration()[0]) > 1 || abs(part.get_acceleration()[1]) > 1){
										std::cout << "__main__ spravne zrychleni OUT FUNCTION" << std::endl;
								}

						}

						for(Particle &part : particle_list){
										part.finish_step();
						}

						for(Particle &part : particle_list){
								if(step == 1){
										help[0] = part.get_velocity()[0] + 0.5*dt*part.get_acceleration()[0];
										help[1] = part.get_velocity()[1] + 0.5*dt*part.get_acceleration()[1];
										part.set_velocity(help);
										std::cout << "__main__ MOVE velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;

										help_pos[0] = part.get_position()[0] + dt*part.get_velocity()[0];
										help_pos[1] = part.get_position()[1] + dt*part.get_velocity()[1];
										part.set_position(help_pos);
								}
								else{
										help[0] = part.get_velocity()[0] + dt*part.get_acceleration()[0];
										help[1] = part.get_velocity()[1] + dt*part.get_acceleration()[1];
										part.set_velocity(help);
										std::cout << "__main__ MOVE velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;

										help_pos[0] = part.get_position()[0] + dt*part.get_velocity()[0];
										help_pos[1] = part.get_position()[1] + dt*part.get_velocity()[1];
										part.set_position(help_pos);
										std::cout << "__main__ help pos: " << help_pos[0] <<","<< help_pos[1] << std::endl;
										//std::cout << "__main__ velocity: " << part.get_velocity()[0] <<","<< part.get_velocity()[1] << std::endl;

										//std::cout << "__main__ position: " << part.get_position()[0] <<","<< part.get_position()[1] << std::endl;

								}

						}

						//for(Particle &part : particle_list){
								//part.finish_step();
						//}

						//druha cast leapfrog integrace


		}

		//for(Particle part : particle_list){

		//std::cout << "__main__ position: " << part.get_position()[0] <<","<< part.get_position()[1] << std::endl;

		//}


// -----------------------------------------------------------------------------------
// Testovani


		//Takto NE-E!
		//for(particle_list_itr = particle_list.begin(); particle_list_itr < particle_list.end(); particle_list_itr++){
		// ...
		//}

		//Takto ANO!
		//for(Particle &part : particle_list){
		//		std::cout << "Castice s ID: " << part.get_ID_of_particle() <<  "s polohou: " << part.get_position()[0] <<","<< part.get_position()[1] << std::endl;
		//}

		//Alokace castic
		std::cout << "Pocet castic hranice: " << particle_boundary << " - aktualne ma byt 20 " << std::endl;
		std::cout << "Pocet castic tekutiny: " << particle_fluid << " - aktualne ma byt 9 " << std::endl;
		std::cout << "Pocet castic celkovy: " << particle_total <<  " - aktualne ma byt 29 "<<  std::endl;

		std::cout << "Delka vektoru particle_list: " << particle_list.size() << std::endl;

// -----------------------------------------------------------------------------------

		//write_to_CSV(particle_list,particle_total);
	//	write_to_ASCII_VTK(particle_list,particle_total, "output");

		return EXIT_SUCCESS;
}
