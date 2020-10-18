
//Class for vertex from STL mesh

#ifndef VERTEX
#define VERTEX

#include <array>
#include <eigen3/Eigen/Dense>

class Vertex{
	private:

		float x;
		float y;
		float z;

	public:
		Vertex();
		Vertex(float x, float y);
		Vertex(float x, float y, float z);

		~Vertex();

		float get_x();
		void set_x(float x);
		float get_y();
		void set_y(float y);
		float get_z();
		void set_z(float z);

		Eigen::Vector2d get_2D_pos_array();
		Eigen::Vector3d get_pos_array();
		void print_vertex();
};


#endif
