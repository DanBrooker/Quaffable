/*
 *  Types.h
 *  Roguelike
 *
 *  Created by Daniel on 11/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */
 
#ifndef TYPES_H_INC
#define TYPES_H_INC 

#include <map>
#include <list>
#include <vector>
#include <string>

#include "SDL/SDL.h"

class Object;
class Window;
class Roguelike;
class Monster;

typedef std::list<std::string> Strings; 
typedef std::list<Window*> Windows;
typedef std::list<Object*> Objects;
typedef std::list<Monster*> Monsters;

//typedef map<int,list<Object*> > ObjectMap;

typedef bool (*KeyAction)(void);
typedef std::map<SDLKey,KeyAction> KeyMap;

class Point
{
	public:
		int X,Y;
		Point() {X=0,Y=0;};
		Point(int x,int y) {X=x,Y=y;};
};

typedef std::list<Point> Points;
typedef Point LocalCoord;
typedef Point WorldCoord;

class Rect
{
	public:
		int X,Y,Width,Height;
		Rect() {X=0,Y=0,Width=0,Height=0;};
		Rect(int x,int y,int width,int height) {X=x,Y=y,Width=width,Height=height;};
};

inline Rect randomRectInRect(Rect rect,int min, int max)
{
    int width = min+rand()%max;
    int height = min+rand()%max;
    int x = rect.X + (rand() % (rect.Width - width));
    int y = rect.Y + (rand() % (rect.Height - height)); 
    return Rect(x,y,width,height);
}

inline Point randomPointInRect(Rect rect)
{
    return Point(rect.X + (rand() % rect.Width),rect.Y + (rand() % rect.Height));
}

inline Point centreOfRect(Rect rect)
{
    return Point(rect.X+(rect.Width/2),rect.Y+(rect.Height/2));
}

template < class Class, typename ReturnType>
class CallBack
{
public:
    
    typedef ReturnType (Class::*Method)(void);
    
    CallBack(Class* _class_instance, Method _method)
    {
        class_instance = _class_instance;
        method        = _method;
    };
    
    ReturnType operator()(void)
    {
        return (class_instance->*method)();
    };
    
    ReturnType execute()
    {
        return (class_instance->*method)();
    };
    
private:
    
    Class*  class_instance;
    Method  method;
};

#define YES 1
#define NO 0

#define ARRAY2D(i_i,j_j,w_w) (i_i+(w_w*j_j))
#define foreach(type,counter,collection) for(type::iterator counter = collection.begin(); counter != collection.end(); counter++)
#define foreachp(type,counter,collection) for(type::iterator counter = collection->begin(); counter != collection->end(); counter++)
#define DEV (Roguelike::dev)

#define MAX(x,y) ( (x>y)?x:y )
#define MIN(x,y) ( (x<y)?x:y )

#endif /* TYPES_H_INC */