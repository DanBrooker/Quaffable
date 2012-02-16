/*
 *  SpriteMap.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/01/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Sprite.h"
#include "Image.h"

Sprite::Sprite(std::string filename,unsigned size)
{
	Image image(filename);
	Size = size;
	texture = image.GLTextureId;
	unsigned width = image.Width; //, height = 768;
	
	texCoordinates = (float*)malloc(sizeof(float) * size * size * 8);
	for(int i=0; i < size*size*8; i+=8)
	{
		int row = i / size, column = i % size;
		float ratio = size/width * 2;
		texCoordinates[i+0] = ratio*column,			texCoordinates[i+1] = ratio*row;
		texCoordinates[i+2] = ratio+ratio*column,	texCoordinates[i+3] = ratio*row;
		texCoordinates[i+4] = ratio+ratio*column,	texCoordinates[i+5] = ratio+ratio*row;
		texCoordinates[i+6] = ratio*column,			texCoordinates[i+7] = ratio+ratio*row;	
	}
}

void Sprite::bind()
{
	glBindTexture(GL_TEXTURE_2D,texture);
}

void Sprite::insertTexCoordinates(float *pointer, int index)
{
	for(int i=0; i < 4; i++)
		pointer[i] = texCoordinates[(index*8)+i];
}