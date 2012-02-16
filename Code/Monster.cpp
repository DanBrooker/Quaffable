/*
 *  Monster.cpp
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Monster.h"
#include "Types.h"
#include "Tile.h"
#include "Map.h"
#include "Player.h"
#include "Ascii.h"
#include "Roguelike.h"
#include "Weapon.h"

#include "Stringer.h"

Monster::Monster() : Object()
{
	hp = maxhp = 1;
	mp = maxmp = 0;
	sight = 10;
	speed = SpeedNormal; 
    name = "Monster";
    
    setTransparent(false);
	setPassable(false);
}

Monster::Monster(Ascii *ascii) : Object(ascii)
{
	hp = maxhp = 1;
	mp = maxmp = 0;
	sight = 10;
	speed = SpeedNormal;
    name = "Monster";
    
    setTransparent(false);
	setPassable(false);
}

int Monster::getHP()
{
    return hp;
}

int Monster::adjustHP(int delta)
{
    setHP(hp + delta);
    return hp;
}

void Monster::setHP(int hitpoints)
{
    if(hitpoints > maxhp)
        hp = maxhp;
    else if(hitpoints <= 0)
    {
        hp = 0;
        onDeath();
    }
    else
    {
        hp = hitpoints;
    }
}

std::string Monster::hpDescription()
{
    std::string description;
    if(hp <= 0)
        description = "#f00Dead";
    else if(hp <= maxhp/2)
        description = "#f82Wounded";
    else if(hp <= 3*maxhp/4)
        description = "#ff0Injured";
    else
        description = "#0f0Uninjured";
    
    return description + stringFormat("< %d/%d>",hp,maxhp);
}

int Monster::getMaxHP()
{
    return maxhp;
}

void Monster::setMaxHP(int maxHitPoints)
{
    maxhp = maxHitPoints;
    hp = maxhp;
}

void Monster::updateAscii()
{
	Object::updateAscii();
}

void randomMovement(int count,Monster *monster, Map *map)
{
    if(count > 5)
        return;
    
    int x=0,y=0;
    switch(rand()%4)
    {
        case 0: //left
            x=-1;
            break;
        case 1: //right
            x=1;
            break;
        case 2: //up
            y=-1;
            break;
        case 3: //down
            y=1;
            break;
            
    }
    
    WorldCoord current = monster->getPosition();
    WorldCoord random(current.X+x,current.Y+y);
    if(map->checkMove(monster,random.X,random.Y))
        map->moveObject(monster,random.X,random.Y);
    else
        randomMovement(count++,monster,map);
}

void Monster::performTurn()
{
    if(hp <= 0)
        return;
	if(dynamic_cast<Player *>(this)== NULL) // Not the player, temp ai for monsters
	{
		randomMovement(0,this,getMap());
	}
}

bool Monster::canSee(int x, int y)
{		
	if(sightMap==NULL)
		calculateSight();
	WorldCoord world(x,y);
	bool visible = sightMap->isLit(world);
	return visible;
}

void Monster::calculateSight()
{
	sightMap = new Lightmap(getPosition(),sight,getMap());
}

Object *Monster::getWeaponForMelee()
{    
    return NULL;
}

void Monster::onDeath()
{
    LOG("#AA0%s died.",this->name.c_str());
    // make corpse
    Object *corpse = new Object(new Ascii(PERCENT,1,1,1));
    parent->addObject(corpse);
    
    // make gore
    // blood
    // body parts
    
    dumpInventory();
    // remove self
    parent->removeObject(this);
}

Damage Monster::getMeleeDamage()
{
    return Damage(1,DamageBlunt);
}

void Monster::onDamagedBy(Object *attacker,Damage damage)
{
    // attack the attacker because if monster
}
