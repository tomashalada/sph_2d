#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class Parameter{
	private:

		std::string name;
		std::string value;
		std::vector<std::string> value_list;

	public:
	
		Parameter();
		Parameter(std::string name, std::string value, std::vector<std::string> value_list);
		~Parameter();
		std::string get_name();
		std::string get_value();
		std::vector<std::string> get_value_list();
};
class Block{
	private:
		std::string name;
		std::vector<Parameter> parameters; 	
		std::vector<std::string> keywords;		
	
	public:
		Block(std::string name);
		Block(std::string name, std::vector<Parameter> parameters);
		~Block();
		std::string get_name();
		std::vector<Parameter> get_parameters();
		void set_parameters(std::vector<std::string> p);

};
class Input_file{
	private:
		std::string name;
		std::vector<Block> blocks;
		std::vector<std::string> options;

	public:
		Input_file();
		Input_file(std::string name, std::vector<Block> blocks);
		~Input_file();
		std::string get_name();
		std::vector<Block> get_blocks();

};
class Input{
	private:
		const std::vector<std::string> file_list = {"main.sph","mesh.sph","boundary.sph"};
		//Input_file main(std::vector<std::string> s = {"main","time_control"});


};

class Patch{
	private:
		std::string name;
	public:
		Patch(std::string name);
		std::string get_name();
};
class Patch_group{
	private:
		std::string name;
		std::vector<std::string> s_patches;
		std::vector<Patch> patches;

	public:
		Patch_group(std::string name);
		void add_patch(std::string s);
		void add_patches(std::vector<Patch> new_patches);
		std::string get_name();
		void print_patches();
		void print_group();
};

void load_parameters();
void read_values();
void load_patches();

std::vector<std::string> read_block_names(std::string file_name);
std::vector<std::string> get_patch_group_elements(std::string line);

std::string clear_white_spaces(std::string);
std::array<std::string,2> split_string(std::string, char c);
bool is_block_name(std::string s);
std::vector<Input_file> read_file(std::string file_name);
void set_values();
std::vector<std::string> read_block_names(std::string file_name);




#endif
