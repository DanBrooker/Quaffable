/*
 *  Heightmap.cpp
 *  Roguelike
 *
 *  Created by Daniel on 27/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Heightmap.h"
#include "Types.h"
	
Heightmap::Heightmap(unsigned size)
{
	Size = size;
	heights = (double*)calloc( size * size, sizeof(double) );
}

Heightmap::~Heightmap()
{
	if(heights)
		free(heights);
}

double Heightmap::at(unsigned i,unsigned j)
{
	return heights[ARRAY2D(i,j,Size)];
}

void Heightmap::put(unsigned i,unsigned j,double value)
{
	heights[ARRAY2D(i,j,Size)] = value;
}

Heightmap Heightmap::operator+( Heightmap &other )
{
	Heightmap temp(Size);
	
	for(int j=0;j<Size;j++)
		for(int i=0;i<Size;i++)
			temp.put(i,j,at(i,j)+other.at(i,j));
	return temp;
}

Heightmap Heightmap::operator+=( Heightmap &other )
{
	for(int j=0;j<Size;j++)
		for(int i=0;i<Size;i++)
			put(i,j,at(i,j)+other.at(i,j));
	return *this;
}

Heightmap Heightmap::operator-( Heightmap &other )
{
	Heightmap temp(Size);
	for(int j=0;j<Size;j++)
		for(int i=0;i<Size;i++)
			temp.put(i,j,at(i,j)-other.at(i,j));
	return temp;
}

Heightmap Heightmap::operator-=( Heightmap &other )
{
	for(int j=0;j<Size;j++)
		for(int i=0;i<Size;i++)
			put(i,j,at(i,j)-other.at(i,j));
	return *this;
}

Heightmap Heightmap::operator=( Heightmap &other )
{
	memcpy(heights, other.heights, Size * Size * sizeof(double));
	return *this;
}