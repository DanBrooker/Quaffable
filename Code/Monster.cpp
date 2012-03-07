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
    
    setTransparent(true);
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
    
    setTransparent(true);
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

WorldCoord Monster::towardAttacker(Object *target)
{
    // two main movements are possible in four connected, effectively one square in the x or y toward the target, eg left or up, up or right, down or left, down or right
    WorldCoord move;
    WorldCoord p = getPosition();
    WorldCoord t = getPosition();
    
    int xdir = p.X > t.X ? -1 : 1;
    int ydir = p.Y > t.Y ? -1 : 1;
    
    // check move in X dir
    move = WorldCoord(p.X+xdir,p.Y);
    if(getMap()->checkMove(this, move.X, move.Y))
    {
        return move;
    }
    
    // check move in Y dir
    move = WorldCoord(p.X,p.Y+ydir);
    if(getMap()->checkMove(this, move.X, move.Y))
    {
        return move;
    }
       
    return  WorldCoord(0,0);
}

WorldCoord Monster::awayFromAttacker(Object *target)
{
    /// same as above just opposite direction
    
    WorldCoord move;
    WorldCoord p = getPosition();
    WorldCoord t = getPosition();
    
    int xdir = p.X > t.X ? 1 : -1;
    int ydir = p.Y > t.Y ? 1 : -1;
    
    // check move in X dir
    move = WorldCoord(p.X+xdir,p.Y);
    if(getMap()->checkMove(this, move.X, move.Y))
    {
        return move;
    }
    
    // check move in Y dir
    move = WorldCoord(p.X,p.Y+ydir);
    if(getMap()->checkMove(this, move.X, move.Y))
    {
        return move;
    }
    
    return  WorldCoord(0,0);
}

void Monster::attack(Object *t, Object *weapon)
{
    Monster *target = dynamic_cast<Monster *>(t);
    if(target != NULL)
    {
        Damage damage = target->calculateMeleeDamageFrom(this);
        LOG("Hit %s.< #AA0%d dmg>",target->name.c_str(),damage.damage);
        target->adjustHP(-damage.damage);
        LOG("<%s.>",target->hpDescription().c_str());
        
        if(target->getHP() > 0 )
            target->onDamagedBy(this, damage);
        this->onDamagedObject(target,damage);
    }
}

void Monster::performTurn()
{
    if(hp <= 0)
        return;
     
    WorldCoord move;
    Map *map = getMap();
    
    if(HAS_MASK(behaviour,BehaviourAggressive)||HAS_MASK(behaviour,BehaviourTimid))
    {
        // check for people to attack
        attackers = map->getVisibleMonsters(this,sight);
    }
    
    Object *nearest = NULL;
    float mindist = sight+1;
    foreach(Objects, o, attackers)
    {
        float dist = (*o)->distanceTo(this);
        if(dist < mindist)
        {
            nearest = (*o);
            mindist = dist;
        }
    }
    
    LOG("<[%s] %d attackers (%s)>",this->name.c_str(),attackers.size(),nearest?nearest->name.c_str():" - ");

    /// check flee
    if(HAS_MASK(behaviour,BehaviourFlees))
    {
        if(HAS_MASK(behaviour,BehaviourAggressive) && hp > (maxhp*0.2))
        {
            LOG("<[%s] too aggressive to flee>",this->name.c_str());
        }
        else
        {
            if(!attackers.empty())
            {
                move = awayFromAttacker(nearest);
                LOG("<[%s] fled>",this->name.c_str());
            }
        }
    }
    
    if(!move.zero() && map->checkMove(this, move.X, move.Y))
    {
        map->moveObject(this,move.X,move.Y);
        return;
    }
    
    /// check actions, steal, eat, etc
    /// todo
    
    /// check can attack
    if( !attackers.empty() && NOT_MASK(behaviour,BehaviourPassive))
    {
        LOG("<[%s] wants to attack target>",nearest->name.c_str());
        
        Object *ranged = getWeaponForRanged();
        if((ranged!=NULL) && (ranged->range >= mindist))
        {
            attack(nearest,ranged);
            return;
        }
        else if(mindist <= 1)
        {
            attack(nearest);
            return;
        }
    }
    
    /// check movement
    if(nearest && HAS_MASK(behaviour,BehaviourAggressive))
    {
        move = towardAttacker(nearest);
        LOG("<[%s] Wants to move toward target>",this->name.c_str());
    }
    else if(nearest && HAS_MASK(behaviour,BehaviourTimid))
    {
        move = awayFromAttacker(nearest);
        LOG("<[%s] Wants to move away from target>",this->name.c_str());
    }
    
    if(move.zero())
    {
       move = randomMove();
       LOG("<[%s] Wants to move randomly>",this->name.c_str());
    }
    
    if(!move.zero() && map->checkMove(this, move.X, move.Y))
    {
        //LOG("<[%s] moved>",this->name.c_str());
        map->moveObject(this,move.X,move.Y);
    }
    else
    {
        //LOG("<[%s] didn't move>",this->name.c_str());
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

/// this is kinda ok for NPCs but isn't very good for player characters
Object *Monster::getWeaponForRanged()
{
    foreachp(ObjectMap, obj, equipment)
    {
        Object *weapon = obj->second;
        if(weapon->_flags.wieldable && (weapon->range > 1))
        {
            return weapon;
        }
    }
    
    return NULL;
}

/// this is more valid than the above ranged version, but still pretty meh
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
    
    if(dmgs.empty())
        dmgs.push_back(Damage(1));
    
    return dmgs;
}

void Monster::onDamagedBy(Object *attacker,Damage damage)
{
    attackers.push_back(attacker);
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
