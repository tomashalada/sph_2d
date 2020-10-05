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
		this->p = 1;
		this->rho = 1;

}

Particle::Particle(int particleID, int type, double p, double rho, std::array<double, 2> position, std::array<double, 2> velocity){
		this->particleID = particleID; //toto by asi chtelo vylepsit pac to je cele spatne
		this->type = type;
		this->position = position;
		this->velocity = velocity;
		this->p = p;
		this->rho = rho;

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

void Particle::add_to_neighbours_list(int neighbour){
		num_of_neighbours++;
		this->list_of_neighbours.push_back(neighbour);
}

// -----------------------------------------------------------------------------------
// Settery a gettery

void Particle::set_position(std::array<double, 2> velocity){
		this->velocity = velocity;
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

void Particle::set_pressure(double p){
		this->p = p;
}

double Particle::get_pressure(){
		return p;
}

void Particle::set_density(double rho){
		this->rho = rho;
}

double Particle::get_density(){
		return rho;
}

int Particle::get_type_of_particle(){
		return type;
}

int Particle::get_ID_of_particle(){
		return particleID;
}


