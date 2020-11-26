#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#define DEBUG_GRID 0
#define DO_TIMING 0

#include <helper_functions.h>
#include "particleKernel.cuh"
#include "vector_functions.h"

class ParticleSystem
{
		public:
		ParticleSystem(uint numParticles, unit3 gridSize);
		~ParticleSystem();

		// data
		enum ParticleArray{
				POSITION,
				VELOCITY,
				ACCELERATION,
				DENSITY,
				PRESSURE,
		};

		void update(float deltaTime);

		float *getArray(ParticleArray array);
		void   setArray(ParticleArray array, const float *data, int start, int count);

		int    getNumParticlesTotal() const{
       return particlesTotal;
		}
		int    getNumParticlesFluid() const{
       return particlesFluid;
		}
		int    getNumParticlesBoundary() const{
       return particlesBoundary;
		}
		int    getNumParticlesVirtual() const{
       return particlesVirtual;
		}
		void setIterations(int i){
				numIterations = i;
		}
		void setSmoothingLength(float x){
				params.smoothingLength = x;
		}
		void setKappa(float x){
				params.Kappa = x;
		}
		float3 getGridSize(){
				return params.girdSize;
		}
		float3 getCellSize(){
				return params.cellSize;
		}

	protected:

		ParticleSystem(){}

		// methods
		void _initialize(int numParticles);
		void _finalize();

    void initGrid(uint *size, float spacing, float jitter, uint numParticles);

		//data
		bool initialized;

		uint particlesTotal;
		uint particlesFluid;
		uint particlesBoundary;
		uint particlesVirtual;

		// CPU data
		float *h_Position;
		float *h_Velocity;
		float *h_Acceleration;
		float *h_Pressure;
		float *h_Density;

		uint *h_ParticleHash;
		uint *h_CellStart;
		uint *h_CellEnd;

		// GPU data
		float *d_Position;
		float *d_Velocity;
		float *d_Acceleration;
		float *d_Pressure;
		float *d_Density;

		float *d_SortedPosition;
		float *d_SortedVelocity;

    // grid data - sorting
		uint *d_GridParticleHash; // grid hash value for each particle
    uint *d_GridParticleIndex;// particle index for each particle
    uint *d_CellStart;        // index of start of each cell in sorted list
    uint *d_CellEnd;          // index of end of cell

    uint gridSortBits;

		Simulation_parameters params;
		uint3 gridSize;
		uint numGridCells;

		uint numIterations;

};

#endif
