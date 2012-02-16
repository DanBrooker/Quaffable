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

//#if defined(__APPLE__)
//    #include "CoreFoundation/CFBundle.h"
//#elif defined __linux__
//    #warning "Untested on Linux"
//#elif defined _WIN32 || defined _WIN64
//    #warning "Untested on Linux"
//#else
//    #error "Unknown platform"
//#endif


std::string stringFormat(std::string format, ...)
{
    char *buffer;
    va_list args;
    va_start(args, format);
    vasprintf(&buffer,format.c_str(), args);
    va_end(args);
    
    return std::string(buffer);
}

std::string filenameWithFormat(std::string format, ...)
{
    char *buffer;
    va_list args;
    va_start(args, format);
    vasprintf(&buffer,format.c_str(), args);
    va_end(args);
    
    char *name = getenv("EXECUTABLE_NAME"); // this is a bad way to do this, it's OSX specific atm
    
    std::string path = stringFormat("%s.app/Contents/Resources/%s",name,buffer);
    
    return path;
}

#endif /* STRINGER_H_INC */