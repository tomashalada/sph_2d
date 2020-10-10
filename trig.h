#ifndef TRIG
#define TRIG

#include <vector>
#include <iostream>

#include "vertex.h"


class Trig{
	private:
		
		std::vector<Vertex> verteces;
		
	public:
		Trig();
		Trig(std::vector<Vertex> verteces);
		~Trig();
		
		Vertex get_vertex(int index);
		void print_triangle(int index);
};

#endif
