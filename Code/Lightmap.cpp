/*
 *  Lightmap.cpp
 *  Roguelike
 *
 *  Created by Daniel on 23/05/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Lightmap.h"
#include "Map.h"
#include <math.h>

Lightmap::Lightmap()
{
	Lightmap(Point(0,0),1,NULL);
}

Lightmap::Lightmap(Point p,int r,Map *map)
{
    this->map = map;
	boolMap = NULL;
	position = p;
	radius = r;
	calculate();
}

bool Lightmap::isLit(WorldCoord world)
{
	LocalCoord local = world2local(world);
	if(local.X < 0 || local.Y < 0)
		return false;
	else if(local.X >= (radius*2+1) || local.Y >= (radius*2+1))
		return false;
	return isVisible(local);
}

Ascii *Lightmap::filter(WorldCoord world,Ascii *ascii)
{
    // filter the ascii 
    return ascii;
}

LocalCoord Lightmap::world2local(WorldCoord w)
{
	WorldCoord me = position;
	LocalCoord local(w.X-me.X+radius,w.Y-me.Y+radius);
	return local;
}

WorldCoord Lightmap::local2world(LocalCoord l)
{
	WorldCoord me = position;
	WorldCoord world(me.X+l.X-radius,me.Y+l.Y-radius);
	return world;
}

bool Lightmap::isBlocked(WorldCoord co)
{
	return ! map->getTransparent(co.X,co.Y);
}

bool Lightmap::isVisible(LocalCoord co)
{
	int w = radius*2+1;
	return boolMap[ARRAY2D(co.X,co.Y,w)];
}

void Lightmap::setVisible(LocalCoord co)
{
	int w = radius*2+1;
	boolMap[ARRAY2D(co.X,co.Y,w)] = YES;
}
					
bool Lightmap::pointInRange(Point a, Point b, int range)
{
	if(a.X==b.X)
		return abs(a.Y-b.Y) <= range;
	else if(a.Y==b.Y)
		return abs(a.X-b.X) <= range;
	else
		return pow(a.X-b.X,2) + pow(a.Y-b.Y,2) <= range*range;
}

void Lightmap::calculate()
{
	//printf("Calculating boolMap\n\n");
	if(boolMap!=NULL)
		free(boolMap);
	boolMap = (bool*)calloc( (radius*2+1) * (radius*2+1), sizeof(bool) );
	
	static int mult[4][8] = {
		{1,  0,  0, -1, -1,  0,  0,  1},
		{0,  1, -1,  0,  0, -1,  1,  0},
		{0,  1,  1,  0,  0, -1, -1,  0},
		{1,  0,  0,  1, -1,  0,  0, -1}};
	
	for(int oct = 0; oct < 8; oct++)
		cast_light(1, 1.0, 0.0, mult[0][oct], mult[1][oct], mult[2][oct], mult[3][oct], 0);
	
	WorldCoord pos = position;
	setVisible(world2local(pos));
	
//	for(int i = 0;i < (radius*2+1) * (radius*2+1); i++)
//	{
//		printf("%d",boolMap[i]);
//		if(i%(radius*2+1)==(radius*2))
//			printf("\n");
//	}
}

void Lightmap::cast_light(int row, float start,float end,int xx,int xy,int yx,int yy,int id)
{

	WorldCoord pos = position;
	int cx =pos.X, cy= pos.Y;

	if(start < end)
		return;
	int radius_squared = radius*radius;
	int new_start=0;
	for(int j=row; j < radius; j++)
	{
		int dx = -j-1, dy = -j;
		bool blocked = false;
        while(dx <= 0)
		{
			dx++;
			int X = cx + dx * xx + dy * xy;
			int Y = cy + dx * yx + dy * yy;
			
			WorldCoord world = WorldCoord(X, Y);
			LocalCoord local = world2local(world);
			
			float l_slope = (dx-0.5)/(dy+0.5), r_slope= (dx+0.5)/(dy-0.5);
			if(start < r_slope)
				continue;
			else if(end > l_slope)
				break;
			else
				if( (dx*dx + dy*dy) < radius_squared)
					setVisible(local);
			
			if (blocked)
			{
				if(isBlocked(world))
				{
					new_start = r_slope;
					continue;
				}
				else
				{
					blocked = false;
				}
				start = new_start;
			}
			else
			{
				if (isBlocked(world) && j <= radius)
				{
					blocked = true;
					cast_light(j+1, start, l_slope, xx, xy, yx, yy, id+1);
					new_start = r_slope;
				}
			}
		}
		if(blocked)
			break;
	}
}
