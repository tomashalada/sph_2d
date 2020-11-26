/* inspired by nvidia dem samples */

#include "particleSystem.h"
#include "particleSystem.cuh"
#include "particles_kernel.cuh"

#include <cuda_runtime.h>

#include <helper_functions.h>
#include <helper_cuda.h>

#include <assert.h>
#include <math.h>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#ifndef CUDART_PI_F
#define CUDART_PI_F 3.141592654f
#endif

ParticleSystem::ParticleSystem(uint numParticles, uint3 gridSize) :
    initialized(false),
    particlesTotal(numParticles),
    h_Position(0),
    h_Velocity(0),
    d_Position(0),
    d_Velocity(0),
    gridSize(gridSize),
    numIterations(1)
{
    numGridCells = gridSize.x*gridSize.y*gridSize.z;
    gridSortBits = 18; // increase this for larger grids

    // set simulation parameters
    params.gridSize = gridSize;
    params.numCells = numGridCells;
    params.numBodies = numParticles;
    params.worldOrigin = make_float3(0.0f, 0.0f, 0.0f);
    params.smoothingLength = 0.02f;
    params.kappa = 1.4f;
    params.mass = 0.04f;
    params.colliderPos = make_float3(-1.2f, -0.8f, 0.8f);
    params.colliderRadius = 0.2f;
    params.gravity = make_float3(0.0f, 0.0f, -9.81f);

    float cellSize = params.particleRadius * params.kappa;
    params.cellSize = make_float3(cellSize, cellSize, cellSize);

    _initialize(particlesTotal);
}

// done destructor
ParticleSystem::~ParticleSystem()
{
    _finalize();
		particlesTotal = 0;
		particlesFluid = 0;
		particlesBoundary = 0;
		particlesVirtual = 0;
}


inline float lerp(float a, float b, float t)
{
    return a + t*(b-a);
}

// done, intialize
void ParticleSystem::_initialize(int numParticles){
    assert(initialized);

    particlesTotal = numParticles;

    // allocate host storage
    h_Position = new double[particlesTotal*4];
    h_Velocity = new double[particlesTotal*4];
    h_Acceleration = new double[particlesTotal*4];
    h_Pressure = new double[particlesTotal*1];
    h_Density = new double[particlesTotal*1];
    memset(h_Position, 0, particlesTotal*4*sizeof(double));
    memset(h_Velocity, 0, particlesTotal*4*sizeof(double));
    memset(h_Acceleration, 0, particlesTotal*4*sizeof(double));
    memset(h_Pressure, 0, particlesTotal*1*sizeof(double));
    memset(h_Density, 0, particlesTotal*1*sizeof(double));

    h_CellStart = new uint[numGridCells];
    memset(h_CellStart, 0, numGridCells*sizeof(uint));
    h_CellEnd = new uint[numGridCells];
    memset(h_CellEnd, 0, numGridCells*sizeof(uint));

    // allocate GPU data
    unsigned int memSize = sizeof(double) * 4 * particlesTotal;

    allocateArray((void **)&d_Velocity, memSize);

    allocateArray((void **)&d_SortedPosition, memSize);
    allocateArray((void **)&d_SortedVelocity, memSize);

    allocateArray((void **)&d_GridParticleHash, numParticlesTotal*sizeof(uint));
    allocateArray((void **)&d_SortedVelocity, numParticlesTotal*sizeof(uint));

    allocateArray((void **)&d_CellStart, numGridCells*sizeof(uint));
    allocateArray((void **)&d_CellEnd, numGridCells*sizeof(uint));

    sdkCreateTimer(&timer);
    setParameters(&params);
    initialized = true;
}

// done, finalize
void ParticleSystem::_finalize()
{
    assert(initialized);

    delete [] h_Position;
    delete [] h_Velocity;
    delete [] h_Acceleration;
    delete [] h_Pressure;
    delete [] h_Density;

    freeArray(d_Position);
    freeArray(d_Velocity);
    freeArray(d_Acceleration);
    freeArray(d_Pressure);
    freeArray(d_Density);

    freeArray(d_GridParticleHash);
    freeArray(d_GridParticleIndex);
    freeArray(d_CellStart);
    freeArray(d_CellEnd);
}

// done step the simulation
void ParticleSystem::update(float deltaTime){
    assert(initialized);

    float *d_Pos;
    d_Pos = (float *) d_Position;

    // update constants
    setParameters(&params);

    // integrate
    integrateSystem(
        d_Pos,
        d_Velocity,
        deltaTime,
        particlesTotal);

    // calculate grid hash
    calcHash(
        d_GridParticleHash,
        d_GridParticleIndex,
        d_Pos,
        particlesTotal);

    // sort particles based on hash
    sortParticles(d_GridParticleHash, d_GridParticleIndex, particlesTotal);

    // reorder particle arrays into sorted order and
    // find start and end of each cell
    reorderDataAndFindCellStart(
        d_CellStart,
        d_CellEnd,
        d_SortedPos,
        d_SortedVel,
        d_GridParticleHash,
        d_GridParticleIndex,
        dPos,
        d_Vel,
        particlesTotal,
        numGridCells);

    // process collisions
    collide(
        d_Vel,
        d_SortedPos,
        d_SortedVel,
        d_GridParticleIndex,
        d_CellStart,
        d_CellEnd,
        particlesTotal,
        numGridCells);

}

