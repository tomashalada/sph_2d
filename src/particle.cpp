#include "particle.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>

// -----------------------------------------------------------------------------------
// Konstruktory & destruktory

Particle::Particle(int particleID, int type, double m, double p, double rho, std::array<double, 2> position, std::array<double, 2> velocity){
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

void Particle::add_to_neighbours_list(int neighbour, double W, double dW_x, double dW_y, std::array<double, 2> neib_dist){
		num_of_neighbours++;
		this->list_of_neighbours.push_back(neighbour);
		this->kernel_W.push_back(W);
		this->kernel_dW_x.push_back(dW_x);
		this->kernel_dW_y.push_back(dW_y);
		this->neighbour_dist.push_back(neib_dist);
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

// .. nahodna testovaci funkce
void Particle::size_of_vectors(){
		std::cout << "List_of_neighbours: " << list_of_neighbours.size() << std::endl;
		std::cout << "Kernel: " << kernel_W.size() << std::endl;
}

// -----------------------------------------------------------------------------------
// Settery a gettery

void Particle::set_position(std::array<double, 2> position){
		this->position = position;
}

std::array<double, 2> Particle::get_position(){
		return position;
}

void Particle::set_velocity(std::array<double, 2> velocity){
		this->velocity = velocity;
}

std::array<double, 2> Particle::get_velocity(){
		return velocity;
}

void Particle::set_velocity_last(std::array<double, 2> velocity_last){
		this->velocity_last = velocity_last;
}

std::array<double, 2> Particle::get_velocity_last(){
		return velocity_last;
}

void Particle::set_acceleration(std::array<double, 2> acceleration){
		this->acceleration = acceleration;
}

std::array<double, 2> Particle::get_acceleration(){
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

void Particle::set_density_change(double drho){
		this->drho = drho;
}

auto Particle::get_density_change() -> double&{
		return drho;
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


