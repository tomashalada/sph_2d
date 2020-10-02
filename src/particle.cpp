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
		this->particleID = 0; //toto by asi chtelo vylepsit pac to je cele spatne
		this->type = 0;
		this->position = {0., 0.};
		this->velocity = {0., 0.};
		this->p = 1;
		this->rho = 1;

}

Particle::~Particle(){

}

// -----------------------------------------------------------------------------------
// Inicializace castic
//void Particle::Create_particles(std::vector<Particle> particles){
//
//}
//
//
//// Nalezeni paru interagujicich castic
//void Particle::Find_pairs(std::vector<Particle> particles){
//}
//
//// Nalezeni paru interagujicich castic
//void Particle::Output_to_VTK(std::vector<Particle> particles){
//
//
//}
//
//// Vypocet hustoty
//void Particle::Compute_density(std::vector<Particle> particles){
//
//
//}
//
//// Vypocet tlaku
//void Particle::Compute_pressure(std::vector<Particle> particles){
//
//
//}
//
//// Vypocet zrychleni castic
//void Particle::Compute_acceleration(std::vector<Particle> particles){
//
//
//}
//
//// Vypocet zrychleni castic
//void Particle::Compute_artificial_viscosity(std::vector<Particle> particles){
//
//
//}

