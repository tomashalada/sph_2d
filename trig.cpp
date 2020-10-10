

#include <iostream>

#include "trig.h"


Trig::Trig(){
}
Trig::Trig(std::vector<Vertex> verteces){
	this->verteces = verteces;
}
Trig::~Trig(){
}

void Trig::print_triangle(int index){
	std::cout << "Triangle n. " << index << " : ";
	for(int i = 0;i<3;i++){
		verteces[i].print_vertex();
		std::cout << " ";	
	}
	std::cout << std::endl;
}
Vertex Trig::get_vertex(int index){
	return verteces[index];
}


