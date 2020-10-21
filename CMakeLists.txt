# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# project name
project(sph_solver)

# creates the variable EXEC and sts it to sph
set(EXEC sph)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# ../includes
include_directories(src)

# puts all .cpp file inside src to the SOURCE variable
file(GLOB SOURCES src/*.cpp)

# compiles te files defined by SOURCES to generate the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})
