/*
 *  Random.h
 *  Roguelike
 *
 *  Created by Daniel on 2/05/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#ifndef RANDOM_H_INC
#define RANDOM_H_INC

#include <cstdlib>

class Random 
{	
	private:
		static int rseed;
	public:
		static void setSeed(int seed);
		static int getInt();
};

#endif /* RANDOM_H_INC */