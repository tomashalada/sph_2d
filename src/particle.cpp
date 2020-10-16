#include "particle.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>
// -----------------------------------------------------------------------------------
// Konstruktory & destruktory

Particle::Particle(){
		this->particleID = 0; //toto by asi chtelo vylepsit pac to je cele spatne
		this->type = 0;
		this->position = {0., 0.};
		this->velocity = {0., 0.};
		this->mass = 1;
		this->p = 1;
		this->rho = 1;
		this->num_of_neighbours = 0;
		this->list_of_neighbours = {};
		this->neighbour_dist = {};
		this->kernel_W = {};
		this->kernel_dW_x = {};
		this->kernel_dW_y = {};

}

Particle::Particle(int particleID, int type, double m, double p, double rho, Eigen::Vector2d position, Eigen::Vector2d velocity){
		this->particleID = particleID; //toto by asi chtelo vylepsit pac to je cele spatne
		this->type = type;
		this->position = position;
		this->velocity = velocity;
		this->mass = m;
		this->p = p;
		this->rho = rho;
		this->num_of_neighbours = 0;
		this->list_of_neighbours = {};
		this->neighbour_dist = {};
		this->kernel_W = {};
		this->kernel_dW_x = {};
		this->kernel_dW_y = {};

}

Particle::~Particle(){

}

// -----------------------------------------------------------------------------------
// Metody

bool Particle::check_domain(std::array<double, 2> position, int height_domain, int width_domain){

		if(( position[0] > -1 && position[0] < width_domain) && (position[1] > -1 && position[1] < height_domain)){
				return true;
		}
		else{
				return false;
		}
}

void Particle::add_to_neighbours_list(int neighbour, double W, double dW_x, double dW_y, Eigen::Vector2d neib_dist){
		num_of_neighbours++;
		this->list_of_neighbours.push_back(neighbour);
		this->kernel_W.push_back(W);
		this->kernel_dW_x.push_back(dW_x);
		this->kernel_dW_y.push_back(dW_y);
		this->neighbour_dist.push_back(neib_dist);
		//std::cout << "pridavam castici " << num_of_neighbours << std::endl;
}

void Particle::finish_step(){

		//rho = 0;
		//acceleration = {0.,0.}; ..fuj to!

		num_of_neighbours = 0;
		list_of_neighbours.clear();
		kernel_W.clear();
		kernel_dW_x.clear();
		kernel_dW_y.clear();
		neighbour_dist.clear();
}

void Particle::size_of_vectors(){

		std::cout << "lbn " << list_of_neighbours.size() << std::endl;
		std::cout << "kernel :" << kernel_W.size() << std::endl;

		for (auto &i : list_of_neighbours){
				if(i > 899){
						//std::cout << "ERROR a" << std::endl;
						std::cout << i << std::endl;
				}
				if(i < 0){
						//std::cout << "ERROR b" << std::endl;
				}
		}
}

// -----------------------------------------------------------------------------------
// Settery a gettery

void Particle::set_position(Eigen::Vector2d position){
		this->position = position;
}

Eigen::Vector2d Particle::get_position(){
		return position;
}

void Particle::set_velocity(Eigen::Vector2d velocity){
		this->velocity = velocity;
}

Eigen::Vector2d Particle::get_velocity(){
		return velocity;
}

void Particle::set_velocity_last(Eigen::Vector2d velocity_last){
		this->velocity_last = velocity_last;
}

Eigen::Vector2d Particle::get_velocity_last(){
		return velocity_last;
}

void Particle::set_acceleration(Eigen::Vector2d acceleration){
		this->acceleration = acceleration;
}

Eigen::Vector2d Particle::get_acceleration(){
		return acceleration;
}

void Particle::set_mass(double m){
		this->mass = m;
}

double Particle::get_mass(){
		return mass;
}

void Particle::set_pressure(double p){
		this->p = p;
}

double Particle::get_pressure(){
		return p;
}

void Particle::set_density(double rho){
		this->rho = rho;
}

auto Particle::get_density() -> double&{
		return rho;
}

int Particle::get_type_of_particle(){
		return type;
}

int Particle::get_ID_of_particle(){
		return particleID;
}

int Particle::get_num_of_neighbours(){
		return num_of_neighbours;
}


