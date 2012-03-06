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
    
    behaviour = BehaviourDefensive;
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
    
    behaviour = BehaviourDefensive;
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

WorldCoord Monster::randomMove()
{
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
    
    WorldCoord current = this->getPosition();
    WorldCoord random(current.X+x,current.Y+y);
    
    return random;
}

WorldCoord Monster::towardTargets(Objects *targets)
{
    return randomMove();
}

WorldCoord Monster::awayFromTargets(Objects *targets)
{
    return randomMove();
}

void Monster::performTurn()
{
    if(hp <= 0)
        return;
     
    WorldCoord move;
    Map *map = getMap();
    
    Objects *aggressors = map->getAggressors(this);
    Objects *targets = map->getTargets(this);
    
    LOG("<[%s] %d targets>",this->name.c_str(),targets->size());
    LOG("<[%s] %d aggressors>",this->name.c_str(),aggressors->size());

    /// check flee
    if(HAS_MASK(behaviour,BehaviourFlees))
    {
        if(HAS_MASK(behaviour,BehaviourAggressive) && hp > (maxhp*0.2))
        {
            LOG("<[%s] too aggressive to flee>",this->name.c_str());
//            if(targets && !targets->empty())
//            {
//                move = towardTargets(targets);
//                LOG("<[%s] move toward target>",this->name.c_str());
//            }
//            else
//            {
//                move = randomMove();
//                LOG("<[%s] moved randomly>",this->name.c_str());
//            }
        }
        else
        {
            if(targets && !targets->empty())
            {
                move = awayFromTargets(targets);
                LOG("<[%s] fled>",this->name.c_str());
            }
//            else
//            {
//                move = randomMove();
//                DLOG("[%s] moved randomly>",this->name.c_str());
//            }
        }
    }
    
    if(move.zero() && map->checkMove(this, move.X, move.Y))
    {
        map->moveObject(this,move.X,move.Y);
        return;
    }
    
    
    /// check can attack
    if(attacking || HAS_MASK(behaviour,BehaviourAggressive))
    {
        if(!targets->empty())
        {
            LOG("<[%s] would attack target>",this->name.c_str());
        }
    }
    
    /// check movement
    
    /// random movement
    
    
    
//        if(HAS_MASK(behaviour,BehaviourPassive)/*behaviour == (behaviour & BehaviourPassive)*/ )
//        {
//            move = randomMove();
//            
//            if(map->checkMove(this, move.X, move.Y))
//            {
//                map->moveObject(this,move.X,move.Y);
//                //break;
//            }
//        }
//        else if(HAS_MASK(behaviour,BehaviourDefensive) && !attacking)
//        {
//            move = randomMove();
//            
//            
//        }
//        else if(HAS_MASK(behaviour,BehaviourDefensive) && attacking)
//        {
//            //break;
//        }

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

Objects Monster::getWeaponsForMelee()
{    
    Objects weapons;
    foreachp(ObjectMap, obj, equipment)
    {
        Object *weapon = obj->second;
        if(weapon->_flags.wieldable)
        {
            weapons.push_back(weapon);
        }
    }
    
    return weapons;
}

void Monster::onDeath()
{
    LOG("#AA0%s died.",this->name.c_str());
    // make corpse
    Object *corpse = new Object(new Ascii(PERCENT,Colour::white()));
    parent->addObject(corpse);
    
    // make gore
    // blood
    // body parts
    
    dumpInventory();
    // remove self
    parent->removeObject(this);
}

Damages Monster::getMeleeDamages()
{
    Damages dmgs;
    Objects weapons = getWeaponsForMelee();
    foreach(Objects,w,weapons)
    {
        dmgs.push_back((*w)->getMeleeDamage());
    }
    return dmgs;
}

void Monster::onDamagedBy(Object *attacker,Damage damage)
{
    // attack the attacker if monster
    attacking = true;
}

void Monster::dumpInventory()
{
    Object::dumpInventory();
    if(equipment == NULL)
        return;
    
    foreachp(ObjectMap, object, equipment)
    {
        dropInventoryObject((object->second));
    }
}
