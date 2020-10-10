#include "particle.h"
#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <cmath>

double *smoothing_kernel(double r, double dx, double dy, double h);

void Find_pairs(std::vector<Particle> particle_list, double smth_length, double kappa){

		std::array<double, 2> position_first;
		std::array<double, 2> position_second;
		std::array<double, 2> position_dif;

		double particle_distance;
		double x;
		double *kernel;

		for(Particle &part_first : particle_list){

				position_first = part_first.get_position();

				for(Particle &part_second : particle_list){

						position_second = part_second.get_position();
						x = pow(position_first[0] - position_second[0], 2) +pow(position_first[1] - position_second[1], 2);
						particle_distance = sqrt( x );

						if (particle_distance < (kappa * smth_length)){

								kernel = smoothing_kernel(particle_distance, position_first[0] - position_second[0],position_first[1] - position_second[1], smth_length);
								position_dif[0] = position_first[0] - position_second[0];
								position_dif[1] = position_first[1] - position_second[1];
								part_first.add_to_neighbours_list(part_second.get_ID_of_particle(), kernel[0], kernel[1], kernel[3], position_dif);

						}
				}
		}
}

//cubic spline kernel
double *smoothing_kernel(double r, double dx, double dy, double h){

	static double smooth_fc[3];
	double rs = fabs(r / h);
	double rx = fabs(dx / h);
	double ry = fabs(dy / h);
	double dim_param = 2.0/(3.0*h);
	if (rs <= 1.0){
		smooth_fc[0] = (1.0 - 1.5 * rs*rs + 0.75 * rs*rs*rs) * dim_param;
		smooth_fc[1]  = (r/fabs(r)) * (2.0 * rx - (3.0/2.0) * rx * rx) * (1.0/(h*h));
		smooth_fc[2]  = (r/fabs(r)) * (2.0 * ry - (3.0/2.0) * ry * ry) * (1.0/(h*h));
	}
	else if ((rs <= 2.0)&&(rs>1.0)){
		smooth_fc[0]  = 0.25 * pow(2 - rs, 3) * dim_param;
		smooth_fc[1] = (r/fabs(r)) * (0.5 * pow(rx-2,2))* (1.0/(h*h));
		smooth_fc[2] = (r/fabs(r)) * (0.5 * pow(ry-2,2))* (1.0/(h*h));
	}
	else{
		smooth_fc[0] = 0.0;
		smooth_fc[1] = 0.0;
		smooth_fc[2] = 0.0;
	}
	if (r == 0.0){
		smooth_fc[0] = 2.0/(3.0*h);
		smooth_fc[1] = 0.0;
		smooth_fc[2] = 0.0;
	}
	return smooth_fc;
}
