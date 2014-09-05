//
//  graphchart.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "graphchart.h"
#include <stdlib.h>
#include <algorithm>

GraphChart::GraphChart(_SharedPtr<ncursesWindow> parent, int xpos, int ypos) : Widget(parent, xpos, ypos){
    
    m_showBars = true;
    m_showBorder = true;
    
    m_xSize = 3;
    m_ySize = 4;
    
    getmaxyx(getParent()->get(), m_height, m_width);
    
    generateChart();
    
}

void GraphChart::setSize(int xSize, int ySize){
    
    
    if(xSize < 2)
        m_xSize = 2;
    else
        m_xSize = xSize;
    
    if(xSize < 1)
        m_xSize = 1;
    else
        m_ySize = ySize;
    
}

void GraphChart::fill(){
    
    //wattrset(m_parent->get(), m_parent->getNormalColor());
    if(m_showBars)
    for(int x = 0; x < m_width; x++){
        for(int y = 0; y < m_height; y++){
            if(!(x % m_xSize) && !(y % m_ySize)){
                if(m_showBars)
                    getParent()->drawAt(x + getXpos(), y + getYpos(), '+');
            }
            else if(!(x % m_xSize)){
                if(m_showBars)
                    getParent()->drawAt(x + getXpos(), y + getYpos(), '|');
            }
            else if(!(y % m_ySize)){
                if(m_showBars)
                    getParent()->drawAt(x + getXpos(), y + getYpos(), '=');
            }
        }
    }
    
    if(m_showBorder)
        getParent()->setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
}


void GraphChart::render(){
    
    generateChart();
    placeAllPoints();
    
}


void GraphChart::generateChart(){
    
    m_rows = m_height / m_ySize;
    m_cols = m_width / m_xSize;
    
}


void GraphChart::placeRawPoint(_SharedPtr<GraphChartPoint> point){
    
    if(!point->m_hidden){
        if( point->m_Y > 0 && point->m_Y < m_height){
            if(point->m_X > 0 && point->m_X < m_width){
                getParent()->drawAt( point->m_X + getXpos(), point->m_Y + getYpos(), point->m_symbol, point->m_fg, point->m_bg, point->m_attr);
            }
        }
    }
    
//    wrefresh(getParent()->get());
}



