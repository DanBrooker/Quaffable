/*
 *  Tile.cpp
 *  Roguelike
 *
 *  Created by Daniel on 6/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Map.h"
#include "Tile.h"
#include "Point.h"

Tile::Tile()
{
	Tile(-1,-1);
}

Tile::Tile(int i, int j)
{
	lastAscii = NULL;
	objects = new Objects();
	_flags.visited = NO;
	_flags.passable  = YES;
	_flags.transparent = YES;
	Position = Point(i,j);
}

Tile::~Tile()
{
    delete objects;
    lastAscii = NULL;
    parent = NULL;
}

void Tile::addObject(Object *object)
{
	object->setParent(this);
	objects->push_back(object);
	
	if(object->_flags.passable==NO)
		_flags.passable = NO;
		
	if(object->_flags.transparent==NO)
		_flags.transparent = NO;
}

void Tile::removeObject(Object *object)
{
	object->setParent(NULL);
	objects->remove(object);
	
	bool passable = true,transparent = true;
	foreachp(Objects,o,objects)
	{
		if((*o)->_flags.passable==NO)
			passable = false;
		
		if((*o)->_flags.transparent==NO)
			transparent = false;
	}
	_flags.passable = passable ? YES : NO ;
	_flags.transparent = transparent ? YES : NO ;
}

Ascii *Tile::getTopAscii(bool visible)
{
	Ascii *ascii = NULL;
	if(visible)
	{
		if(objects->size() > 0)
        {   
            Object *object = objects->back();
			ascii = object->getAscii();
        }
		_flags.visited = YES;
		lastAscii = ascii;
	}
	else if(_flags.visited)
	{
		ascii = lastAscii;
	}
	
	return ascii;
}

Object *Tile::getTopObject()
{
    if(objects->size() > 0)
        return objects->back();
    else
        return NULL;
}
