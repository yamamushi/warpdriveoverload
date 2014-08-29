//
//  graphchart.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__graphchart__
#define __warpdriveoverloaded__graphchart__

#include <ncurses.h>

#include "shell.h"
#include "window.h"
#include "tr1_wrapper.h"
#include "widget.h"

#include <string>
#include <vector>

struct GraphChartPoint {
    
    int m_X, m_Y;
    int m_color;
    
    std::string m_symbol;
    bool m_hidden;
    
    GraphChartPoint(int x = -1, int y = -1, int color = -1, std::string symbol = "", bool hidden = false)
    : m_X(x), m_Y(y), m_color(color), m_symbol(symbol), m_hidden(hidden){}
    
};

class GraphChart : public Widget {
    
public:
    
    GraphChart(_SharedPtr<ncursesWindow> parent, int xSize, int ySize);
    
    void render();
    void refresh();
    
    void resize(int xSize, int ySize){m_xSize = xSize; m_ySize = ySize;}

    void hideBars(){m_showBars = false;}
    void showBars(){m_showBars = true;}
    void toggleBars(){m_showBars = !m_showBars;}
    
    void hideBorder(){m_showBars = false;}
    void showBorder(){m_showBars = true;}
    void toggleBorder(){m_showBars = !m_showBars;}
    
    void addChartPoint(_SharedPtr<GraphChartPoint> point);
    void removeChartPoint(_SharedPtr<GraphChartPoint> point);
    
    void handleKeys(int input);

private:
    
    void generateChart();
    void fill();
    void placePoint(_SharedPtr<GraphChartPoint> point);
    void placeAllPoints();
    void removePoint(_SharedPtr<GraphChartPoint> point);
    
    int m_rows;
    int m_cols;
    
    int m_height;
    int m_width;
    
    int m_xSize;
    int m_ySize;
    
    bool m_showBars;
    bool m_showBorder;
    
    std::vector<_SharedPtr<GraphChartPoint> > m_chartPoints;
};


#endif /* defined(__warpdriveoverloaded__graphchart__) */
