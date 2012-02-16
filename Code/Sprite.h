/*
 *  SpriteMap.h
 *  Roguelike
 *
 *  Created by Daniel on 30/01/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef SPRITE_H_INC
#define SPRITE_H_INC 

#include <string>
typedef unsigned SpriteIndex;

class Sprite
{
	private:
		unsigned texture;
		float *texCoordinates;
		
	public:
		unsigned Size;
	
		Sprite(std::string filename,unsigned size);
		void bind();
		void insertTexCoordinates(float *pointer, int index);
};

#endif /* SPRITE_H_INC */