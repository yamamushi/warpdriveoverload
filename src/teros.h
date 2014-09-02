/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#ifndef TEROS_H
#define TEROS_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

#include "window.h"
#include "widget.h"
#include "tr1_wrapper.h"
#include "graphchart.h"

#define SCRHEIGHT 50
#define SCRWIDTH 78

#define PI 3.14159265358979323846264338327950288419716939937510f

using namespace std;

int roundnum (double);

double dist (double, double, double, double, double, double);
double findang (double, double);

string doubletostring (double);

class TerosScreen;


class TerosWindow
{
    
public:
    TerosWindow(_SharedPtr<TerosScreen> owner, int width, int height, int xpos, int ypos);
    
    // Begin Widget Functions
    void render(){}
    void refresh(){}
    void resize(int newx, int newy){}
    void handleKeys(int input){}
    
    // End Widget Functions
    

    // Teros Defaults
    
    void loadfromfile(std::string target);
    void loadfromvector (std::vector <char>, int);
    void modcontent (char, int, int);
    void tlrepos (int, int);
    void setcursor (int, bool);
    void setactivetext (int, string);
    void setfill (char);
    void setcursorchar (char);
    void setatxtid (char);
    void setcursorid (char);
    void settranspid (char);
    
    bool putcursor (int);
    
    std::string readcontent (int, int);
    char putfill ();
    char putcursorchar ();
    char putatxtid ();
    char putcursorid ();
    char puttranspid ();
    
    int putwidth ();
    int putheight ();
    int putxpos ();
    int putypos ();
    int getxpos(){return m_xpos;}
    int getypos(){return m_ypos;}
    int cursorcount ();
    int activetextcount ();
    
    string putactivetext (int);
    
private:
    std::vector <char> m_content;
    std::vector <bool> m_cursors;
    std::vector <string> m_activetext;
    
    std::vector<_SharedPtr<GraphChartPoint> > m_display;
    
    int m_width;
    int m_height;
    int m_tlposx;
    int m_tlposy;
    int m_xpos;
    int m_ypos;
    
    char m_cursorchar;
    char m_fill;
    char m_atxtid;
    char m_cursorid;
    char m_transparency;
    
    _SharedPtr<TerosScreen> m_screen;
    
};

class TerosScreen : public Widget
{
    
public:
    TerosScreen (_SharedPtr<ncursesWindow> owner, int xpos, int ypos, _SharedPtr<GraphChart> renderObject);
    
    
    // New Functions
    int getwidth(){return m_width;}
    int getheight(){return m_height;}
    
    void drawAt(int x, int y, std::string output);
    void drawAt(int x, int y, char c);
    
    int getxpos(){return m_xpos;}
    int getypos(){return m_ypos;}
    
    // End New Functions
    
    void buildscr ();
    void displayscr ();
    void addlayer ( _SharedPtr<TerosWindow> layer);
    void dellayer (int);
    void swaplayer (int, int);
    void modlayer (int,  _SharedPtr<TerosWindow> layer);
    
    
    
    int layercount ();
    
     _SharedPtr<TerosWindow> putlayer(int);
    
    
private:
    
    std::vector<_SharedPtr<GraphChartPoint> > m_display;
    std::vector< _SharedPtr<TerosWindow> > layers;
    
    int m_width;
    int m_height;
    int m_xpos;
    int m_ypos;
    
    _SharedPtr<GraphChart> m_graphChart;

};





#endif