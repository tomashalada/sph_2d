#include "particle.h"
#include <iostream>
#include <vector>
#include <cmath>

void Particle::Compute_artificial_viscosity(std::vector<Particle> &particle_list, double smth_length, double mass, std::array<double, 2> forces){

		//
		double alpha = 1;
		double epsilon = 0.01;

		double v_dot_r;
		double vel_tempx;
		double vel_tempy;

		double c_ab = 40.;
		double mu;
		double rho_avg;
		double neighbour_dist_kvadr;
		double artif;

		double r_ab_test;
		double denominator;

		std::array<double, 2> av_help;
		std::array<double, 2> av_new;
		//artif_acc = {0., 0.};
		//double VISC_LAP = 45.f/(M_PI*pow(smth_length, 6.f))*0.01;

		for(unsigned i = 0; i < num_of_neighbours; i++) {

				//v_dot_r = position[0]*particle_list[list_of_neighbours[i]]
				vel_tempx = velocity[0] - particle_list[list_of_neighbours[i]].get_velocity()[0];
				vel_tempy = velocity[1] - particle_list[list_of_neighbours[i]].get_velocity()[1];

				v_dot_r = vel_tempx*neighbour_dist[i][0] + vel_tempy * neighbour_dist[i][1];
				neighbour_dist_kvadr = pow(neighbour_dist[i][0],2) + pow(neighbour_dist[i][1], 2);

				//kontrola
				r_ab_test = pow(position[0] - particle_list[list_of_neighbours[i]].get_position()[0],2) + \
										pow(position[1] - particle_list[list_of_neighbours[i]].get_position()[1],2);

				//fvisc += VISC*MASS*(pj.v - pi.v)/pj.rho * VISC_LAP*(H-r);
				//av_new[0] = mass * VISC_LAP * vel_tempx* (smth_length - neighbour_dist[i][0]) / (rho + particle_list[list_of_neighbours[i]].get_density());
				//av_new[1] = mass * VISC_LAP * vel_tempy* (smth_length - neighbour_dist[i][1]) / (rho + particle_list[list_of_neighbours[i]].get_density());


				//std::cout << "__compute_artif_acc__ dist_kvadr: " << neighbour_dist_kvadr << std::endl;
				//std::cout << "__compute_artif_acc__ dist_test: " << r_ab_test << std::endl;
				//std::cout << std::endl;

				//std::cout << "__compute_artif_acc__ pos_dif_class x: " << neighbour_dist[i][0] << std::endl;
				//std::cout << "__compute_artif_acc__ pos_dif_computed x: " << position[0] - particle_list[list_of_neighbours[i]].get_position()[0] << std::endl;

				//std::cout << "__compute_artif_acc__ pos_dif_class y: " << neighbour_dist[i][1] << std::endl;
				//std::cout << "__compute_artif_acc__ pos_dif_computed y: " << position[1] - particle_list[list_of_neighbours[i]].get_position()[1] << std::endl;

						artif_acc[0] = artif_acc[0] - av_new[0];
						artif_acc[1] = artif_acc[1] - av_new[1];



				if(v_dot_r < 0){

						rho_avg = 0.5*(rho + particle_list[list_of_neighbours[i]].get_density());
						mu = smth_length * v_dot_r / (neighbour_dist_kvadr + epsilon);
						artif = -alpha*c_ab*mu/rho_avg;

						//v_dot_r = vel_tempx*neighbour_dist[i][0] + vel_tempy * neighbour_dist[i][1];

						//av_new[0] = 2*0.001* vel_tempx* neighbour_dist[i][0] / (pow(rho_avg, 2) * neighbour_dist_kvadr + pow(smth_length,2)*epsilon);
						//av_new[1] = 2*0.001* vel_tempy* neighbour_dist[i][1] / (pow(rho_avg, 2) * neighbour_dist_kvadr + pow(smth_length,2)*epsilon);

						//artif_acc[0] = artif_acc[0] - kernel_dW_x[i]*artif*mass;
						//artif_acc[1] = artif_acc[1] - kernel_dW_y[i]*artif*mass;

						//av_help[0] =
						av_help[0] = particle_list[list_of_neighbours[i]].get_artif_acc()[0] - kernel_dW_x[i]*artif*mass;
						av_help[1] = particle_list[list_of_neighbours[i]].get_artif_acc()[1] - kernel_dW_y[i]*artif*mass;


				//acceleration[0] = acceleration[0] + kernel_dW_x[i]*p_temp*mass;
				//acceleration[1] = acceleration[1] + kernel_dW_y[i]*p_temp*mass;

				//acc_help[0] = particle_list[list_of_neighbours[i]].get_acceleration()[0] - kernel_dW_x[i]*p_temp*mass;
				//acc_help[1] = particle_list[list_of_neighbours[i]].get_acceleration()[1] - kernel_dW_y[i]*p_temp*mass;
				//article_list[list_of_neighbours[i]].set_acceleration(acc_help);

				}

		}
		//acceleration[0] = artif_acc[0] + forces[0];
		//acceleration[1] = artif_acc[1] + forces[1];

}


//	double pi;
//	double pi_reunit; //Pomocny parametr, umela viskozita prenasobena derivaci jadra a hmotnosti, aby ji bylo mozne primo pricist ke zrcyhleni a energii - toto asi taky jeste upravit
//
//	for(int i = 0; i < n; i++){
//		particleList[i].set_ac_v(0.);
//		particleList[i].set_ec_v(0.);
//	}
//	for(int q = 0; q < pairs; q ++){
//		int i = i_ptcs[q];
//		int j = j_ptcs[q];
//		dr = particleList[i].get_poss() - particleList[j].get_poss();
//		dv = particleList[i].get_vel() - particleList[j].get_vel();
//		if((dr*dv) < 0){
//			uavg = 0.5*(particleList[i].get_dens() + particleList[j].get_dens());
//			cavg = 0.5*(sqrt(kappa*particleList[i].get_pressure()/particleList[i].get_dens()) + sqrt(kappa*particleList[j].get_pressure()/particleList[j].get_dens()));
//			theta = (h*dr*dv)/(dr*dr + h*h*epsilon*epsilon);
//
//			pi = ((beta*theta - alfa*cavg)*theta)/uavg;
//			pi_reunit = -pi*m*dW[q];
//
//			particleList[i].set_ac_v(particleList[i].get_ac_v() + pi_reunit);
//			particleList[j].set_ac_v(particleList[j].get_ac_v() - pi_reunit);
//			particleList[i].set_ec_v(particleList[i].get_ec_v() + 0.5 * dv * pi_reunit);
//			particleList[j].set_ec_v(particleList[j].get_ec_v() + 0.5 * dv * pi_reunit);
//		}
//	}
//}

