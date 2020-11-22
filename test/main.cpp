#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// sit xD
#define size_x 500 //dx = 1
#define size_y 500 //dy = 1
#define steps 50 //dt = 1

int main(){

float *rho = NULL;
float *u = NULL;
float *f_1 = NULL;
float *f_2 = NULL;
float *f_eq = NULL;
float *f_post = NULL;
float *ct = NULL;

rho = new float[size_x*size_y];
u = new float[size_x*size_y*2];
f_1 = new float[size_x*size_y*9];
f_2 = new float[size_x*size_y*9];
f_eq = new float[size_x*size_y*9];
f_post = new float[size_x*size_y*9];
ct = new float[size_x*size_y];

memset(rho, 1, size_x*size_y);
memset(u, 2, size_x*size_y*2);
memset(f_1, 0, size_x*size_y*9);
memset(f_2, 0, size_x*size_y*9);
memset(f_eq, 0, size_x*size_y*9);
memset(f_post, 0, size_x*size_y*9);
memset(ct, 0, size_x*size_y);

//rho, u do souboru aby to pekne vypadalo v paraview xD

return EXIT_SUCCESS;
}
