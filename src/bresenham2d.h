#pragma oncebres

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


void bresenham2d(int x0, int y0, int x1, int y1, _STD_FUNCTION(void(int, int)) passCommand);


#endif
