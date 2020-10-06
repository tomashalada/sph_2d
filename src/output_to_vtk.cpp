#include "particle.h"
#include <iostream>
#include <vector>
#include <fstream>

void Output_to_VTK(std::vector<Particle> particles){
		std::cout << "output_to_VTK" << std::endl;
}

// QUEST no. 1:
/*
		Taaakze, je hotova inicializace castic, nejak. Inicializuje to malou krabici a v ni nejakej
		blok vody, zatim pouze par castic pro testovani.

		Je potreba udelat output do .vtk souboru at si to pak pekne muzeme prohlizet v
		paraview. Koukni se do:

		particle.h
		particle.cpp

		kde je zadefinovata castice jako objekt. Castice ma polohu, rychlost, hustotu a tlak a
		to jsou veci ktere chceme v paraview zobrazovat.

		particle.cpp - zde jsou metody ktere umoznuji pristup k
		- poloze, rychlosti, tlaku, hustote etc.

		std::array<double, 2> Particle::get_position(){
		return position;
		}


		std::array<double, 2> Particle::get_velocity(){
		return velocity;
		}


		double Particle::get_pressure(){
		return p;
		}	

		double Particle::get_density(){
		return rho;
		}

		atd. Bacha na to, ze ty castice jsou body a nemuzes mezi nima interpolovat jako kdyz mas vypocetni
		sit. Treba kdyz to tam pak bude splouchat, tak aby v tom paraview byla videt ta vlna a ne aby to ten
		prazdny prostor mezi vlnou a tekutinou nejak spojite vybarvilo. Jsem si jist, ze si nejak poradis. xD

		


*/
void write_to_CSV(std::vector<Particle> particle_list, int &particle_total){

	std::ofstream file;
	file.open("particles.csv");
	file << "particle ID,x,y,vx,vy,pressure,density" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_ID_of_particle() << "," << part.get_position()[0] << "," << part.get_position()[1] << "," << part.get_velocity()[0] << "," << part.get_velocity()[1] << "," << part.get_pressure() << "," << part.get_density() << std::endl;
	}
	file.close();
}
void write_to_ASCII_VTK(std::vector<Particle> particle_list, int &particle_total){
	std::ofstream file;
	file.open("particles.vtk");

//	file header
	file << "# vtk DataFile Version 3.0" << std::endl << "vtk output" << std::endl << "ASCII" << std::endl << "DATASET POLYDATA" << std::endl;

//      point coordinates list
	file << "POINTS " << particle_total << " float" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_position()[0] << " " << part.get_position()[1] << " 1" << std::endl;
	}

//	data fields
	file << "POINT_DATA " << particle_total << std::endl << "FIELDS FieldData 3" << std::endl;
	file << "pressure 1 " << particle_total << " float" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_pressure() << std::endl;
	}

	file << "density 1 " << particle_total << " float" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_density() << std::endl;
	}

	file << "velocity 3 " << particle_total << " float" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_velocity()[0] << " " << part.get_velocity()[1] << " 0" << std::endl;
	}
	
	file.close();

}

