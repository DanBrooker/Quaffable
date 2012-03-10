/*
 *  Voronoi.h
 *  Roguelike
 *
 *  Created by Daniel on 27/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef VORONOI_H
#define VORONOI_H

#include "Heightmap.h"
#include "Point.h"

#define BIG 99999.0

class Voronoi : public Heightmap
{
	Points points;
	float min,max;
		
	public:
		Voronoi(int size, int scale, int n);
	private:
		float distanceToNearestPoint(int x, int y);
};

#endif /* VORONOI_H */