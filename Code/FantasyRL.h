/*
 *  FantasyRL.h
 *  Roguelike
 *
 *  Created by Daniel Brooker on 29/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FANTASYRL_H_INC
#define FANTASYRL_H_INC 

//#include "SDL/SDL.h"
//#include "SDL_image/SDL_image.h"
//#include "SDL_OpenGL.h"
//#include "SDLWindow.h"
//#include "Window.h"
//#include "World.h"
//#include "Image.h"
//#include "Timer.h"
//#include "ExitMenu.h"
//#include <string>
//#include "Player.h"

#include "Roguelike.h"

class Player;

class FantasyRL : public Roguelike
{
	protected:
		Player *player;
	public:
		FantasyRL();
		~FantasyRL();
		virtual void init_world();
};

#endif /* FANTASYRL_H_INC */