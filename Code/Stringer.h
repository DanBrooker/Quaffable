//
//  Stringer.h
//  Roguelike
//
//  Created by Daniel Brooker on 23/07/11.
//  Copyright 2011 Nocturnal Code Limited. All rights reserved.
//

#ifndef STRINGER_H_INC
#define STRINGER_H_INC

#include <string>

std::string stringFormat(std::string format, ...);
std::string filenameWithFormat(std::string format, ...);

#endif /* STRINGER_H_INC */