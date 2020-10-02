#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

class Particle{
		public:

		int particleID;
		int type; //0 castice tekutiny, 1 castice hranice
		double rho, p;
		std::array<double, 2> position, velocity;

		//Konstruktory
		Particle(int, int, double, double, std::array<double,2>, std::array<double, 2>);
		Particle();
		~Particle();

		//Metody
		void Create_particles(std::vector<Particle>);
		void Find_pairs(std::vector<Particle>);
		void Output_to_VTK(std::vector<Particle> particles);
		void Compute_density(std::vector<Particle> particles);
		void Compute_pressure(std::vector<Particle> particles);
		//void Compute_acceleration(std::vector<Particle> particles);
		void Compute_artificial_viscosity(std::vector<Particle> particles);

};

#endif

