/* Parameters */

#include <array>
#include "config.h"

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
