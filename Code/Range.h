//
//  Range.h
//  Roguelike
//
//  Created by Daniel Brooker on 20/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Window.h"
#include <string>

#ifndef RANGE_H
#define RANGE_H

class Range : public Window
{
protected:
    int selectedIndex;
    Display *selected;
public:
    Range();
    bool open;
    virtual void close();
    virtual bool handleEvents(SDL_Event *event);
    virtual int numberOfItems();
    virtual void didSelectItem(int index);
    virtual void add(Display *displayable);
    virtual bool wantsEvents();
    virtual void changeSelection();
};

#endif /* RANGE_H */ 