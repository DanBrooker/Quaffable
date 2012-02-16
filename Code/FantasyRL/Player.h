/*
 *  Player.h
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef PLAYER_H_INC
#define PLAYER_H_INC 

#include "Monster.h"

typedef struct {
//	unsigned passable:1;
//	unsigned transparent:1;
	unsigned _reserved:32;
} PlayerFlags;

typedef struct {
	// academic
	unsigned read:1;
	unsigned _academic_reserved:31;
	
	// religion
	unsigned atheist:1;
	unsigned monotheist:1;
	unsigned pagan:1;
	unsigned _religion_reserved:29;
	
	// combat related
	unsigned passifist:1;
	unsigned _combat_reserved:31;
	unsigned kills;
	
	// food related
	unsigned fasting:1;
	unsigned vegan:1;
	unsigned vegetarian:1;
	unsigned cannnibal:1;
	unsigned _food_reserved:28;
	
	// game specific
//	unsigned cannnibal:1;
	unsigned _game_reserved:32;
	
} PlayerAchievements;

class Player: public Monster
{
	private:
		PlayerFlags _flags;
    public:
    
		Player();
};

#endif /* PLAYER_H_INC */