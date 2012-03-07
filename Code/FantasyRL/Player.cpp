/*
 *  Player.cpp
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Player.h"

Player::Player() : Monster(new Ascii(64,1.0,0,0))
{
	behaviour = BehaviourNone;
    sight = 20;
}