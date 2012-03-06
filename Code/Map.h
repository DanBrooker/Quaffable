/*
 *  Map.h
 *  Roguelike
 *
 *  Created by Daniel on 24/04/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */



#ifndef MAP_H_INC
#define MAP_H_INC 

#include "SDL_OpenGL.h" 
#include "Object.h"

#include "Types.h"
#include "Tile.h"

#include "World.h"
class Monster;

class Map
{
	private:
		unsigned size;
		float *tex,*col,*bgCol;
		Tile *tiles;
    
        Monster *player;
		
		void displayTile(float *texture, float *colour,float *backgroundColour, Tile *tile, Monster *monster);
		
	public:
		World	*world;
        Monsters monsters;
        Objects	 objects;
        Rect	visibleRect;

		Map(unsigned size);
		
        void generate();
        void createRoom(Rect rect,Ascii floor);
    
        void update(Speed turnSpeed);
        void updateAscii();
        
        bool adjustPlayer(int i, int j);
        
        void setPlayer(Monster *player);
        Monster *getPlayer();

		// arrays to display
		void setTexturePointer(float *texurePointer);
		void setColourPointer(float *colourPointer);
		void setBackgroundColourPointer(float *bgColourPointer);
		
		// Display
		void display();
		
		void addObject(int x, int y,Object *object);
		void removeObject(Object *object);
		void moveObject(Object *object, int i, int j);
		bool checkMove(Object *object, int i, int j);
    
        bool checkCombat(Monster *monster, int i, int j);
        bool checkAction(Object *object, int i, int j);

		bool getTransparent(int x, int y);
    
        // Conflict
    
        Objects *getAggressors(Object *object);
        Objects *getTargets(Object *object);
};

#endif /* MAP_H_INC  */