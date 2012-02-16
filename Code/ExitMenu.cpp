/*
 *  ExitMenu.cpp
 *  Roguelike
 *
 *  Created by Daniel on 20/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "ExitMenu.h"
#include "Roguelike.h"
#define RETURN_TO_GAME 0
#define DEBUG_MODE 1
#define EXIT 2

ExitMenu::ExitMenu(Rect rect) : Menu(rect)
{
	borderStyle = Border_Double;
	getCentreLabel()->setString("Paused");
	getCentreLabel()->setColour(Colour::Red());
	
	Label *optionsLabel = new Label("Return to Game");
	optionsLabel->setFrame(Rect(16,18+12,100,40));
	add(optionsLabel);
	
	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
	devLabel->setFrame(Rect(16,18+24,100,40));
	devLabel->setString("Debug");
	add(devLabel);
	
	Label *exitLabel = new Label("Exit");
	exitLabel->setFrame(Rect(16,18+36,100,40));
	add(exitLabel);
}

int ExitMenu::numberOfItems()
{
	return 3;
}

void ExitMenu::didSelectItem(int index)
{
	switch(index)
	{
		case RETURN_TO_GAME:
			close();
			break;
		case DEBUG_MODE:
			// nothing
			break;
		case EXIT:
			SDL_Quit();
			exit(0);
			break;
	}
}