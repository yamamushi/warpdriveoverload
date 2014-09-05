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

#include "bresenham2d.h"
#include "drawing.h"

#include <string>
#include <vector>

struct GraphChartPoint {
    
    int m_X, m_Y;
    int m_color;
    
    std::string m_symbol;
    bool m_hidden;
    
    bool m_specialSymbol;
    
    GraphChartPoint(int x = -1, int y = -1, int color = -1, std::string symbol = "", bool hidden = false, bool special = false)
    : m_X(x), m_Y(y), m_color(color), m_symbol(symbol), m_hidden(hidden), m_specialSymbol(special){}
    
};

class GraphChart : public Widget {
    
public:
    
    GraphChart(_SharedPtr<ncursesWindow> parent, int xpos=0, int ypos=0);
    
    void render();
    void refresh();
    
    void resize(int xSize, int ySize);
    int getXSize(){return m_xSize;}
    int getYSize(){return m_ySize;}
    void setSize(int xSize, int ySize);
    
    int getRows(){return m_rows;}
    int getCols(){return m_cols;}
    
    int getHeight(){return m_height;}
    int getWidth(){return m_width;}

    void hideBars(){m_showBars = false;}
    void showBars(){m_showBars = true;}
    void toggleBars(){m_showBars = !m_showBars;}
    
    void hideBorder(){m_showBars = false;}
    void showBorder(){m_showBars = true;}
    void toggleBorder(){m_showBars = !m_showBars;}
    
    void addChartPoint(_SharedPtr<GraphChartPoint> point);
    void removeChartPoint(_SharedPtr<GraphChartPoint> point);
    std::vector<_SharedPtr<GraphChartPoint> > getAllChartPoints(){return m_chartPoints;}
    void clearAllChartPoints();
    
    void addRawChartPoint(_SharedPtr<GraphChartPoint> point);
    void removeRawChartPoint(_SharedPtr<GraphChartPoint> point);
    std::vector<_SharedPtr<GraphChartPoint> > getAllRawChartPoints(){return m_rawchartPoints;}
    void clearAllRawChartPoints();
    
    void clearAll(){wclear(m_parent->get());}

    void resizeWindow(int height, int width){m_height = height; m_width = width; generateChart();}
    void handleKeys(int input);

    void removePoint(_SharedPtr<GraphChartPoint> point);
    void placeRawPoint(_SharedPtr<GraphChartPoint> point);
    void placeAllPoints();
    
    void generateChart();
    void fill();

    
    void drawAt(int x=-1, int y=-1, std::string symbol=" ", int color=0);
    // A callback that does nothing
    void failedAt(int x=-1, int y=-1){};
    
    void drawLine(int x1, int y1, int x2, int y2, std::string symbol, int color);

    
private:

    int m_xpos;
    int m_ypos;
    
    int m_rows;
    int m_cols;
    
    int m_height;
    int m_width;
    
    int m_xSize;
    int m_ySize;
    
    bool m_showBars;
    bool m_showBorder;
    
    std::vector<_SharedPtr<GraphChartPoint> > m_chartPoints;
    std::vector<_SharedPtr<GraphChartPoint> > m_rawchartPoints;

};


#endif /* defined(__warpdriveoverloaded__graphchart__) */
