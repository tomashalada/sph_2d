#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

class Particle{
		private:

		int particleID;
		int type; //0 castice tekutiny, 1 castice hranice
		double rho, p;
		std::array<double, 2> position, velocity;

		int num_of_neighbours;
		std::vector<int> list_of_neighbours; //list spoluinteragujicich castic

		public:
		//Konstruktory/destruktory
		Particle(int, int, double, double, std::array<double,2>, std::array<double, 2>);
		Particle();
		~Particle();

		//Samostatne funkce
		//void Create_particles(std::vector<Particle>);
		//void Find_pairs(std::vector<Particle>);
		//void Output_to_VTK(std::vector<Particle> particles);

		//Metody
		void Compute_density();
		void Compute_pressure();
		void Compute_acceleration();
		void Compute_artificial_viscosity();

		//Metody - vyhledavani paru
		bool check_domain(std::array<double, 2>, int height_domain, int width_domain);
		void add_to_neighbours_list(int);

		//Settery/gettery
		void set_possition(std::array<double, 2>);
		std::array<double, 2> get_possition();

		void set_velocity(std::array<double, 2>);
		std::array<double, 2> get_velocity();

		void set_pressure(double p);
		double get_pressure();

		void set_density(double rho);
		double get_density();

		int get_type_of_particle();
		int get_ID_of_particle();

};

#endif

