//
//  Rect.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Rect.h"
#include <cstdlib>

Rect::Rect() 
{
    X=0,Y=0,Width=0,Height=0;
}

Rect::Rect(int x,int y,int width,int height) 
{
    X=x,Y=y,Width=width,Height=height;
}

Rect randomRectInRect(Rect rect,int min, int max)
{
    int width = min+rand()%max;
    int height = min+rand()%max;
    int x = rect.X + (rand() % (rect.Width - width));
    int y = rect.Y + (rand() % (rect.Height - height)); 
    return Rect(x,y,width,height);
}