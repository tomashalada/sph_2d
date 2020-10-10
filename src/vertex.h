
//Class for vertex from STL mesh

#ifndef VERTEX
#define VERTEX

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
		
		void print_vertex();
};


#endif
