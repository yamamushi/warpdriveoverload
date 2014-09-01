//
//  bresenham2d.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/30/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
//
// slightly Modified from http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C.2B.2B

#ifndef warpdriveoverloaded_bresenham2d_h
#define warpdriveoverloaded_bresenham2d_h


#include "tr1_threading.h"
#include <algorithm>
#include <cmath>
#include <utility>


void bresenham2d(int x0, int y0, int x1, int y1, _STD_FUNCTION(void(int, int)) passCommand) {
    
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        passCommand(x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}
#endif
