/*
 *  FantasyRL.cpp
 *  Roguelike
 *
 *  Created by Daniel Brooker on 29/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "FantasyRL.h"

#include "Stringer.h"
#include "LabelValue.h"
#include "Player.h"

#include "World.h"
#include "Map.h"

FantasyRL::FantasyRL()
{
	init_window();
	init_world();
	
	menuWindow = new ExitMenu(Rect(256-24,128,140+32,64+24));
	
	rootWindow = new Window(Rect(0,0,width,height));
	rootWindow->delegate = world;
	rootWindow->eventDelegate = world;
	rootWindow->texture = sprite;
	rootWindow->getCentreLabel()->setString("FantasyRL");
	rootWindow->getRightLabel()->setString("v0.1");
	
	character = new Window(Rect(16,24,140+32,32+16));
	character->borderStyle = Border_Single;
	character->getLeftLabel()->setString("Draconis");
	character->getLeftLabel()->setColour(Colour::yellow());
	
	Label *familyLabel = new Label("Static Label");
	familyLabel->setFrame(Rect(16,18,100,40));
	familyLabel->setColour(Colour(1,1,1));
	character->add(familyLabel);
	
    CallBack<Player, std::string> *getHealth = new CallBack<Player, std::string>(player,&Player::hpDescription);
    LabelValue<std::string,Player> *health = new LabelValue<std::string,Player>("",getHealth);
	health->setFrame(Rect(16,18+12,100,40));
	health->setColour(Colour(0,1,0));
	character->add(health);
	
	rootWindow->add(character);
}

FantasyRL::~FantasyRL()
{
}

void FantasyRL::init_world()
{
	int worldSize = 200;
	
	rnd =  new Random(42);
	
	sprite = new Sprite(filenameWithFormat("tileset.png") /*"FantasyRL.app/Contents/Resources/tileset.png"*/,16);
    world = new World();
    
    world->setMap(new Map(worldSize));
	
	player = new Player();
	player->setTransparent(false);
	player->setPassable(false);
	//	player->setSight(50);
    
    world->getMap()->addObject(12,12,player);
	world->getMap()->setPlayer(player);
    
    world->getMap()->createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
    
    //- Test Monster
//    Ascii *ascii = new Ascii(LETTER_k+16,Colour::cyan(),Colour::black());
//	Monster *monster = new Monster(ascii);
//    monster->name = "Kobold";
//	monster->speed = SpeedNormal;
//    monster->setMaxHP(2);
//    monster->behaviour = BehaviourTimid;
//	world->getMap()->addObject(20,20,monster);
//	world->getMap()->monsters.push_back(monster);
    
    for(int i=0;i<10;i++)
    {
        Ascii *ascii = new Ascii(LETTER_k+16,Colour(0,1,1),Colour(0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = "Kobold";
        monster->speed = (Speed)(rand()%SpeedCount);
        monster->setMaxHP(rand()%4);
        monster->behaviour = (rand()%BehaviourCount);
        world->getMap()->addObject(rand()%100,rand()%100,monster);
        world->getMap()->monsters.push_back(monster);
    }
}