void GraphChart::placeAllPoints(){
    
    for(size_t chartX = 0; chartX < m_chartPoints.size(); chartX++){
        
        int pointX = m_chartPoints.at(chartX)->m_X;
        int pointY = m_chartPoints.at(chartX)->m_Y;
        
        if(!m_chartPoints.at(chartX)->m_hidden){
            for(int x = 0; x < m_width; x++){
                for(int y = 0; y < m_height; y++){
                    if( (y % m_ySize+1) && (x % m_xSize)){
                        if(y != m_height-1 && x < m_width-1){
                            if((x > m_xSize*pointX) && (x < (m_xSize*pointX)+m_xSize+1)){
                                if((y > m_ySize*pointY) && (y < (m_ySize*pointY)+m_ySize+1)){
                                    if(m_showBorder){
                                        if( y > 0){
                                            getParent()->drawAt( x + getXpos(),
                                                                y + getYpos(),
                                                                m_chartPoints.at(chartX)->m_symbol,
                                                                m_chartPoints.at(chartX)->m_fg,
                                                                m_chartPoints.at(chartX)->m_bg,
                                                                m_chartPoints.at(chartX)->m_attr);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(size_t rawchartX = 0; rawchartX < m_rawchartPoints.size(); rawchartX++){
        if(!m_rawchartPoints.at(rawchartX)->m_hidden){
            if( m_rawchartPoints.at(rawchartX)->m_Y > 0 && m_rawchartPoints.at(rawchartX)->m_Y < m_height){
                if(m_rawchartPoints.at(rawchartX)->m_X > 0 && m_rawchartPoints.at(rawchartX)->m_X < m_width){
                    getParent()->drawAt( m_rawchartPoints.at(rawchartX)->m_X + getXpos(),
                                        m_rawchartPoints.at(rawchartX)->m_Y + getYpos(),
                                        m_rawchartPoints.at(rawchartX)->m_symbol,
                                        m_rawchartPoints.at(rawchartX)->m_fg,
                                        m_rawchartPoints.at(rawchartX)->m_bg,
                                        m_rawchartPoints.at(rawchartX)->m_attr);
                }
            }
        }
    }
}

void GraphChart::removePoint(_SharedPtr<GraphChartPoint> point){
    
    //wattrset(m_parent->get(), m_parent->getNormalColor());
    
    std::vector<_SharedPtr<GraphChartPoint> >::iterator it = std::find(m_chartPoints.begin(), m_chartPoints.end(), point);
    if (it != m_chartPoints.end()){
        
        int pointX = point->m_X;
        int pointY = point->m_Y;
        
        for(int x = 0; x < m_width; x++){
            for(int y = 0; y < m_height; y++){
                if( (y % m_ySize+1) && (x % m_xSize)){
                    if((x > m_xSize*pointX) && (x < (m_xSize*pointX)+m_xSize+1)){
                        if((y > m_ySize*pointY) && (y < (m_ySize*pointY)+m_ySize+1)){
                            if(y == ((m_ySize*pointY)+m_ySize) || y < m_height-1)
                                if( y > 0){
                                    getParent()->drawAt( x + getXpos(), y + getYpos(), " ");
                                }
                            if(m_showBars){
                                if(y == ((m_ySize*pointY)+m_ySize) && y < m_height-1)
                                    getParent()->drawAt( x + getXpos(), y + getYpos(), "=");
                            }
                            if(m_showBorder){
                                if( y == m_height-1)
                                    getParent()->drawAt( x + getXpos(), y + getYpos(), "=");
                            }
                            if(!m_showBorder){
                                if( y == m_height-1)
                                    getParent()->drawAt( x + getXpos(), y + getYpos(), " ");
                            }
                        }
                    }
                }
            }
        }
    }
    //wrefresh(getParent()->get());
}

void GraphChart::addRawChartPoint(_SharedPtr<GraphChartPoint> point){
    
    removeRawChartPoint(point);
    m_rawchartPoints.push_back(point);
    
}

void GraphChart::removeRawChartPoint(_SharedPtr<GraphChartPoint> point){
    std::vector<_SharedPtr<GraphChartPoint> >::iterator it = std::find(m_rawchartPoints.begin(), m_rawchartPoints.end(), point);
    if (it != m_rawchartPoints.end()){
        m_rawchartPoints.erase(std::remove(m_rawchartPoints.begin(), m_rawchartPoints.end(), point), m_rawchartPoints.end());
    }
}

void GraphChart::addChartPoint(_SharedPtr<GraphChartPoint> point){
    
    removeChartPoint(point);
    m_chartPoints.push_back(point);
    
}

void GraphChart::removeChartPoint(_SharedPtr<GraphChartPoint> point){
    std::vector<_SharedPtr<GraphChartPoint> >::iterator it = std::find(m_chartPoints.begin(), m_chartPoints.end(), point);
    if (it != m_chartPoints.end()){
        m_chartPoints.erase(std::remove(m_chartPoints.begin(), m_chartPoints.end(), point), m_chartPoints.end());
    }
}



void GraphChart::drawAt(int x, int y, std::string symbol, int fg, int bg, int attr){
    
    if(y == -1 || x == -1)
        return;
    
    _SharedPtr<GraphChartPoint> point(new GraphChartPoint( x, y, symbol, fg, bg, attr));
    addRawChartPoint(point);
    
}




void GraphChart::drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg, int bg, int attr){
    
    bresenham2d(x1, y1, x2, y2, _STD_BIND(&GraphChart::drawAt, this, std::placeholders::_1, std::placeholders::_2, symbol, fg, bg, attr));
    
}



void GraphChart::clearAllChartPoints(){

    m_chartPoints.clear();

}

void GraphChart::clearAllRawChartPoints(){
   
    for(int x=0; x < m_rawchartPoints.size(); x++){
        removePoint(m_rawchartPoints.at(x));
    }
    wrefresh(getParent()->get());
    m_rawchartPoints.clear();
    
}


void GraphChart::refresh(){
    
    fill();
    wrefresh(getParent()->get());
    
}

void GraphChart::resize(int xSize, int ySize){
    
    if(xSize > 1)
        m_xSize = xSize;
    if(ySize > 0)
        m_ySize = ySize;
    
    m_parent->clearScreen();
    refresh();
    
}


void GraphChart::handleKeys(int input){
    
    
}
