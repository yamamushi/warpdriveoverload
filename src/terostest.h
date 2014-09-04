//
//  terostest.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__terostest__
#define __warpdriveoverloaded__terostest__

#include "interface.h"
#include "menu.h"
#include "window.h"
#include "widget.h"
#include "connectionwidget.h"
#include "teros.h"
#include "graphchart.h"
#include "terosR3.h"
#include "terospolygon.h"
#include "TreasureChest.h"
#include "TRModel.h"
#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>


#include <ncurses.h>
#include <vector>

class TerosTestInterface : public Interface {
    
public:
    
    TerosTestInterface(_SharedPtr<Shell> owner) : Interface(owner){};
    
    void init();
    void run();
    void handleKeys(int input);
    
private:
    
    void doNothing(){};
    
    _SharedPtr<TerosScreen> m_terosScreen;
    _SharedPtr<GraphChart> m_graphController;
    _SharedPtr<TerosR3Cam> m_terosCam;
    _SharedPtr<TerosR3Object> m_terosObject;
    _SharedPtr<TerosWindow> m_terosWindow;
    _SharedPtr<TreasureChest> m_treasurechest;
    _SharedPtr<TRModel> m_trModel;

    void move(double speed, double distance);
    
    int yrotation;
    int xrotation;
    int zrotation;
    
    int direction;
    double m_zoom;
    bool m_rotate;
    double m_rotspeed;
    double xpos;
    double ypos;
    double zpos;
    
    bool m_tool;
    double m_camx, m_camy, m_camz;
    
    double m_camspeed;
    
    vmml::vector<4, double> m_camPosition;
    vmml::vector<4, double> m_camRotation;
};


#endif /* defined(__warpdriveoverloaded__terostest__) */
