// Pouzivat standard C++ 17
// pouzivat iteratory a std algoritmy

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "particle.h"
#include "create_particles.h"
#include "find_pairs.h"
#include "output_to_vtk.h"
#include "compute_density.h"
#include "compute_pressure.h"
#include "compute_acceleration.h"
#include "compute_artificial_viscosity.h"

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

// -----------------------------------------------------------------------------------

int main(int argc, char **argv){

		//Integractni algoritmus loop
		double time;
		//while (time < t_max){
		//
		//}


		std::vector<Particle> particle_TEST(1, Particle());

		Create_particles(particle_TEST);
		Find_pairs(particle_TEST);
		Output_to_VTK(particle_TEST);
		Compute_density(particle_TEST);
		Compute_pressure(particle_TEST);
		Compute_acceleration(particle_TEST);
		Compute_artificial_viscosity(particle_TEST);

		return EXIT_SUCCESS;
}
