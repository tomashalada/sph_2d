#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_pressure(){

		//Parametry stavove rovnice pro umelous stlacitelnost
		double gamma = 7;
		double ref_density = 1000;
		double sound_speed = 60; //toto je numericka rychlost zvuku.. asi
		double b_const = pow(sound_speed, 2)*ref_density/gamma;

		double relative_density = rho/ref_density;

		p = b_const * ( pow(relative_density, gamma) - 1 );

}
