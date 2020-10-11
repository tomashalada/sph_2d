#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_pressure(){

		//Parametry stavove rovnice pro umelous stlacitelnost
		double gamma = 7;
		double ref_density = 1;
		double sound_speed = 0.1; //toto je numericka rychlost zvuku.. asi
		double b_const = pow(sound_speed, 2)*ref_density/gamma;

		double relative_density = rho/ref_density;

		p = b_const * ( pow(relative_density, gamma) - 1 );
		//std::cout << "__compute_pressure__ pressure: " << p << std::endl;
		//std::cout << "__compute_pressure__ density: " << rho << std::endl;

}
