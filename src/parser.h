#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>


void read_values();
std::string clear_white_spaces(std::string);
bool is_block_name(std::string s);

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
			
	public:
		Block();
		Block(std::string name, std::vector<Parameter> parameters);
		~Block();
		std::string get_name();
		std::vector<Parameter> get_parameters();

};
class Input_file{
	private:
		std::string name;
		std::vector<Block> blocks;

	public:
		Input_file(std::string name, std::vector<Block> blocks);
		~Input_file();
		std::string get_name();
		std::vector<Block> get_blocks();

};



#endif
