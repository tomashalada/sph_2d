#include "cell_ll.h"
#include "particle.h"

#include <vector>


Cell_LL::Cell_LL(double edge_length){
		this->cell_id = 0;
		this->edge_length = 0;
		this->left_bottom_corner_poss = {0.,0.};
		this->num_of_part_in_cell = 0;
		this->contained_particle = {};

}
/*
Cell_LL::~Cell_LL(){

}
*/
void Cell_LL::add_particle(int part_id){

		this->contained_particle.push_back(part_id);
		num_of_part_in_cell++;
		//if(num_of_part_in_cell > 100){std::cout << "ERROR in particle in cells: " << num_of_part_in_cell << std::endl;}

}

void Cell_LL::clear_cell(){
		contained_particle.clear();
		num_of_part_in_cell = 0;
		//std::cout << "CELARING CELLS" << std::endl;
}


void Cell_LL::set_cell_id(int cell_id){
		this->cell_id = cell_id;
}

int Cell_LL::get_cell_id(){
		return cell_id;
}

std::vector<int> Cell_LL::get_contained_particles(){
		return contained_particle;
}

