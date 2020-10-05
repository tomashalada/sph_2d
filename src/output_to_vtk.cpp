#include "particle.h"
#include <iostream>
#include <vector>

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
