#include <iostream>

#include "vertex.h"

Vertex::Vertex(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vertex::Vertex(float _x, float y){
	x = _x;
	this->y = y;
	this->z = 0;
}
Vertex::Vertex(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}
Vertex::~Vertex(){
	
}

float Vertex::get_x(){
	return x;
}
void Vertex::set_x(float x){
	this->x = x;
}

float Vertex::get_y(){
	return y;
}
void Vertex::set_y(float y){
	this->y = y;
}

float Vertex::get_z(){
	return z;
}
void Vertex::set_z(float z){
	this->z = z;
}

void Vertex::print_vertex(){
	std::cout << "(" << x << ", " << y << ", " << z << ")";
}
