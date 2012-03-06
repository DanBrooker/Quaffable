/*
 *  Object.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#include "Object.h"
#include "Map.h"
#include "Tile.h"
#include "Ascii.h"

Object::Object()
{
	parent = NULL;
	asciis = new AsciiGroup(new Ascii());
	_flags.passable = NO;
	_flags.transparent = NO;
    weight = 0.1;
}

Object::Object(Ascii *asc) 
{
	parent = NULL;
	asciis = new AsciiGroup(asc);
	_flags.passable = YES;
	_flags.transparent = YES;
    weight = 0.1;
}

Object::Object(AsciiGroup *asc)
{
	parent = NULL;
	asciis = asc;
	_flags.passable = YES;
	_flags.transparent = YES;
    weight = 0.1;
}

void Object::removeFromTile()
{
    if(parent)
        parent->removeObject(this);
}

void Object::setParent(Tile *tile)
{
	parent = tile;
}

Tile* Object::getParent()
{
	return parent;
}

Point Object::getPosition()
{
    if(parent == NULL)
        return Point();
	return parent->Position;
}

Map *Object::getMap()
{
    return parent->parent;
}

void Object::setPassable(bool passable)
{
	if(passable)
		_flags.passable = YES;
	else
		_flags.passable = NO;
}

bool Object::passable()
{
	return _flags.passable==YES;
}

void Object::setTransparent(bool transparent)
{
	if(transparent)
		_flags.transparent = YES;
	else
		_flags.transparent = NO;
}

bool Object::transparent()
{
	return _flags.transparent==YES;
}

Ascii* Object::getAscii()
{
    if(asciis == NULL)
        return new Ascii();
	return asciis->currentAscii();
}

void Object::updateAscii()
{
	asciis->update();
}

void Object::addObjectToInventory(Object *object)
{
    if(inventory == NULL)
        inventory = new std::list<Object *>();
    inventory->push_back(object);
}

void Object::removeObjectFromInventory(Object *object)
{
    if(inventory == NULL)
        return;
    inventory->remove(object);
}

Objects *Object::getInventory()
{
    return inventory;
}

void Object::dumpInventory()
{
    if(inventory == NULL)
        return;
    foreachp(std::list<Object *>, object, inventory)
    {
        dropInventoryObject((*object));
    }
}

void Object::dropInventoryObject(Object *object)
{
    
}

Damage Object::getMeleeDamage()
{
    return Damage(weight*20,DamageBlunt);
}

Damage Object::calculateMeleeDamageFrom(Object *object)
{
    Damage raw = object->getMeleeDamage();
    // reduce damage from armour, resistances, 
    
    return raw;
}

Damage Object::getThrowDamage()
{
    return Damage(weight*10,DamageBlunt);
}

void Object::onDeath()
{
    
}

void Object::onDamagedBy(Object *attacker,Damage damage)
{
    
}

void Object::onHealedBy(Object *attacker,Damage damage)
{
    
}

void Object::onDamagedObject(Object *target,Damage damage)
{
    
}
