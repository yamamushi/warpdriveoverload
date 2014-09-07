//
//  drawing.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
//
//  A set of functions for drawing
//
//
//

#ifndef __warpdriveoverloaded__drawing__
#define __warpdriveoverloaded__drawing__

void plotLine(int x0, int y0, int x1, int y1);
void plotCircle(int xm, int ym, int r);
void plotEllipseRect(int x0, int y0, int x1, int y1);
void plotQuadBezierSeg(int x0, int y0, int x1, int y1, int x2, int y2);
void plotLineAA(int x0, int y0, int x1, int y1);
void plotQuadBezierSegAA(int x0, int y0, int x1, int y1, int x2, int y2);
void plotLineWidth(int x0, int y0, int x1, int y1, double wd);
void plotRotatedEllipseRect(int x0, int y0, int x1, int y1, long zd);
void plotCubicBezierSeg(int x0, int y0, double x1, double y1, double x2, double y2, int x3, int y3);
void plotOptimizedEllipse(int xm, int ym, int a, int b);
void plotQuadBezier(int x0, int y0, int x1, int y1, int x2, int y2);
void plotQuadRationalBezierSeg(int x0, int y0, int x1, int y1, int x2, int y2, double w);
void plotQuadRationalBezier(int x0, int y0, int x1, int y1, int x2, int y2, double w);
void plotRotatedEllipse(int x, int y, int a, int b, double angle);
void plotRotatedEllipseRect(int x0, int y0, int x1, int y1, long zd);
void plotCubicBezierSeg(int x0, int y0, double x1, double y1, double x2, double y2, int x3, int y3);
void plotCubicBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
void plotCircleAA(int xm, int ym, int r);
void plotEllipseRectAA(int x0, int y0, int x1, int y1);
void plotQuadRationalBezierSegAA(int x0, int y0, int x1, int y1, int x2, int y2, double w);
void plotCubicBezierSegAA(int x0, int y0, double x1, double y1, double x2, double y2, int x3, int y3);
void plotQuadSpline(int n, int x[], int y[]);
void plotCubicSpline(int n, int x[], int y[]);



#endif /* defined(__warpdriveoverloaded__drawing__) */
