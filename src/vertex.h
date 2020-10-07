
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
		float get_y();
		float get_z();
};


#endif
