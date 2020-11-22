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
//#include <eigen3/Eigen/Dense>
//#include <experimental/filesystem> alternativa pro nizsi verze
#include <filesystem> //c++17

#include "particle.h"
#include "create_particles.h"
#include "find_pairs.h"
#include "output_to_vtk.h"
#include "define_options.h"
#include "cell_ll.h"
#include "help_functions.h"
#include "compute_step.h"

// -----------------------------------------------------------------------------------

int main(int argc, char **argv){

// -----------------------------------------------------------------------------------
// HLAVNI GLOBALNI PRVKY

	/* Counter jednotlivych castic */
	static int particle_boundary = 0;
	static int particle_fluid = 0;
	static int particle_total = 0;
	static int particle_dynamic = 0;

	/* Listy jednotlvych castic */
	static std::vector<Particle> particle_list;
	static std::vector<Particle> particle_list_boundary;

	/* Cas a krok simulace*/
	static double time;
	static int step = 0;
	static int step_f;
	static const int steps = t_max / dt;

// -----------------------------------------------------------------------------------
// INICIALIZACE CASTIC

	//initialize_fluid(particle_list, particle_total, particle_fluid, width_fluid, height_fluid, init_dist, mass);
	initialize_fluid2(particle_list, particle_total, particle_fluid, width_fluid, height_fluid, init_dist, mass);

	/* PISKOVISTE
	Particle single_particle(1, 0, mass ,1., 1000, {-0.8,0.05}, {2., 0.});
	particle_total++;
	particle_fluid++;
	particle_list.push_back(single_particle);
	*/

	initialize_dynamic_boundary(particle_list, particle_total, particle_dynamic, 1.3, 1, init_dist, mass);
	//initialize_boundary(particle_list_boundary, particle_boundary, particle_boundary, width_box, height_box, init_dist, mass);


// -----------------------------------------------------------------------------------
// OUTPUT DIR

	if (!std::filesystem::is_directory(dir_name) || !std::filesystem::exists(dir_name)){
			std::filesystem::create_directory(dir_name);
	}
// -----------------------------------------------------------------------------------
// VYPOCET

	compute_step(particle_list, particle_list_boundary, particle_total, particle_fluid, particle_boundary, particle_dynamic, step, steps, step_f);

// -----------------------------------------------------------------------------------

		//write_to_CSV(particle_list,particle_total);
		std::cout << "Pocet catic celkovy: " << particle_total << std::endl;
		std::cout << "Pocet catic hranice: " << particle_dynamic << std::endl;
		std::cout << "Pocet catic tekutiny: " << particle_fluid << std::endl;
		//write_to_ASCII_VTK(particle_list,particle_total, "output_finalni.vtk");

		return EXIT_SUCCESS;
}
