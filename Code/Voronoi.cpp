/*
 *  Voronoi.cpp
 *  Roguelike
 *
 *  Created by Daniel on 27/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Voronoi.h"
#include "Types.h"
#include <cmath>

Voronoi::Voronoi(int size, int scale, int n) : Heightmap(size)
{
	min = BIG;
	max = 0;

	for (int p = 0; p < n; p++)
	{
		Point point((float)(rand()%255)/255.0 * size,(float)(rand()%255)/255.0 * size);
		points.push_back(point);
	}

	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			float distance = distanceToNearestPoint(i, j);
			put(i,j,distance);
			if (distance < min)
				min = distance;
			else if (distance > max)
				max = distance;
		}
	}

	
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			put(i,j, scale * (at(i, j) - min) / (max - min));
}

float Voronoi::distanceToNearestPoint(int x, int y)
{
	float mindist = BIG;

	foreach(Points,p,points)
	{
		float dist = sqrtf(powf(((*p).X - x), 2) + powf(((*p).Y - y), 2));
		if (dist < mindist)
			mindist = dist;
	}
	return mindist;
}