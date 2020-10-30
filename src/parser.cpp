#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "parser.h"

void load_parameters(){
	std::vector<std::string> bn = read_block_names("main.sph");
	for(std::string s : bn){
		std::cout << s << std::endl;
	}

	std::map<std::string, std::vector<std::string> > blocks = {
		{"main.sph", {"main","time_control"}},
	};

	std::map<std::string, std::vector<std::string> > main_sph_main_keywords = {
		{"dimensions", {"2","3"}},
		{"write_times", {"true","false"}},
	};
	load_patches();
	static std::string st = "patches.walls{";
//	std::cout << split_string(st,'.')[0];
//	std::cout << split_string(split_string(st,'.')[1],'{')[0] << std::endl;
	
}
void load_patches(){

	static std::string file_name = "boundary.sph";
	Input_file inFile;
	std::string line;
	std::ifstream file(file_name);
	bool in_block = false;
	int line_index = 1;
	//std::vector<std::string> patch_groups;

	std::vector<Patch_group> patch_groups;
	std::vector<Patch> patches;

	if(file.fail()){
		std::cout << "Setup file boundary.sph does not exist!" << std::endl;  
	}


	
	//loading patch groups
	while(std::getline(file, line)){
		line = clear_white_spaces(line);

		if(line[0] != '/' && line[1] != '/' && line != ""){
			//line[line.length()-1] == '{' && 
			if(split_string(line,'.')[0] == "patches"){
				Patch_group pg(split_string(split_string(line,'.')[1],'{')[0]);
				//patch_groups.push_back(split_string(split_string(line,'.')[1],'{')[0]);
				patch_groups.push_back(pg);
			}
		}
	}
	std::cout << "read " << patch_groups.size() << " blocks in boundary.sph:" << std::endl;
	for(Patch_group p : patch_groups){
		std::cout << p.get_name() << std::endl;
	}
	
	file.close();
	file.open(file_name);
	//adding elements to patch group
	for(Patch_group p : patch_groups){

		while(std::getline(file, line)){
			std::cout << "l. " << line_index << ":";
			line = clear_white_spaces(line);
			if(line[0] != '/' && line[1] != '/' && line != ""){
				if(in_block) std::cout << "in block " << p.get_name() << std::endl;
				std::cout << line << std::endl;
				if(in_block && split_string(line,'=')[0] == "elements"){
					std::cout << "elements line" << std::endl;

					//TODO clear_white_space rework, with \t

					std::vector<std::string> elements = get_patch_group_elements(line);
					for(std::string ps : elements){
						Patch new_patch(ps);
						patches.push_back(new_patch);
					}
					in_block = false;
					p.add_patches(patches);
				}
				
				if(split_string(line,'.')[0] == "patches" && split_string(split_string(line,'.')[1],'{')[0] == p.get_name() ){

					in_block = true;
				}
			}
		line_index++;
		}
		line_index = 1;	
		file.close();
		file.open(file_name);
	}

	
	for(Patch_group p : patch_groups){
		p.print_group();
	}	



	file.close();
}

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

std::vector<Input_file> read_file(std::string file_name){
	std::vector<Block> blocks;
	Input_file inFile;
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
				
				Block b(line.substr(0,line.length()-1));
				blocks.push_back(b);
				continue;
			}
			if(line[0] == '}'){
				in_block = false;
				//blocks.push_back(b);
				continue;
			} 
			if(in_block){
				keyword = split_string(line,'=')[0];
				value = split_string(line,'=')[1];
			//	blocks.add_parameter(keyword,value);
				
			}
		}
	}

}

std::vector<std::string> read_block_names(std::string file_name){
	Input_file inFile;
	std::string line;
	std::ifstream file(file_name);
	std::vector<std::string> block_names;


	if(file.fail()){
		std::cout << "Setup file " << file_name << " does not exist!" << std::endl;  
	}

	while(std::getline(file, line)){
		line = clear_white_spaces(line);

		if(line[0] != '/' && line[1] != '/' && line != ""){

			if(line[line.length()-1] == '{'){
				std::string s = line.substr(0,line.length()-1);
				block_names.push_back(s);
			}
		}
	}
	std::cout << "read " << block_names.size() << " blocks in " << file_name << std::endl;
	return block_names;
}
std::vector<std::string> get_patch_group_elements(std::string line){
	std::vector<std::string> res;
	
	return res;
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
			key = s.substr(0,i);
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
Block::Block(std::string name){
	this->name = name;
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

void Block::set_parameters(std::vector<std::string> p){
	this->keywords = p;
}
Input_file::Input_file(){
	this->name = "default_name";
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
Patch_group::Patch_group(std::string name){
	this->name = name;
}
void Patch_group::add_patch(std::string s){
	patches.push_back(s);
}
void Patch_group::add_patches(std::vector<Patch> new_patches){
	patches = new_patches;
}
std::string Patch_group::get_name(){
	return name;
}
void Patch_group::print_patches(){
//	for(Patch p : patches)
}
void Patch_group::print_group(){
	std::cout << std::endl;
	std::cout << "Patch group name: \"" << name << "\", patches: "<< std::endl;
	for(Patch p : patches){
		std::cout << "	" << p.get_name() << std::endl;
	}
}

Patch::Patch(std::string name){
	this->name = name;
}
std::string Patch::get_name(){
	return name;
}



