#include <vector>
#include <iostream>
#include <string>

#include "input_geometry.h"
#include "vertex.h"
#include "output_to_vtk.h"

void create_bounding_box (){
	std::vector<Vertex> verteces;
	std::string solid_name = "test.stl";

	verteces = get_verteces(solid_name,false);

	std::cout << "number of verteces in vector: " << verteces.size() << std::endl;

	for(int vertex;vertex<verteces.size();vertex++){
		std::cout << "vertex n. " << vertex << " : " << verteces[vertex].get_x() << ", " << verteces[vertex].get_y() << ", " << verteces[vertex].get_z() << std::endl;
	}
}
void cw(){

}

void create_wall() {
	std::cout << "creating wall..." << std::endl;
	std::string solid_name = "test.stl";
	std::vector<Trig> trigs;
	std::vector<Vertex> particles;
	std::vector<Particle> final;
	std::array<double,2> def_velocity = {0,0};

	trigs = get_trigs(solid_name);
	for(int i =0;i < trigs.size();i++){
		trigs[i].print_triangle(i);
	}

	for(Trig &defTrig : trigs){
		std::vector<Vertex> new_particles;

		new_particles = mesh_trig_ico(defTrig, 1);
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());

	}

	std::cout << "...done" << std::endl;

	int index = 0;
	for(Vertex &vertex : particles){
		Particle p(index,0,0,0,0,vertex.get_2D_pos_array(),def_velocity);
		final.push_back(p);
		index++;
	}
	write_to_ASCII_VTK(final,index,"meshed.vtk");
}

std::vector<Vertex> mesh_trig_ico(Trig input_trig,int levels){
	std::vector<Vertex> particles_output;

	std::vector<Trig> triangles_for_meshing;

	triangles_for_meshing.push_back(input_trig);
	int number_of_particles = 3;
	for(int lev = 0; lev < levels; lev++){

		std::vector<Trig> new_triangles;
		new_triangles = ico_recursive(triangles_for_meshing);
		for(Trig &t : new_triangles) t.print_triangle(0);
		triangles_for_meshing.insert(triangles_for_meshing.end(), new_triangles.begin(), new_triangles.end());
	}

	std::cout << "size in mesh_trig_ico(): " << particles_output.size() << std::endl;
	return particles_output;

}

// returns vector of new triangles created in input_trig
std::vector<Trig> ico_recursive(std::vector<Trig> trigs){
	std::vector<Trig> new_trigs;


	//creates new triangle
	for(Trig &trig : trigs){
		std::vector<Vertex> new_verteces;

		for(int i = 0; i < 3; i++){
			Vertex v = trig.get_vertex(i);
		}
		Vertex v1 = trig.get_vertex(0);
		Vertex v2 = trig.get_vertex(1);
		Vertex v3 = trig.get_vertex(2);
		Vertex vn1 = get_middle_point(v1,v2);
		new_verteces.push_back(vn1);
		Vertex vn2 = get_middle_point(v2,v3);
		new_verteces.push_back(vn2);
		Vertex vn3 = get_middle_point(v3,v1);
		new_verteces.push_back(vn3);
		Trig ntrig(new_verteces);

		new_trigs.push_back(ntrig);

		//ntrig.print_triangle(0);
	}
	std::cout << "size in ico_recursive(): " << new_trigs.size() << std::endl;

	return new_trigs;
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
std::vector<Trig> get_trigs(std::string solid_name){
	std::vector<Trig> trigs;
	try {
		stl_reader::StlMesh <float, unsigned int> mesh (solid_name);
		for(size_t isolid = 0; isolid < mesh.num_solids(); ++isolid) {

     		for(int itrig = 0; itrig < mesh.num_tris(); ++itrig) {

     			const unsigned int* f = mesh.tri_corner_inds(itrig);
     			std::vector<Vertex> verteces;
     			for(size_t icorner = 0; icorner < 3; ++icorner){

     				Vertex v(mesh.vrt_coords (f[icorner])[0],	mesh.vrt_coords (f[icorner])[1],	mesh.vrt_coords (f[icorner])[2]);
     				verteces.push_back(v);
     			}

     			Trig t(verteces);
				trigs.push_back(t);
				verteces.clear();
    	  }


}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;

	}
	return trigs;
}
Vertex get_middle_point(Vertex v1, Vertex v2){
	Vertex res;
	res.set_x((v1.get_x() + v1.get_x()) / 2.);
	res.set_y((v1.get_y() + v2.get_y()) / 2.);
	res.set_z((v1.get_z() + v2.get_z()) / 2.);
	return res;
}
