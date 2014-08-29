//
//  graphchart.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "graphchart.h"
#include <stdlib.h>


GraphChart::GraphChart(_SharedPtr<ncursesWindow> parent, int xSize, int ySize) : Widget(parent), m_xSize(xSize), m_ySize(ySize){
    
    m_showBars = true;
    m_showBorder = true;
    
}

void GraphChart::fill(){
    
    getmaxyx(getParent()->get(), m_height, m_width);
    
    wattrset(m_parent->get(), m_parent->getNormalColor());
    
    for(int x = 0; x < m_width; x++){
        for(int y = 0; y < m_height; y++){
            if(!(x % m_xSize)){
                if(m_showBars)
                    mvwprintw(getParent()->get(), y, x,"%c", '|');
                wrefresh(getParent()->get());
            }
            else if(!(y % m_ySize) && y != m_height-2){
                if(m_showBars)
                    mvwprintw(getParent()->get(), y, x,"%c", '=');
                wrefresh(getParent()->get());
            }
            
        }
    }
    
    if(m_showBorder)
        getParent()->setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
    wrefresh(getParent()->get());
    
}


void GraphChart::render(){
    
    generateChart();
    mvwprintw(getParent()->get(), 5, 2,"%d", m_rows);
    mvwprintw(getParent()->get(), 8, 2,"%d", m_cols);
    randDirection();
    placeAllPoints();
    
}


void GraphChart::generateChart(){
    
    m_rows = m_height / m_ySize;
    m_cols = m_width / m_xSize;
}

void GraphChart::placePoint(_SharedPtr<GraphChartPoint> point){
    
    std::vector<_SharedPtr<GraphChartPoint> >::iterator it = std::find(m_chartPoints.begin(), m_chartPoints.end(), point);
    if (it != m_chartPoints.end()){
        int pointX = point->m_X;
        int pointY = point->m_Y;
        if(!point->m_hidden){
            for(int x = 0; x < m_width; x++){
                for(int x = 0; x < m_width; x++){
                    for(int y = 0; y < m_height; y++){
                        if( (y % m_ySize+1) && (x % m_xSize)){
                            if(y != m_height-1 && x < m_width-1){
                                
                                if((x > m_xSize*pointX) && (x < (m_xSize*pointX)+m_xSize+1)){
                                    if((y > m_ySize*pointY) && (y < (m_ySize*pointY)+m_ySize+1)){
                                        if(m_showBorder){
                                            if( y > 0){
                                                wattrset(m_parent->get(), COLOR_PAIR(point->m_color));
                                                mvwprintw(getParent()->get(), y, x,"%s", point->m_symbol.c_str());
                                                wattrset(m_parent->get(), m_parent->getNormalColor());
                                                wrefresh(getParent()->get());
                                                
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
    }
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
                                            wattrset(m_parent->get(), COLOR_PAIR(m_chartPoints.at(chartX)->m_color));
                                            mvwprintw(getParent()->get(), y, x,"%s", m_chartPoints.at(chartX)->m_symbol.c_str());
                                            wattrset(m_parent->get(), m_parent->getNormalColor());
                                            
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
}

void GraphChart::removePoint(_SharedPtr<GraphChartPoint> point){
    
    wattrset(m_parent->get(), m_parent->getNormalColor());
    
    std::vector<_SharedPtr<GraphChartPoint> >::iterator it = std::find(m_chartPoints.begin(), m_chartPoints.end(), point);
    if (it != m_chartPoints.end()){
        
        int pointX = point->m_X;
        int pointY = point->m_Y;
        
        for(int x = 0; x < m_width; x++){
            for(int y = 0; y < m_height; y++){
                if( (y % m_ySize+1) && (x % m_xSize)){
                    
                    if((x > m_xSize*pointX) && (x < (m_xSize*pointX)+m_xSize+1)){
                        if((y > m_ySize*pointY) && (y < (m_ySize*pointY)+m_ySize+1)){
                            
                            //mvwprintw(getParent()->get(), y, x,"%c", ' ');
                            
                            if(!m_showBars){
                                if(y == ((m_ySize*pointY)+m_ySize) || y < m_height-1)
                                    if( y > 0){
                                        mvwprintw(getParent()->get(), y, x,"%c", ' ');
                                    }
                                }
                            }
                            if(m_showBars){
                                if(y == ((m_ySize*pointY)+m_ySize) || y < m_height-1)
                                    mvwprintw(getParent()->get(), y, x,"%c", '=');
                            }
                            if(m_showBorder){
                                if( y == m_height-1)
                                    mvwprintw(getParent()->get(), y, x,"%c", '=');
                            }
                            if(!m_showBorder){
                                if( y == m_height-1)
                                    mvwprintw(getParent()->get(), y, x,"%c", ' ');
                            }
                        }
                    }
                }
            }
        }
    
    wrefresh(getParent()->get());
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


void GraphChart::refresh(){
    
    fill();
    
}


void GraphChart::handleKeys(int input){
    
    switch(input){
        case KEY_DOWN:
            removePoint(m_chartPoints.at(0));
            if(m_chartPoints.at(0)->m_Y < m_rows)
                m_chartPoints.at(0)->m_Y++;
            break;
            
        case KEY_UP:
            removePoint(m_chartPoints.at(0));
            if(m_chartPoints.at(0)->m_Y > 0)
                m_chartPoints.at(0)->m_Y--;
            break;
            
        case KEY_LEFT:
            removePoint(m_chartPoints.at(0));
            if(m_chartPoints.at(0)->m_X > 0)
                m_chartPoints.at(0)->m_X--;
            break;
            
        case KEY_RIGHT:
            removePoint(m_chartPoints.at(0));
            if(m_chartPoints.at(0)->m_X < m_cols)
                m_chartPoints.at(0)->m_X++;
            break;
        case '\n':
            m_chartPoints.at(0)->m_hidden = !m_chartPoints.at(0)->m_hidden;
            break;
    }
    
}


void GraphChart::randDirection(){
    int limit = 1000000;
    int lottery = rand() % limit;
    if(lottery > limit - m_chartPoints.size()*10000 ){
        int number = rand() % m_chartPoints.size();
        _SharedPtr<GraphChartPoint> point1 = m_chartPoints.at(number);
        if(point1){
            
            int direction = rand() % 9 + 1;
            
            
            switch(direction){
                case 1:
                    removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    if(point1->m_Y < m_rows-1)
                        point1->m_Y++;
                    break;
                case 2:
                    removePoint(point1);
                    if(point1->m_Y < m_rows-1)
                        point1->m_Y++;
                    break;
                case 3:
                    removePoint(point1);
                    if(point1->m_X < m_cols)
                        point1->m_X++;
                    if(point1->m_Y < m_rows-1)
                        point1->m_Y++;
                    break;
                case 4:
                    removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    break;
                case 5:
                    break;
                case 6:
                    removePoint(point1);
                    if(point1->m_X < m_cols)
                        point1->m_X++;
                    break;
                case 7:
                    removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
                case 8:
                    removePoint(point1);
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
                case 9:
                    removePoint(point1);
                    if(point1->m_X < m_cols)
                        point1->m_X++;
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
            }
            
        }
    }
}
