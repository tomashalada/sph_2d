#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "parser.h"

void read_values(){
	std::string file_name = "main.sph";
	std::ifstream setup_file(file_name);
	std::string line;
	int line_index = 1;	

	std::array<std::string,2> dimension_options = {"2","3"};

	std::map<std::string, std::string > options = {
		{"dimensions", "2"},
		{"startTime", "0"},
		{"endTime", "0"},
		{"boundary-type","empty"},
	};

	std::map<std::string, std::vector<std::string> > options_values = {
		{"dimensions", {"2","3"}},
		{"boundary-type", {"wall","inlet","outlet"}},
	};

	struct {
		std::array<double,3> start;
		std::array<double,3> end;
	} two_point_line;


	if(setup_file.fail()){
		std::cout << "Setup file " << file_name << " does not exist!" << std::endl;  
	}

	while(std::getline(setup_file, line)){
		std::istringstream iss(line);
		std::string name, div, value;

		if(line[0] && line[1] != '/'){
			if(std::getline(iss, name, '=')){
				if(std::getline(iss, value)){
					if(options.find(name) != options.end()){
						if(value.empty()){
							std::cout << "Paramater " << name << " has empty value. Setting default value  " << options[name] << std::endl;					
						}
						else{
							options[name] = value;
						}
					}
					else{
						std::cout << "Option " << name << " is not available. Try following options: " << std::endl;
						for(auto o : options){
							std::cout << "\t" << o.first << std::endl;
						}
						continue;
					}
				}
				else{
					std::cout << "No \"=\" key" << std::endl; 
				}	


			}
	
		}
	line_index++;
	}
	std::map<std::string, std::string>::iterator it;
	if((it = options.find("dimensions")) != options.end()){
	std::cout << "dimensions: " << it->second << std::endl;
	}
}

std::vector<Block> read_file(std::string file_name){
	std::vector<Block> blocks;
	std::string line;
	std::ifstream file(file_name);
	std::string block_name;
	bool in_block = false;	

	if(file.fail()){
		std::cout << "Setup file " << file_name << " does not exist!" << std::endl;  
	}
	
	while(std::getline(file, line)){
		std::string keyword;
		std::string value;
		line = clear_white_spaces(line);

		if(line[0] != '/' && line[1] != '/' && line != ""){

			if(line[line.length()-1] == '{'){
				in_block = true;
				continue;
			}
			if(in_block){
				
			}
		}
	}

}

std::string clear_white_spaces(std::string s){  
	int i = 0, j = 0; 
	while (s[i]) 
	{ 
        	if (s[i] != ' '){
        		s[j++] = s[i]; 
        		i++; 
		}
	} 
	s[j] = '\0'; 
	return s;
}
std::array<std::string,2> split_string(std::string s, char c){
	std::string key, value;
	std::array<std::string,2> res;
	for(int i=0;i<s.length();i++){
		if(s[i] == c){
			key = s.substr(0,i-1);
			value = s.substr(i+1,s.length());
			break;
		}
	}
	res[0] = key;
	res[1] = value;
	return res;
}
Parameter::Parameter(std::string name, std::string value, std::vector<std::string> value_list){
	this->name = name;
	this->value = value;
	this->value_list = value_list;
}
Parameter::~Parameter(){

}

std::string Parameter::get_name(){
	return name;
}

std::vector<std::string> Parameter::get_value_list(){
	return value_list;
}

Block::Block(std::string name, std::vector<Parameter> parameters){
	this->name = name;
	this->parameters = parameters;
}
Block::~Block(){
}

std::string Block::get_name(){
	return name;
}

std::vector<Parameter> Block::get_parameters(){
	return parameters;
}

Input_file::Input_file(std::string name, std::vector<Block> blocks){
	this->name = name;
	this->blocks = blocks;	
}
Input_file::~Input_file(){
}

std::string Input_file::get_name(){
	return name;
}

std::vector<Block> Input_file::get_blocks(){
	return blocks;
}

