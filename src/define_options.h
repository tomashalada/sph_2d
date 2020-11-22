/* Parameters */



#include <array>
#include <string>
#include <cmath>

#include "config.h"

/*
#if SPH2D
const int dimension = 2;
typedef std::array<double,2> sph_vect;
#else
const int dimension = 3;
typedef std::array<double,3> sph_vect;
#endif

#if SPH2D
sph_vect gravity = {0., -9.81};
#else
sph_vect gravity = {0., 0., -9.81};
#endif

*/
// -----------------------------------------------------------------------------------
// Vstupni parametry
//pozn. s kernel_fix funkci, h = 0.03 a m 400 to snad i neco dela...

const static std::array<double, 2> gravity = {0, -9.81};
const static double h = 0.02; // kernel constant
const static double mass = 400; // mass
const static double visco = 1; //visco
const static double dt = 0.0001; // time-step
const static double t_max = 1.0; // koncovy cas
const static double init_dist = 0.02; //referencni pocet castic pro inicializaci
const static double kappa = 1.5;
const static double eps = h;
const static double damp = -0.8;

//Oblast - tohle aktualne nefunguje
const static int height_domain = 2; //rozmery pripustneho oboru
const static int width_domain = 2;
const static int height_box = 1; //rozmer hranic
const static int width_box = 1;
const static double height_fluid = 0.6; //rozmer uvodniho boxiku tekutiny
const static double width_fluid = 0.6;
const static std::string dir_name = "vystup_testovaci_5";


const double x_min = -1.5;
const double x_max = 1.8;
const double y_min = -1;
const double y_max = 1.5;

