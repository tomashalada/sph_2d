

#include <iostream>

#include "trig.h"
#include "vertex.h"

Trig::Trig(){
}
Trig::Trig(std::vector<Vertex> verteces){
	this->verteces = verteces;
}
Trig::Trig(Vertex v1, Vertex v2, Vertex v3){
	this->verteces.push_back(v1);
	this->verteces.push_back(v2);
	this->verteces.push_back(v3);
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


