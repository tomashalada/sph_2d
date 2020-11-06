#ifndef CELL_LL_H
#define CELL_LL_H

#include "particle.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>

class Cell_LL{

		private:
		// parametry bunky
		int cell_id;
		double edge_length;
		std::array<double, 2> left_bottom_corner_poss;

		// castice v bunce
		int num_of_part_in_cell;
		std::vector<int> contained_particle; //ID castic obsazenych v dane bunce

		public:
		// konstruktory, destruktory
		Cell_LL(double edge_length);
		//~Cell_LL();

		// metody
		void add_particle(int part_id);
		void clear_cell();

		// settery, gettery
		void set_cell_id(int cell_id);
		int get_cell_id();

		void set_edge_length(double edge_length);
		double get_edge_length();

		void set_lbc_poss(std::array<double,2> left_bottom_corner_poss);
		std::array<double, 2> get_lbc_poss();

		std::vector<int> get_contained_particles();

};

#endif
