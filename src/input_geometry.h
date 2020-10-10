// functions for creating boundary patches from input geometry (STL)

// should give patch objects to create_particles library

#ifndef INPUT_GEOMETRY
#define INPUT_GEOMETRY

#include <iostream>
#include <vector>
#include <string>

#include "stl_reader.h"
#include "vertex.h"
#include "trig.h"


// for creating extern boundary of computational domain (only quadrateral now)
void create_bounding_box();
void create_wall();

void cw();

// reads verteces from STL file, returns vector of Vertex object (float x, float y, float z)
// for 2D (two_dimensions == true), z is equal to 0
std::vector<Vertex> get_verteces(std::string solid_name, bool two_dimensions);
std::vector<Trig> get_trigs(std::string solid_name);


std::vector<Vertex> mesh_trig_ico(Trig input_trig,int levels);
std::vector<Trig> ico_recursive(std::vector<Trig> trigs);


Vertex get_middle_point(Vertex v1, Vertex v2);

#endif
