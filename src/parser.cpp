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
							for(auto o : options_values){
								if(o.first == name){
										for(std::string s : o.second){
														
									}								
								}
							}
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
