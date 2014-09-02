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

#define SCRHEIGHT 50
#define SCRWIDTH 78

#define PI 3.14159265358979323846264338327950288419716939937510f

using namespace std;

int roundnum (double);

double dist (double, double, double, double, double, double);
double findang (double, double);

string doubletostring (double);

class TerosWindow : public Widget
{
    
public:
    TerosWindow(_SharedPtr<ncursesWindow> owner, int xpos, int ypos);
    
    // Begin Widget Functions
    void render(){}
    void refresh(){}
    void resize(int newx, int newy){}
    void handleKeys(int input){}
    
    // End Widget Functions
    
    void loadfromfile (string);
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
    
    char readcontent (int, int);
    char putfill ();
    char putcursorchar ();
    char putatxtid ();
    char putcursorid ();
    char puttranspid ();
    
    int putwidth ();
    int putheight ();
    int putxpos ();
    int putypos ();
    int cursorcount ();
    int activetextcount ();
    
    string putactivetext (int);
    
private:
    std::vector <char> content;
    std::vector <bool> cursors;
    std::vector <string> activetext;
    
    int width;
    int height;
    int tlposx;
    int tlposy;
    
    char cursorchar;
    char fill;
    char atxtid;
    char cursorid;
    char transparency;
    
};

class TerosScreen
{
private:
    char display [SCRWIDTH][SCRHEIGHT];
    
    std::vector <TerosWindow *> layers;
    
public:
    TerosScreen ();
    
    void clrscr ();
    void buildscr ();
    void displayscr ();
    void addlayer (TerosWindow *);
    void dellayer (int);
    void swaplayer (int, int);
    void modlayer (int, TerosWindow *);
    
    int layercount ();
    
    TerosWindow * putlayer (int);
};





#endif