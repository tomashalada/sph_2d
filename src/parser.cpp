#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

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

	
	static std::string st = "elements={top-wall,bottom-wall};";
	std::cout << "substr_test:" << st.substr(10,8) << std::endl;
//	std::cout << split_string(st,'.')[0];
//	std::cout << split_string(split_string(st,'.')[1],'{')[0] << std::endl;
	
	load_patches();
	std::cout << std::endl;
	std::array<double,3> test = split_3D_vector("(20,13,0.132)");
	std::cout << test[0] << "," << test[1] << "," << test[2] << std::endl;

}
void load_patches(){

	static std::string file_name = "boundary.sph";
	Input_file inFile;
	std::string line;
	std::ifstream file(file_name);
	bool in_block = false;
	int line_index = 1;
	int k = 0;
	//std::vector<std::string> patch_groups;

	std::vector<Patch_group> patch_groups;


	if(file.fail()){
		std::cout << "Setup file boundary.sph does not exist!" << std::endl;  
	}


	
	//------------------loading patch groups

	std::cout << "@ loading patch groups" << std::endl;
	while(std::getline(file, line)){
		line = clear_whitespaces(line);

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
	std::cout << std::endl;
	
	file.close();
	file.open(file_name);

	std::cout << std::endl;
	//------------------adding elements to patch group
	std::cout << "@ adding patches to patch groups"	<< std::endl;

	for(Patch_group pg : patch_groups){
		std::vector<Patch> patches;
		while(std::getline(file, line)){
			//std::cout << "l. " << line_index << ":";
			line = clear_whitespaces(line);
			if(line[0] != '/' && line[1] != '/' && line != ""){
				if(in_block) std::cout << "in block " << pg.get_name() << std::endl;
				//std::cout << line << std::endl;
				if(in_block && split_string(line,'=')[0] == "elements"){
					//std::cout << "elements line" << std::endl;

					std::vector<std::string> elements = get_patch_group_elements(line);
					for(std::string ps : elements){
						Patch new_patch(ps);
						patches.push_back(new_patch);
						//std::cout << ps << std::endl;
					}
					in_block = false;
					//std::cout << "patches for insert:" << std::endl;
					for(Patch pat : patches){
						std::cout << pat.get_name() << " ";
					}
					std::cout << std::endl;
					patch_groups[k].add_patches(patches);
				}
				
				if(split_string(line,'.')[0] == "patches" && split_string(split_string(line,'.')[1],'{')[0] == pg.get_name() ){

					in_block = true;
				}
			}
		line_index++;
		}
		line_index = 1;	
		file.close();
		file.open(file_name);	
		k++;

	}
	//---------------loading setting of individual patches
	std::cout << std::endl;
	std::cout << "@ reading parameters of each patch" << std::endl;
	in_block = false;
	k=0;
	int c = 0;
	std::string patch_name;
	for(Patch_group pg : patch_groups){
		while(std::getline(file, line)){
			//-------------
			line = clear_whitespaces(line);
			if(line[0] != '/' && line[1] != '/' && line != ""){
				if(in_block && line == "}"){
//					std::cout << "block for patch " << patch_name << " ends" << std::endl;
					in_block = false;
				}
				if(in_block){
//					std::cout << "loading parameter " << split_string(line,'=')[0] << std::endl;
					std::cout << split_string(line,'=')[1] << std::endl;
					patch_groups[k].set_patch_in_group(patch_name,split_string(line,'='));
					c++;
				}

				if(split_string(line,'.')[0] == pg.get_name() && !in_block){
					patch_name = split_string(split_string(line,'.')[1],'{')[0];
//					std::cout << "patch " << patch_name << " in " << pg.get_name() << std::endl;
					in_block = true;
				}
			
			}
	
		}	
		file.close();
		file.open(file_name);
		k++;
	}


	std::cout << "loaded " << c << " parameters" << std::endl;

	for(Patch_group pg : patch_groups){
		pg.print_group();
	}	

	std::cout << std::endl;
	//printing current setting
	k=0;
	for(Patch_group pg : patch_groups){
		patch_groups[k].print_parameters();
		k++;
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
		line = clear_whitespaces(line);

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
		line = clear_whitespaces(line);

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
	int a = 0;
	int b = 0;

	for(int i = 0;i<line.length();i++){	
		if(line[i] == '{') a = i;
		if(line[i] == ',' || line[i] == '}') {
			b = i;	
			res.push_back(line.substr(a+1,b-a-1));
			a = b;
				
		}
		if(line[i] == '}') break;
	}
	return res;
}

std::string clear_whitespaces(std::string s){  
//	s.erase(remove(s.begin(),s.end(),' '),s.end());
	s.erase(remove(s.begin(), s.end(), '\n'), s.end());
	s.erase(remove(s.begin(), s.end(), '\t'), s.end());
	s.erase(remove(s.begin(), s.end(), ' '), s.end());

	return s;
}
std::array<double,2> split_2D_vector(std::string s){
	std::array<double,2> res;
	std::string str_number;	
	int coordinate = 0;
	double number = 0;
	bool read = false;

	for(int i = 0; i < s.length(); i++){

		if(read && s[i] != ','){
			str_number.push_back(s[i]);
		}
		if(s[i] == ',' || s[i] == ')'){
			number = atof(str_number.c_str());
			res[coordinate] = number;
			coordinate++;
			str_number = "";
		}
		if(s[i] == '('){
			read = true;
		}
		if(s[i] == ')') break;
	}
	return res;
}
std::array<double,3> split_3D_vector(std::string s){
	std::array<double,3> res;
	std::string str_number;	
	int coordinate = 0;
	double number = 0;
	bool read = false;

	for(int i = 0; i < s.length(); i++){

		if(read && s[i] != ','){
			str_number.push_back(s[i]);
		}
		if(s[i] == ',' || s[i] == ')'){
			number = atof(str_number.c_str());
			res[coordinate] = number;
			coordinate++;
			str_number = "";
		}
		if(s[i] == '('){
			read = true;
		}
		if(s[i] == ')') break;
	}
	return res;
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
Patch_group::Patch_group(std::string patch_group_name){
	this->patch_group_name = patch_group_name;
}
void Patch_group::add_patch(std::string s){
	patches.push_back(s);
}
void Patch_group::add_patches(std::vector<Patch> new_patches){
	patches = new_patches;
	std::cout << "in function patches: " << std::endl;
	for(Patch p : patches) std::cout << p.get_name() << std::endl;
	std::cout << std::endl;
}
std::string Patch_group::get_name(){
	return patch_group_name;
}
void Patch_group::print_patches(){
//	for(Patch p : patches)
}
void Patch_group::print_group(){
	std::cout << std::endl;
	std::cout << "Patch group name: \"" << patch_group_name << "\", number of patches: " << patches.size() <<  ", patches: " << std::endl;
	for(Patch p : patches){
		std::cout << "	" << p.get_name() << std::endl;
	}
}
void Patch_group::set_patch_in_group(std::string patch_name,std::array<std::string,2> set){
	int k = 0;
	for(Patch p : patches){
		if(p.get_name() == patch_name){
			patches[k].add_patch_parameter(set);
		}
		k++;
	}
} 
void Patch_group::print_parameters(){
	std::cout << "patch group " << patch_group_name << std::endl;
	for(Patch p : patches){
		std::cout << "\t" << "patch " << p.get_name() << ", number of parameters: " << p.get_number_of_parameters() << std::endl;
		std::vector<std::array<std::string,2>> pars = p.get_patch_parameters();
		for(std::array<std::string,2> par : pars){
			std::cout << "\t\t" << par[0] << ", " << par[1] << std::endl;				
		}
	}

}


Patch::Patch(std::string name){
	this->name = name;
}
std::string Patch::get_name(){
	return name;
}
void Patch::add_patch_parameter(std::array<std::string,2> par){
	patch_parameters.push_back(par);
}
std::vector<std::array<std::string,2>> Patch::get_patch_parameters(){
	return patch_parameters;
}
int Patch::get_number_of_parameters(){
	return patch_parameters.size();
}


