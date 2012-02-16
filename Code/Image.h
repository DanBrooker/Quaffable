/*
 *  Image.h
 *  Roguelike
 *
 *  Created by Daniel on 30/01/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */
#ifndef IMAGE_H_INC
#define IMAGE_H_INC 

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_OpenGL.h"
#include <string>

class Image
{
	private:
		
	public:
		GLuint GLTextureId;
		unsigned Width,Height;
		Image(std::string filename);
//		~Image();
};

#endif /* IMAGE_H_INC */