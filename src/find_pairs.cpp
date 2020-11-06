#include "particle.h"
#include "find_pairs.h"
#include "define_options.h"

#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <cmath>


void Find_pairs(std::vector<Particle> &particle_list, double smth_length, double kappa){

		std::array<double, 2> position_first;
		std::array<double, 2> position_second;
		std::array<double, 2> position_dif;

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

								kernel = smoothing_kernel_fix2(particle_distance,smth_length);

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

	//double dim_param = 5/(14*M_PI*h*h);
	double dim_param = 10/(7*M_PI*h*h);

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

double *smoothing_kernel_fix2(double r, double h){

	static double smooth_fc[3];
	double rs = fabs(r / h);

	//double dim_param = 5/(14*M_PI*h*h);
	double dim_param = 10/(7*M_PI*h*h);

	if (rs <= 1.0){
		smooth_fc[0] = (1 - 3/2*pow(rs,2) + 3/4*pow(rs,3)) * dim_param;
		smooth_fc[1] = (-3*rs + 9/4*pow(rs, 2)) * dim_param;
		smooth_fc[2] = (-3*rs + 9/4*pow(rs, 2)) * dim_param;
	}
	else if ((rs <= 2.0)&&(rs>1.0)){
		smooth_fc[0] = (1/4*pow((2 - rs), 2)) * dim_param;
		smooth_fc[1] = ((-1)*3/4*pow((2 - rs), 2)) * dim_param;
		smooth_fc[2] = ((-1)*3/4*pow((2 - rs), 2)) * dim_param;
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


double *smoothing_kernel_fix_Wendland(double r, double h){

	static double smooth_fc[3];
	double rs = fabs(r / h);

	//double dim_param = 5/(14*M_PI*h*h);
	double dim_param = 7/(4*M_PI*h*h);

	if (rs <= 2.0){
		smooth_fc[0] = (pow((1-rs/2),4)*(2*rs + 1)) * dim_param;
		smooth_fc[1] = (2*pow((1-rs/2),4) - 2* pow((1-rs/2),3)*(2*rs+1)) * dim_param;
		smooth_fc[2] = (2*pow((1-rs/2),4) - 2* pow((1-rs/2),3)*(2*rs+1)) * dim_param;
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


void Find_pairs_linked_list(std::vector<Particle> &particle_list, double smth_length, double kappa){

		std::array<double, 2> position_first;
		std::array<double, 2> position_second;
		std::array<double, 2> position_dif;

		double particle_distance;
		double x;

		double *kernel;

		int n_x = (x_max - x_min)/(smth_length*kappa) +1;
		int n_y = (y_max - y_min)/(smth_length*kappa) +1;
		int num_of_cells = n_x * n_y;
		std::cout << "nx = " << n_x << " ny = " << n_y << std::endl;
		std::cout << "num of cells: " << num_of_cells << std::endl;

		std::vector<Cell_LL> list_of_cells(n_x*n_y, Cell_LL(smth_length*kappa));
		std::vector<int> active_neighbours;
		std::vector<int> active_cells;

		double helpx;
		double helpy;
		int to_cell;
		int to_cell2;

		std::vector<int> help_vector;

		/*
		for(auto &c : list_of_cells){
				c.clear_cell();
		}
		*/
		#pragma acc parallel loop
		for(auto &part : particle_list){

				helpx = (x_min - part.get_position()[0])/(smth_length*kappa);
				helpy = (y_min - part.get_position()[1])/(smth_length*kappa);
				to_cell = abs((int)helpy) * n_x + abs((int)helpx);
				//std::cout << "POSITION: " <<  part.get_position()[0] << "/" << part.get_position()[1] << std::endl;
				//std::cout << "helpx: " << helpx << " helpy " << helpy << " tocell1 " << to_cell << std::endl;
				if(to_cell > num_of_cells || to_cell < 0){std::cout << "FATAL ERROR in to_cell: " << to_cell << std::endl;}

				//std::cout << "TO CELL2 : " << to_cell << " NUM OF CELLS: " << list_of_cells.size() << std::endl;
				//if(to_cell < 2000){std::cout << "SUCCES" << std::endl;}


				list_of_cells[to_cell].add_particle(part.get_ID_of_particle() - 1);

		}

		#pragma acc parallel loop
		for(int i = 0; i < particle_list.size(); i++){

				position_first = particle_list[i].get_position();
				helpx = (x_min - position_first[0])/(smth_length*kappa);
				helpy = (y_min - position_first[1])/(smth_length*kappa);
				to_cell = abs((int)helpy) * n_x + abs((int)helpx);

				//std::cout << "TO CELL2 : " << to_cell << " NUM OF CELLS: " << list_of_cells.size() << std::endl;
				//if(to_cell < 5000){std::cout << "SUCCES" << std::endl;}


				if(to_cell > num_of_cells || to_cell < 0){std::cout << "FATAL ERROR in to_cell2: " << to_cell << std::endl;}

				active_cells = {to_cell, to_cell-1, to_cell+1, to_cell-n_x-1, to_cell-n_x, to_cell-n_x+1, to_cell+n_x-1, to_cell+n_x, to_cell+n_x+1};

				//for(auto &c : active_cells){
				for(int c = 0; c < active_cells.size(); c++){
						//if(c < 0 || c > num_of_cells){continue;}
						if(active_cells[c] < 0 || active_cells[c] > num_of_cells){continue;}
						/*
						std::cout << "CELL: " << c << " LENGHT OF LIST OF CELLS: " << list_of_cells.size() << std::endl;
						std::cout << "CONTAINED PARTICLE SIZE: " << list_of_cells[c].get_contained_particles().size() << std::endl;
						if(list_of_cells[c].get_contained_particles().size() != 0){
						std::cout << "SUCCES: " << list_of_cells[c].get_contained_particles().size() << std::endl;
						}
						*/
						if(active_cells[c] < 0 || active_cells[c] > num_of_cells){std::cout << "FATAL ERROR in c: " << active_cells[c] << std::endl;}

						help_vector =  list_of_cells[active_cells[c]].get_contained_particles();
						//if(list_of_cells[c].get_contained_particles().empty()){continue;}

						//for(auto &id : help_vector){
						for (int p = 0; p < help_vector.size(); p++){

								//std::cout << "PARTICLE ID: " << id << " PARTICLE TOTAL: " << particle_list.size() <<std::endl;
								if(help_vector[p] > particle_list.size() || help_vector[p] < 0){std::cout << "FATAL ERROR in id: " << help_vector[p] << std::endl;}
								/*
								if(particle_list[i].get_ID_of_particle() == particle_list[help_vector[p]].get_ID_of_particle()){
										if(particle_list[i].get_ID_of_particle() == 1){
										std::cout << "Castice pusobi sama na sebe __ ID: " <<  particle_list[i].get_ID_of_particle() << \
												"," << particle_list[help_vector[p]].get_ID_of_particle() <<std::endl;
										}
								}
								*/

								position_second = particle_list[help_vector[p]].get_position();
								x = pow(position_first[0] - position_second[0], 2) +pow(position_first[1] - position_second[1], 2);
								particle_distance = sqrt( x );

								if (particle_distance < (kappa * smth_length)){

										//std::cout << "success" << std::endl;

										//kernel = smoothing_kernel_fix(particle_distance,smth_length);
										//kernel = smoothing_kernel_fix2(particle_distance,smth_length);
										kernel = smoothing_kernel_fix_Wendland(particle_distance,smth_length);

										position_dif[0] = position_first[0] - position_second[0];
										position_dif[1] = position_first[1] - position_second[1];


										//std::cout << "kernel: " << kernel[1] << " //// " << kernel[2] << std::endl;
										kernel[1] = kernel[1]*position_dif[0];
										kernel[2] = kernel[2]*position_dif[1];

										//particle_list[i].add_to_neighbours_list(particle_list[id].get_ID_of_particle() -1, \
												 kernel[0], kernel[1], kernel[2], position_dif);

										particle_list[i].add_to_neighbours_list(particle_list[help_vector[p]].get_ID_of_particle() -1 , \
												 kernel[0], kernel[1], kernel[2], position_dif);

								}
						}
				}
				//active_cells.clear();
		}

		for(auto &c : list_of_cells){
				c.clear_cell();
		}
}


