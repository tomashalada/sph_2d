// functions for creating boundary patches from input geometry (STL)

// should give patch objects to create_particles

#ifndef INPUT_GEOMETRY
#define INPUT_GEOMETRY

#include <iostream>
#include <vector>
#include <string>

#include "stl_reader.h"
#include "vertex.h"




void create_bounding_box();
std::vector<Vertex> get_verteces(std::string solid_name, bool two_dimensions);

#endif
