#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "particle.h"
#include "vertex.h"

void Output_to_VTK(std::vector<Particle> particles){
		std::cout << "output_to_VTK" << std::endl;
}

void write_to_CSV(std::vector<Particle> particle_list, int &particle_total){

	std::ofstream file;
	file.open("particles.csv");
	file << "particle ID,x,y,vx,vy,pressure,density" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_ID_of_particle() << "," << part.get_position()[0] << "," << part.get_position()[1] << "," << part.get_velocity()[0] << "," << part.get_velocity()[1] << "," << part.get_pressure() << "," << part.get_density() << std::endl;
	}
	file.close();
}
void write_verteces_to_CSV(std::vector<Vertex> particle_list,std::string output_file_name){

	std::ofstream file;
	file.open(output_file_name);
	int index = 0;
	file << "particle ID,x,y,z,vx,vy,vz,pressure,density" << std::endl;
	for(Vertex &vert : particle_list){
		file << index << "," << vert.get_x() << "," << vert.get_y() << "," << vert.get_z() << "," << "0,0,0,0,0" << std::endl;
		index++;
	}
	file.close();
}
void write_to_ASCII_VTK(std::vector<Particle> particle_list, int &particle_total,std::string output_file_name){
	std::ofstream file;
	file.open(output_file_name);

//	file header
	file << "# vtk DataFile Version 3.0" << std::endl << "vtk output" << std::endl << "ASCII" << std::endl << "DATASET POLYDATA" << std::endl;

//      point coordinates list
	file << "POINTS " << particle_total << " float" << std::endl;
	for(Particle &part : particle_list){
		file << part.get_position()[0] << " " << part.get_position()[1] << " 0" << std::endl;
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
void write_mesh_to_ASCII_VTK(std::vector<Vertex> vertex_list, std::string output_file_name){
	std::ofstream file;
	file.open(output_file_name);

//	file header
	file << "# vtk DataFile Version 3.0" << std::endl << "vtk output" << std::endl << "ASCII" << std::endl << "DATASET POLYDATA" << std::endl;

//      point coordinates list
	file << "POINTS " << vertex_list.size() << " float" << std::endl;
	for(Vertex &vert : vertex_list){
		file << vert.get_x() << " " << vert.get_y() << " " << vert.get_z() << std::endl;
	}
	file.close();
}
void write_raw_mesh(std::vector<Vertex> input_particles, std::string output_file_name, bool two_dimensional){
	std::cout << "writing raw mesh..." << std::endl;

	std::vector<Particle> output_particles;
	std::array<double,2> def_velocity = {0,0};
	int index = 0;
	for(Vertex &vertex : input_particles){
		if(two_dimensional && vertex.get_z() == 0){
			Particle p(index,0,0,0,0,vertex.get_2D_pos_array(),def_velocity);
			output_particles.push_back(p);
			index++;
		}
		else{
			std::cout << "3D particle not yet implemented !" << std::endl;

		}
	}
	write_to_ASCII_VTK(output_particles,index,output_file_name);
	std::cout << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << "VTK WRITE PARAMETERS:" << std::endl;
	std::cout << "Detected particles to write in input particle vector: " << input_particles.size() << std::endl;
	std::cout << "2D mode: ";
	if(two_dimensional) std::cout << "ON" << std::endl;
	else std::cout << "OFF" << std::endl;
	std::cout << "Particles written in VTK file: " << index << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << "Write done" << std::endl;
	std::cout << std::endl;
}

