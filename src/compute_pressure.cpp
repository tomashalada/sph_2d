#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_pressure(){

		//Parametry stavove rovnice pro umelous stlacitelnost
		double gamma = 7;
		double ref_density = 1000;
		double sound_speed = 40; //toto je numericka rychlost zvuku.. asi
		double b_const = pow(sound_speed, 2)*ref_density/gamma;

		double relative_density = rho/ref_density;



		//double p0 = 1000*31.3*31.3 /7;
		double p0 = sound_speed*sound_speed*ref_density/7;
		p = p0 * ( pow(relative_density, gamma) - 1 );
		//std::cout << "pressure: " << p << std::endl;
		if(p < 0){
				p = 0;
				//std::cout << "__compute_pressure__: undefined behaviour" << std:: endl;
		}
		//p = pow(sound_speed,2)*rho;
		//p = 2000*(rho - ref_density);

}
