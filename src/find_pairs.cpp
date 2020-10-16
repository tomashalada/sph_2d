#include "particle.h"
#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <cmath>
#include <eigen3/Eigen/Dense>


double *smoothing_kernel(double r, double dx, double dy, double h);
double *smoothing_kernel_fix(double r, double h);

void Find_pairs(std::vector<Particle> &particle_list, double smth_length, double kappa, double &W0){

		Eigen::Vector2d position_first;
		Eigen::Vector2d position_second;
		Eigen::Vector2d position_dif;

		double particle_distance;
		double x;

		double *kernel;

		for(int i = 0; i < particle_list.size(); i++){

				position_first = particle_list[i].get_position();

				for(int j = 0; j < particle_list.size(); j++){

						position_second = particle_list[j].get_position();
						x = pow(position_first[0] - position_second[0], 2) +pow(position_first[1] - position_second[1], 2);
						particle_distance = sqrt( x );

						if (particle_distance < (kappa * smth_length)){

								kernel = smoothing_kernel_fix(particle_distance,smth_length);

								position_dif[0] = position_first[0] - position_second[0];
								position_dif[1] = position_first[1] - position_second[1];


								//std::cout << "kernel: " << kernel[1] << " //// " << kernel[2] << std::endl;
								kernel[1] = kernel[1]*position_dif[0];
								kernel[2] = kernel[2]*position_dif[1];

								particle_list[i].add_to_neighbours_list(particle_list[j].get_ID_of_particle() -1, \
												 kernel[0], kernel[1], kernel[2], position_dif);

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
		smooth_fc[1]  = (1) * (2.0 * rx - (3.0/2.0) * rx * rx) * (1.0/(h*h));
		smooth_fc[2]  = (1) * (2.0 * ry - (3.0/2.0) * ry * ry) * (1.0/(h*h));
	}
	else if ((rs <= 2.0)&&(rs>1.0)){
		smooth_fc[0]  = 0.25 * pow(2 - rs, 3) * dim_param;
		smooth_fc[1] = (1) * (0.5 * pow(rx-2,2))* (1.0/(h*h));
		smooth_fc[2] = (1) * (0.5 * pow(ry-2,2))* (1.0/(h*h));
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

//cubic spline kernel
double *smoothing_kernel_fix(double r, double h){

	static double smooth_fc[3];
	double rs = fabs(r / h);

	double dim_param = 5/(14*M_PI*h*h);

	if (rs <= 1.0){
		smooth_fc[0] = (pow(2 - rs, 3) - 4 * pow(1 - rs, 3)) * dim_param;
		smooth_fc[1] = ( (-3) * pow(2 - rs, 2)  + 12 * pow(1 - rs, 2)) * dim_param;
		smooth_fc[2] = ( (-3) * pow(2 - rs, 2)  + 12 * pow(1 - rs, 2)) * dim_param;
	}
	else if ((rs <= 2.0)&&(rs>1.0)){
		smooth_fc[0] = pow(2 - rs, 3) * dim_param;
		smooth_fc[1] = (-3) * pow(2 - rs, 2) * dim_param;
		smooth_fc[2] = (-3) * pow(2 - rs, 2) * dim_param;
	}
	else{
		smooth_fc[0] = 0.0;
		smooth_fc[1] = 0.0;
		smooth_fc[2] = 0.0;
	}
	if (r == 0.0){
		smooth_fc[0] = dim_param;
		smooth_fc[1] = 0.0;
		smooth_fc[2] = 0.0;
	}
	return smooth_fc;
}
