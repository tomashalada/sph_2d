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
float Vertex::get_y(){
	return y;
}
float Vertex::get_z(){
	return z;
}
