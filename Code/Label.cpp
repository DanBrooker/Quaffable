/*
 *  Label.cpp
 *  Roguelike
 *
 *  Created by Daniel on 2/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Label.h"
#include "Roguelike.h"
#include "Colour.h"

Label::Label()
{
	Label("");
}

Label::Label(std::string text)
{
	parent = NULL;
	this->text = text;
	colour = Colour::White();
	bgColour = Colour::Black();
	selected = false;
}

void Label::setString(std::string text)
{
	this->text = text;
}

std::string Label::getString()
{
	return text;
}

void Label::setColour(Colour colour)
{
	this->colour = colour;
}

Colour Label::getColour()
{
	return colour;
}

void Label::setBackgroundColour(Colour colour)
{
	this->bgColour = colour;
}

Colour Label::getBackgroundColour()
{
	return bgColour;
}

void Label::setFrame(Rect frame)
{
	this->frame = frame;
}

Rect Label::getFrame()
{
	return frame;
}

void Label::setParent(Display* parent)
{
	this->parent = parent;
}

Display* Label::getParent()
{
	return parent;
}

void Label::setSelected(bool sel)
{
	selected = sel;
}

bool Label::getSelected()
{
	return selected;
}

float floatFromHex(char hexChar)
{
    float value = 1.0f;
    switch(hexChar)
    {
        case '0': value=0.0f; break;
        case '1': value=1.0f; break;
        case '2': value=2.0f; break;
        case '3': value=3.0f; break;
        case '4': value=4.0f; break;
        case '5': value=5.0f; break;
        case '6': value=6.0f; break;
        case '7': value=7.0f; break;
        case '8': value=8.0f; break;
        case '9': value=9.0f; break;
        case 'a':
        case 'A': value=10.0f; break;
        case 'b':
        case 'B': value=11.0f; break;
        case 'c':
        case 'C': value=12.0f; break;
        case 'd':
        case 'D': value=13.0f; break;
        case 'e':
        case 'E': value=14.0f; break;
        case 'f':
        case 'F': value=15.0f; break;
    }
    return value/15.0f;
}

Colour colourFromString(std::string hex)
{
    return Colour(floatFromHex(hex[0]), floatFromHex(hex[1]), floatFromHex(hex[2]));
}

void Label::display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates)
{
	unsigned tileW = (4*2);
	unsigned tileH = (6*2);
	unsigned width = parent->getFrame().Width;//, height = parent->getFrame().Height;
	unsigned nWide = width/tileW;
	//unsigned nHigh = height/tileH;
	unsigned xOff = frame.X/tileW;
	unsigned yOff = frame.Y/tileH;
	
	int i=0;
    std::string print = prefix() + text + suffix();
    
    Colour c1,c2;
    if(!selected)
    {
        c1 = colour;
        c2 = bgColour;
    }
    else
    {
        c1 = bgColour;
        c2 = colour;
    }
    
    int debug = 0;
	for(int m=0;m < print.size();m++)
	{        
        if(print[m]=='#') //eg #f0f
        {
            m += 4;
            if(!selected)
                c1 = colourFromString(print.substr(m-3,m-1));
        }
        else if(print[m]=='%')
        {
            if(!selected)
            {
                c1 = colour;
                c2 = bgColour;
            }
            else
            {
                c1 = bgColour;
                c2 = colour;
            }
            
            m++;
        }
        else if(print[m]=='<')
        {
            debug++;
            continue;
        }
        else if(print[m]=='>')
        {
            debug--;
            continue;
        }
        
        if(debug > 0 && !DEV)
        {
            continue;
        }
        
		int texI = ARRAY2D((i+xOff),yOff,nWide)*8;
		int colI = ARRAY2D((i+xOff),yOff,nWide)*16;
        
		Ascii a = Ascii(CHAR_TO_ASCII(print[m])+16,c1,c2); 
		displayTile(&texCoordinates[texI],&colCoordinates[colI],&bgColCoordinates[colI],a);
        i++;
    }
}

/*
void Label::displayTile(float *texture, float *colour, float *background, Ascii ascii)
{
	int row = ascii.Index / 16;
	int column = ascii.Index % 16;
	float ratio = 0.0625f;
	Colour fc = ascii.Foreground;
	Colour bc = ascii.Background;

	texture[0] = ratio*			column;		texture[1] = ratio*			row;	
	texture[2] = ratio+ratio*	column;		texture[3] = ratio*			row;
	texture[4] = ratio+ratio*	column;		texture[5] = ratio+ratio*	row;
	texture[6] = ratio*			column;		texture[7] = ratio+ratio*	row;

	colour[0] = fc.R;	colour[1] = fc.G; colour[2] = fc.B;  colour[3]  = fc.A;
	colour[4] = fc.R;	colour[5] = fc.G; colour[6] = fc.B;  colour[7]  = fc.A;
	colour[8] = fc.R;	colour[9] = fc.G; colour[10]= fc.B;  colour[11] = fc.A;
	colour[12] =fc.R;	colour[13] =fc.G; colour[14]= fc.B;  colour[15] = fc.A;
	
	background[0] = bc.R;	background[1] = bc.G; background[2] = bc.B;  background[3]  = bc.A;
	background[4] = bc.R;	background[5] = bc.G; background[6] = bc.B;  background[7]  = bc.A;
	background[8] = bc.R;	background[9] = bc.G; background[10]= bc.B;  background[11] = bc.A;
	background[12] =bc.R;	background[13] =bc.G; background[14]= bc.B;  background[15] = bc.A;
}
*/