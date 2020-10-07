#include <vector>
#include <iostream>
#include <string>

#include "input_geometry.h"
#include "vertex.h"


void create_bounding_box (){ 
	std::vector<Vertex> verteces;
	std::string solid_name = "test.stl";
	
	verteces = get_verteces(solid_name,true);
	
	std::cout << "number of verteces in vector: " << verteces.size() << std::endl;
	
	for(int vertex;vertex<verteces.size();vertex++){
		std::cout << "vertex n. " << vertex << " : " << verteces[vertex].get_x() << ", " << verteces[vertex].get_y() << ", " << verteces[vertex].get_z() << std::endl; 
	}
	
	
	
}

std::vector<Vertex> get_verteces(std::string solid_name, bool two_dimensions){
	std::vector<Vertex> verteces;

	try {
		stl_reader::StlMesh <float, unsigned int> mesh (solid_name);
		for(size_t isolid = 0; isolid < mesh.num_solids(); ++isolid) {
			
			for(int vertex_index = 0; vertex_index < mesh.num_vrts(); vertex_index++){
				if(two_dimensions && mesh.vrt_coords(vertex_index)[2] == 0){
				
				Vertex v(mesh.vrt_coords(vertex_index)[0],mesh.vrt_coords(vertex_index)[1]);
				verteces.push_back(v);
				}
				else{
				Vertex v(mesh.vrt_coords(vertex_index)[0],mesh.vrt_coords(vertex_index)[1],mesh.vrt_coords(vertex_index)[2]);
				verteces.push_back(v);
				}
			}


}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;

	}
	return verteces;
}
