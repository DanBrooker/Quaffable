//
//  Point.h
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef POINT_H_INC
#define POINT_H_INC

#include <list>

class Rect;

class Point
{
public:
    int X,Y;
    Point();
    Point(int x,int y);
    
    bool zero();
    
    bool operator==(Point &other);
    bool operator!=(Point &other);
    
    float distance(Point b);
};

typedef std::list<Point> Points;
typedef Point LocalCoord;
typedef Point WorldCoord;

inline Point randomPointInRect(Rect rect);
inline Point centreOfRect(Rect rect);

#endif /* POINT_H_INC */
