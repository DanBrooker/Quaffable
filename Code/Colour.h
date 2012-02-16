/*
 *  Colour.h
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#ifndef COLOUR_H_INC
#define COLOUR_H_INC 

class Colour 
{
	public:
		float R,G,B,A;
		
		Colour();
		Colour(float r,float g,float b);
		Colour(float r,float g,float b, float a);
		
		static Colour Black();
		static Colour White();
		static Colour Clear();
		
		static Colour Red();
		static Colour Green();
		static Colour Blue();
		
		static Colour Yellow();
		static Colour Cyan();
		static Colour Magenta();
};

#endif /* COLOUR_H_INC */