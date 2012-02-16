/*
 *  Random.cpp
 *  Roguelike
 *
 *  Created by Daniel on 2/05/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "Random.h"

int Random::rseed = 0;

void Random::setSeed(int seed)
{
	static bool first = true;
	if(first)
	{
		rseed = seed;
		first = false;
	}
}