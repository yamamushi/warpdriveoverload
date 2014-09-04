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
#include "teroscam.h"
#include "terosobject.h"
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
    _SharedPtr<TerosCam> m_terosCam;
    _SharedPtr<TerosCam> m_terosCam2;

    _SharedPtr<TerosObject> m_terosObject;
    
    _SharedPtr<TerosWindow> m_terosWindow;
    _SharedPtr<TerosWindow> m_terosWindow2;

    _SharedPtr<TreasureChest> m_treasurechest;
    _SharedPtr<TRModel> m_trModel;

    void move(double speed, double distance);
    
    int m_direction;
    
    double m_zoom;
    bool m_rotate;
    bool m_objectSelected;
    double m_rotspeed;
    
    double m_camx, m_camy, m_camz;
    double m_camspeed;
    
    

};


#endif /* defined(__warpdriveoverloaded__terostest__) */
