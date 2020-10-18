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

void create_wall(std::string input_file_name, std::string output_file_name, int levels) {
	std::cout << "creating wall..." << std::endl;
	std::vector<Trig> trigs;
	std::vector<Vertex> particles;
	std::vector<Particle> final;
	Eigen::Vector2d def_velocity = {0,0};

	trigs = get_trigs(input_file_name);
	for(int i =0;i < trigs.size();i++){
		trigs[i].print_triangle(i);
	}

	for(Trig &defTrig : trigs){
		std::vector<Vertex> new_particles;

		new_particles = mesh_trig_ico(defTrig, levels);
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());

	}

	std::cout << "...done" << std::endl;
	std::cout << "number of final particles: " << particles.size() << std::endl;

	// writing to VTK
	/*
	int index = 0;
	for(Vertex &vertex : particles){
		Particle p(index,0,0,0,vertex.get_2D_pos_array(),def_velocity);

		final.push_back(p);
		index++;
	}
	write_to_ASCII_VTK(final,index,"meshed.vtk");
	*/
	write_mesh_to_ASCII_VTK(particles,output_file_name);

	//write_verteces_to_CSV(particles,"verteces.csv");
}


// gets 1 STL triangle, returns vector of particles
std::vector<Vertex> mesh_trig_ico(Trig input_trig,int levels){
	std::vector<Vertex> particles_output;

	std::vector<Trig> triangles_for_meshing;

	triangles_for_meshing.push_back(input_trig);
	int number_of_particles = 3;
	for(int lev = 0; lev < levels; lev++){
		int index = 0;
		std::vector<Trig> new_triangles;
		new_triangles = ico_recursive(triangles_for_meshing);
		for(Trig &t : new_triangles) {
			t.print_triangle(index);
			index++;
		}

		triangles_for_meshing.insert(triangles_for_meshing.end(), new_triangles.begin(), new_triangles.end());
	}

	std::cout << "size in mesh_trig_ico(): " << triangles_for_meshing.size() << std::endl;

	for(Trig &transfer : triangles_for_meshing){
		for(int i=0;i<3;i++) particles_output.push_back(transfer.get_vertex(i));
	}

	std::cout << "number of returning verteces in mesh_trig_ico(): " << particles_output.size() << std::endl;
	return particles_output;

}

// returns vector of new triangles created in input_trig
std::vector<Trig> ico_recursive(std::vector<Trig> trigs){
	std::vector<Trig> new_trigs;


	//creates new triangle
	for(Trig &trig : trigs){
		std::vector<Vertex> new_verteces;

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

		v1.print_vertex();
		v2.print_vertex();
		v3.print_vertex();
		std::cout << std::endl;

		for(Vertex &v : new_verteces){
			v.print_vertex();
		}
		std::cout << std::endl;

		Trig t1(v1,vn1,vn3);
		Trig t2(vn1,v2,vn2);
		Trig t3(v3,vn3,vn2);

		new_trigs.push_back(ntrig);
		new_trigs.push_back(t1);
		new_trigs.push_back(t2);
		new_trigs.push_back(t3);

		//ntrig.print_triangle(0);
	}
	std::cout << "number of triangles returning from ico_recursive(): " << new_trigs.size() << std::endl;

	return new_trigs;
}

void test_meshing(){
	Vertex v1(0,0,0);
	Vertex v2(1,0,0);
	Vertex v3(0,1,0);

	std::vector<Vertex> result_verteces;
	std::vector<Particle> final;
	Eigen::Vector2d def_velocity = {0,0};
	Trig test_trig(v1,v2,v3);
	result_verteces = mesh_trig_ico(test_trig,1);

	int index = 0;
	for(Vertex &vertex : result_verteces){
		Particle p(index,0,0,0,0,vertex.get_2D_pos_array(),def_velocity);

		final.push_back(p);
		index++;
	}
	write_to_ASCII_VTK(final,index,"test_trig.vtk");
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
	res.set_x((v1.get_x() + v2.get_x()) / 2.);
	res.set_y((v1.get_y() + v2.get_y()) / 2.);
	res.set_z((v1.get_z() + v2.get_z()) / 2.);
	return res;
}