void
ParticleSystem::dumpGrid()
{
    // dump grid information
    copyArrayFromDevice(m_hCellStart, m_dCellStart, 0, sizeof(uint)*m_numGridCells);
    copyArrayFromDevice(m_hCellEnd, m_dCellEnd, 0, sizeof(uint)*m_numGridCells);
    uint maxCellSize = 0;

    for (uint i=0; i<m_numGridCells; i++)
    {
        if (m_hCellStart[i] != 0xffffffff)
        {
            uint cellSize = m_hCellEnd[i] - m_hCellStart[i];

            //            printf("cell: %d, %d particles\n", i, cellSize);
            if (cellSize > maxCellSize)
            {
                maxCellSize = cellSize;
            }
        }
    }

    printf("maximum particles per cell = %d\n", maxCellSize);
}

void
ParticleSystem::dumpParticles(uint start, uint count)
{
    // debug
    copyArrayFromDevice(m_hPos, 0, &m_cuda_posvbo_resource, sizeof(float)*4*count);
    copyArrayFromDevice(m_hVel, m_dVel, 0, sizeof(float)*4*count);

    for (uint i=start; i<start+count; i++)
    {
        //        printf("%d: ", i);
        printf("pos: (%.4f, %.4f, %.4f, %.4f)\n", m_hPos[i*4+0], m_hPos[i*4+1], m_hPos[i*4+2], m_hPos[i*4+3]);
        printf("vel: (%.4f, %.4f, %.4f, %.4f)\n", m_hVel[i*4+0], m_hVel[i*4+1], m_hVel[i*4+2], m_hVel[i*4+3]);
    }
}

// done
float *ParticleSystem::getArray(ParticleArray array){
    assert(initialized);

    float *h_data = 0;
    float *d_data = 0;
		uint dim = 0;

    switch (array)
    {
        default:
        case POSITION:
            h_data = h_Position;
            d_data = d_Position;
						dim = 4;
            break;

        case VELOCITY:
            h_data = h_Velocity;
            d_data = d_Velocity;
						dim = 4;
            break;

        case ACCELERATION:
            h_data = h_Acceleration;
            d_data = d_Acceleration;
						dim = 4;
            break;

        case PRESSURE:
            h_data = h_Pressure;
            d_data = d_Pressure;
						dim = 1;
            break;

        case DENSITY:
            h_data = h_Density;
            d_data = d_Density;
						dim = 1;
            break;
    }

    copyArrayFromDevice(h_data, d_data, &cuda_vbo_resource, numParticlesTotal*dim*sizeof(double));
    return h_data;
}

// done
void ParticleSystem::setArray(ParticleArray array, const float *data, int start, int count){
    assert(initialized);

    switch (array)
    {
        default:
        case POSITION:
            copyArrayToDevice(d_Position, data, start*4*sizeof(float), count*4*sizeof(float));
            break;

        case VELOCITY:
            copyArrayToDevice(d_Velocity, data, start*4*sizeof(float), count*4*sizeof(float));
            break;

        case ACCELERATION:
            copyArrayToDevice(d_Acceleration, data, start*4*sizeof(float), count*4*sizeof(float));
            break;

        case PRESSURE:
            copyArrayToDevice(d_Pressure, data, start*4*sizeof(float), count*4*sizeof(float));
            break;

        case DENSITY:
            copyArrayToDevice(d_Density, data, start*4*sizeof(float), count*4*sizeof(float));
            break;
    }
}

inline float frand()
{
    return rand() / (float) RAND_MAX;
}


// Jakoze inicializace castic pro DEM
void ParticleSystem::initGrid(uint *size, float spacing, float jitter, uint numParticles){
    srand(1973);

    for (uint z=0; z<size[2]; z++)
    {
        for (uint y=0; y<size[1]; y++)
        {
            for (uint x=0; x<size[0]; x++)
            {
                uint i = (z*size[1]*size[0]) + (y*size[0]) + x;

                if (i < numParticles)
                {
                    m_hPos[i*4] = (spacing * x) + m_params.particleRadius - 1.0f + (frand()*2.0f-1.0f)*jitter;
                    m_hPos[i*4+1] = (spacing * y) + m_params.particleRadius - 1.0f + (frand()*2.0f-1.0f)*jitter;
                    m_hPos[i*4+2] = (spacing * z) + m_params.particleRadius - 1.0f + (frand()*2.0f-1.0f)*jitter;
                    m_hPos[i*4+3] = 1.0f;

                    m_hVel[i*4] = 0.0f;
                    m_hVel[i*4+1] = 0.0f;
                    m_hVel[i*4+2] = 0.0f;
                    m_hVel[i*4+3] = 0.0f;
                }
            }
        }
    }
}

// eh?
void ParticleSystem::reset(ParticleConfig config){
    switch (config)
    {
        default:
        case CONFIG_RANDOM:
            {
                int p = 0, v = 0;

                for (uint i=0; i < m_numParticles; i++)
                {
                    float point[3];
                    point[0] = frand();
                    point[1] = frand();
                    point[2] = frand();
                    m_hPos[p++] = 2 * (point[0] - 0.5f);
                    m_hPos[p++] = 2 * (point[1] - 0.5f);
                    m_hPos[p++] = 2 * (point[2] - 0.5f);
                    m_hPos[p++] = 1.0f; // radius
                    m_hVel[v++] = 0.0f;
                    m_hVel[v++] = 0.0f;
                    m_hVel[v++] = 0.0f;
                    m_hVel[v++] = 0.0f;
                }
            }
            break;

        case CONFIG_GRID:
            {
                float jitter = m_params.particleRadius*0.01f;
                uint s = (int) ceilf(powf((float) m_numParticles, 1.0f / 3.0f));
                uint gridSize[3];
                gridSize[0] = gridSize[1] = gridSize[2] = s;
                initGrid(gridSize, m_params.particleRadius*2.0f, jitter, m_numParticles);
            }
            break;
    }

    setArray(POSITION, m_hPos, 0, m_numParticles);
    setArray(VELOCITY, m_hVel, 0, m_numParticles);
}

