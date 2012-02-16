/*
 *  World.cpp
 *  
 *
 *  Created by Daniel Brooker on 29/03/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "World.h"
#include "SDL/SDL.h"
#include "Map.h"

World::World()
{
	map = NULL;
	
	turn.count = -1;
    turn.playerCount = 0;
	turn.orderCount = 6;
	turn.order = (Speed *)calloc(turn.orderCount,sizeof(Speed));
	turn.order[0] = SpeedFast;
	turn.order[1] = SpeedNormal;
	turn.order[2] = SpeedFast;
	turn.order[3] = SpeedNormal;
	turn.order[4] = SpeedFast;
	turn.order[5] = SpeedSlow;
}

void World::setMap(Map *newMap)
{
    if(map)
        delete map;
    this->map = newMap;
	map->world = this;
}

Map *World::getMap()
{
    return map;
}

void World::display(float *texPointer, float *colPointer, float *bgColPointer)
{
	map->setTexturePointer(texPointer);
	map->setColourPointer(colPointer);
	map->setBackgroundColourPointer(bgColPointer);
	map->display();
}

void World::updateWorld()
{
	turn.count++;
	
	int turnCurrent = turn.count % turn.orderCount;
	
	Speed turnSpeed = turn.order[turnCurrent];
//	printf("Turn %d speed=%s\n",turnCurrent,stringForSpeed(turnSpeed).c_str());
	
    map->update(turnSpeed);
	
	if(map->getPlayer()->speed == turnSpeed)
	{
		map->getPlayer()->calculateSight();
		return;
	}
	
	updateWorld();
}

Rect World::getFrame()
{
	return Rect();
}

Display* World::getParent()
{
	return parent;
}

int World::getTurn()
{
    return turn.playerCount;
}

bool World::handleEvents(SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_KEYDOWN:
//			keyDown[event->key.keysym.sym]();
//			break;
			switch( event->key.keysym.sym )
			{
				case SDLK_w:
					map->adjustPlayer(0,-1);
					//	map->visibleRect.Y -= 1;
					break;
				case SDLK_a:
					map->adjustPlayer(-1,0);
					//	map->visibleRect.X -= 1;
					break;
				case SDLK_s:
					map->adjustPlayer(0,1);
					//	map->visibleRect.Y += 1;
					break;
				case SDLK_d:
					map->adjustPlayer(1,0);
					//	map->visibleRect.X += 1;
					break;
                case SDLK_f:
                    // add range overlay, which takes key presses
                    return false;
                    break;
                case SDLK_PERIOD:
                    break;
				default:
					return false;
			}
			break;
		default:
			return false;
	}
	
    turn.playerCount++;
	updateWorld();	
	
	return true;
}