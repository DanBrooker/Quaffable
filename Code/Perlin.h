/*
 *  Perlin.h
 *
 */

#include "Heightmap.h"

#ifndef PERLIN_H_INC
#define PERLIN_H_INC 

class Perlin : public Heightmap
{
	public:
		Perlin(int size, int octaves, double persistance);
};

#endif /* PERLIN_H_INC */