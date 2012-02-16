/*
 *  Colour.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#include "Colour.h"
#include <cstdio>

Colour::Colour()
{
	R = 1.0;
	G = 1.0;
	B = 1.0;
	A = 1.0;
}

Colour::Colour(float r,float g,float b)
{
	R = r;
	G = g;
	B = b;
	A = 1.0;
}

Colour::Colour(float r,float g,float b,float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Colour Colour::Black()
{
	return Colour(0,0,0);
}

Colour Colour::White()
{
	return Colour(1.0,1.0,1.0);
}

Colour Colour::Clear()
{
	return Colour(0,0,0,0);
}

Colour Colour::Red()
{
	return Colour(1.0,0,0);
}
Colour Colour::Green()
{
	return Colour(0,1.0,0);
}
Colour Colour::Blue()
{
	return Colour(0,0,1.0);
}
		
Colour Colour::Yellow()
{
	return Colour(1.0,1.0,0);
}

Colour Colour::Cyan()
{
	return Colour(0,1.0,1.0);
}
Colour Colour::Magenta()
{
	return Colour(1.0,0,1.0);
}