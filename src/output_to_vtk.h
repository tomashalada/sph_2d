#ifndef OUTUP_TO_VTK_H
#define OUTUP_TO_VTK_H

#include <fstream>
#include <string>

#include "particle.h"
#include "vertex.h"

void Output_to_VTK(std::vector<Particle> particles);
void write_to_CSV(std::vector<Particle> particle_list, int &particle_total);
void write_verteces_to_CSV(std::vector<Vertex> particle_list,std::string output_file_name);
void write_to_ASCII_VTK(std::vector<Particle> particle_list, int &particle_total,std::string output_file_name);
void write_mesh_to_ASCII_VTK(std::vector<Vertex> vertex_list, std::string output_file_name);
void write_raw_mesh(std::vector<Vertex> input_particles,std::string output_file_name,bool two_dimensional);

#endif
