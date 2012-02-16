/*
 *  ExitMenu.h
 *  Roguelike
 *
 *  Created by Daniel on 20/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef EXITMENU_H
#define EXITMENU_H

#include "Menu.h"
#include "LabelValue.h"
#include <string>

class ExitMenu : public Menu
{

	public:
		ExitMenu(Rect rect);
		
		virtual int numberOfItems();
		virtual void didSelectItem(int index);
};

#endif /* EXITMENU_H */