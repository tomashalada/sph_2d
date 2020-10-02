// c++ 17
// pouzivat iteratory

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "particle.h"
#include "create_particles.h"
#include "find_pairs.h"
#include "output_to_vtk.h"


// -----------------------------------------------------------------------------------
// Vstupni parametry

const static std::vector<double> gravity{0, -9.81};
const static double h = 1; // kernel constant
const static double mass = 1; // mass
const static double visco = 1; //visco
const static double dt = 1; // time-step
const static double t_max = 2; // koncovy cas
const static float init_dist = 0.1; //referencni pocet castic pro inicializaci

//Oblast
const static int height_domain = 2; //rozmery pripustneho oboru
const static int width_domain = 2;
const static int height_box = 1; //rozmer hranic
const static int width_box = 1;
const static float height_fluid = 0.5; //rozmer uvodniho boxiku tekutiny
const static float width_fluid = 0.5;


// -----------------------------------------------------------------------------------
// Na pak

//class Particle_boundary: public Particle{
//
//		Particle_boundary(int, double, double, std::array<double,2>);
//		Particle_boundary();
//		~Particle_boundary();
//
//};

//class Particle_fluid: public Particle{
//
//		Particle_fluid(int, double, double, std::array<double,2>);
//		Particle_fluid();
//		~Particle_fluid();
//
//};


// -----------------------------------------------------------------------------------
// Vycisleni jadra

//double *Smoothing_kernel(double r, double h){
//
//}

//po algoritmizacni strance je tohle ciry odpad, prilezitostne predelam
void initialize_test_boundary(std::vector<Particle> &particle_list, int &particle_total){

		std::array<double, 2> initial_position;
		std::array<double, 2> initial_velocity;
		double initial_p = 1;
		double initial_rho = 1;

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
				//Particle(int, int, double, double, std::array<double, 2>, std::array<double, 2>)
				particle_list.push_back(Particle());
		}

}

// -----------------------------------------------------------------------------------

int main(int argc, char **argv){

		int particle_total = 0;
		std::vector<Particle> particle_list;

// -----------------------------------------------------------------------------------

		//Integractni loop - asi Leap frog
		double time;
		//while (time < t_max){
		//
		//}


// -----------------------------------------------------------------------------------
		std::vector<Particle> particle_TEST(1, Particle());

		Create_particles(particle_TEST);
		Find_pairs(particle_TEST);
		Output_to_VTK(particle_TEST);
		//Compute_density(particle_TEST);
		//Compute_pressure(particle_TEST);
		//Compute_acceleration(particle_TEST);
		//Compute_artificial_viscosity(particle_TEST);

		particle_TEST[0].Compute_acceleration();
		particle_TEST[0].Compute_density();
		particle_TEST[0].Compute_pressure();
		particle_TEST[0].Compute_artificial_viscosity();

		return EXIT_SUCCESS;
}
