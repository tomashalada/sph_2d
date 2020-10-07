// c++ 17
// pouzivat iteratory

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <iterator>
#include <fstream>

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
const static double init_dist = 0.2; //referencni pocet castic pro inicializaci

//Oblast
const static int height_domain = 2; //rozmery pripustneho oboru
const static int width_domain = 2;
const static int height_box = 1; //rozmer hranic
const static int width_box = 1;
const static double height_fluid = 0.6; //rozmer uvodniho boxiku tekutiny
const static double width_fluid = 0.6;


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


// -----------------------------------------------------------------------------------

int main(int argc, char **argv){

		int particle_boundary = 0;
		int particle_fluid = 0;
		int particle_total = 0;
		std::vector<Particle> particle_list;

// -----------------------------------------------------------------------------------

		//Integractni loop - asi Leap frog
		double time;
		//while (time < t_max){
		//
		//}


// -----------------------------------------------------------------------------------
// Testovani

		//Inicializace castic
		initialize_boundary(particle_list, particle_total, particle_boundary, width_box, height_box, init_dist);
		initialize_fluid(particle_list, particle_total, particle_fluid, width_fluid, height_fluid, init_dist);

		//Takto NE-E!
		//for(particle_list_itr = particle_list.begin(); particle_list_itr < particle_list.end(); particle_list_itr++){
		// ...
		//}

		//Takto ANO!
		for(Particle &part : particle_list){
				std::cout << "Castice s ID: " << part.get_ID_of_particle() <<  "s polohou: " << part.get_position()[0] <<","<< part.get_position()[1] << std::endl;
		}

		//Alokace castic
		std::cout << "Pocet castic hranice: " << particle_boundary << " - aktualne ma byt 20 " << std::endl;
		std::cout << "Pocet castic tekutiny: " << particle_fluid << " - aktualne ma byt 9 " << std::endl;
		std::cout << "Pocet castic celkovy: " << particle_total <<  " - aktualne ma byt 29 "<<  std::endl;

		std::cout << "Delka vektoru particle_list: " << particle_list.size() << std::endl;

// -----------------------------------------------------------------------------------
		//Linkovani
		std::vector<Particle> particle_TEST(1, Particle());

		Particle_boundary test_bounday_particle(1, 1, 1., 1., {0.,0.}, {0.,0.});
		Particle_fluid test_fluid_particle;
		Particle test_particle;

		//test
		particle_TEST.push_back(test_particle);
		particle_TEST.push_back(test_fluid_particle);
		particle_TEST.push_back(test_bounday_particle);

		Create_particles(particle_TEST);
		Find_pairs(particle_TEST);
		Output_to_VTK(particle_TEST);
		//Compute_density(particle_TEST);
		//Compute_pressure(particle_TEST);
		//Compute_acceleration(particle_TEST);
		//Compute_artificial_viscosity(particle_TEST);

		particle_TEST[0].Compute_acceleration();
		particle_TEST[1].Compute_density();
		particle_TEST[2].Compute_pressure();
		particle_TEST[3].Compute_artificial_viscosity();

		//write_to_CSV(particle_list,particle_total);
		//write_to_ASCII_VTK(particle_list,particle_total);

		return EXIT_SUCCESS;
}
