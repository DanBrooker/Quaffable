/*
 *  Object.h
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#ifndef OBJECT_H_INC
#define OBJECT_H_INC 

#include "Types.h"
#include <vector>
#include <list>

#include "Ascii.h"
#include "Damage.h"

class Map;
class Tile;

typedef struct 
{
	unsigned passable:1;
	unsigned transparent:1;
    unsigned carryable:1;
    unsigned holdable:1;
    unsigned wieldable:1;
    unsigned wearable:1;
	unsigned _reserved:27;
} ObjectFlags;

class Object {
	protected:
		AsciiGroup *asciis;
        std::list<Object *> *inventory;
	public:
		Tile *parent;
		std::string name;
		std::string shortDescription;
		std::string longDescription;
        float weight;
		
		ObjectFlags _flags;
				
		Object();
		Object(Ascii *ascii);
		Object(AsciiGroup *ascii);
		
		void setParent(Tile *tile);
		Tile* getParent();
		
        Map *getMap();
		void removeFromTile();
    
        Point getPosition();
		
		void setPassable(bool passable);
		bool passable();
		
		void setTransparent(bool transparent);
		bool transparent();
    
        virtual Damage getMeleeDamage();
        virtual Damage getThrowDamage();
    
        virtual Damage calculateMeleeDamageFrom(Object *object);
		
		Ascii* getAscii();
		virtual void updateAscii();
    
        void addObjectToInventory(Object *object);
        void removeObjectFromInventory(Object *object); 
        std::list<Object *> *getInventory();
        void dumpInventory();
    
        virtual void onDeath();
        virtual void onDamagedBy(Object *attacker,Damage damage);
        virtual void onHealedBy(Object *attacker,Damage damage);
        virtual void onDamagedObject(Object *target,Damage damage);
};

#endif /* OBJECT_H_INC  */

/*

 ADOMs itemset:
 
 [  Armor, shields, cloaks, boots, girdles, gauntlets and helmets
 *  Gems and rocks
 ]  Tools (keys, writing sets, elemental orbs, and various other things)
 '  Necklaces
 (  Melee weapons (all of them)
 }  Missile weapons (bows, crossbows, slings)
 /  Missiles (arrows, quarrels, etc)
 =  Rings
 \  Wands
 !  Potions
 ?  Scrolls
 ~  Bracers
 %  Food (inc corpses and herbs)
 $  Gold
 {  Musical Instruments
 "  Books

 
Angband items:
 
 , : Food, Mushrooms
 | : Edged weapon
 \ : Hafted weapon, Shovel, Pick
 / : Polearm
 } : Sling, Bow, Crossbow
 { : Ammo
 ] : Armor
 ( : Armor
 [ : Armor
 ) : Shield
 = : Ring
 " : Amulet
 ? : Scrolls, Books
 ! : Potions
 - : Wands, Rods
 _ : Staffs
 ~ : Junk, Chest, Torch, Bones, Some magic light sources
 $ : Treasure
 & : Pile of mixed items.
 
 § : Not used
 ' : Not used (too similar to ` and ´ maybe?)
 ° : Not used (Is this 7-Bit ASCII ? Edit: No, and § also isn't)

*/

