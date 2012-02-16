/*
 *  Monster.h
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef MONSTER_H_INC
#define MONSTER_H_INC 

#include "Object.h"
#include "Types.h"
#include "Lightmap.h"

class Weapon;

typedef enum {
	SpeedFrozen,
	SpeedSlow,
	SpeedNormal,
	SpeedFast
} Speed;

typedef enum {
    AIPassive,
    AIDefensive,
    AIAggressive,
} AI;

typedef struct {
//	unsigned passable:1;
//	unsigned transparent:1;
	unsigned _reserved:32;
} MonsterFlags;

typedef struct {
	// covert

	// combat
	
	// faith
	
	// magic 
	
	// crafting
	
	// general
} Skills;

class Monster: public Object
{
	protected:
		MonsterFlags _flags;
		Lightmap *sightMap;
		
        unsigned hp,maxhp;
        unsigned mp,maxmp;
    
        std::map<std::string, Object *> equipment;
		
	public:

		unsigned sight;
		Speed speed;
	
		Monster();
		Monster(Ascii *ascii);
    
        int getHP();
        int adjustHP(int delta);
        void setHP(int hitpoints);
        std::string hpDescription();
        
        int getMaxHP();
        void setMaxHP(int maxHitPoints);
    
        Object *getWeaponForMelee();
    
        virtual Damage getMeleeDamage();
		
		virtual void updateAscii();
		virtual void performTurn();
	
		void calculateSight();
		virtual bool canSee(int x, int y);
		
		static void load();
    
        virtual void onDeath();
        virtual void onDamagedBy(Object *attacker,Damage damage);
//        virtual void onHealedBy(Object *attacker,Damage damage);
};

inline std::string stringForSpeed(Speed s)
{
	std::string name;
	switch((int)s)
	{
		case SpeedSlow:
			name = "Slow";
			break;
		case SpeedNormal:
			name = "Normal";
			break;
		case SpeedFast:
			name = "Fast";
			break;
	}
	return name;
}

#endif /* MONSTER_H_INC */
