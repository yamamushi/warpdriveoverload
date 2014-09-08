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
#include "wintypes/window.h"

#include "widgets/widget.h"
#include "widgets/connectionwidget.h"
#include "teros/teros.h"
#include "widgets/graphchart.h"
#include "teros/teroscam.h"
#include "teros/terosobject.h"
#include "teros/terospolygon.h"
#include "terosmodels/TRModel.h"
#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

#include "util/Clock.h"
#include "engine/Hermes.h"

#include <vector>

class TerosTestInterface : public Interface {
    
public:
    
    TerosTestInterface(_SharedPtr<Shell> owner) : Interface(owner){};
    
    void init();
    void run();
    void handleKeys(int input);

protected:
    
    void resizeComponents();
    
private:
    
    void doNothing(){};
    
    _SharedPtr<TerosScreen> m_terosScreen;
    _SharedPtr<GraphChart> m_graphController;
    
    _SharedPtr<TerosCam> m_terosCam;

    _SharedPtr<TerosCam> m_terosCam1;
    _SharedPtr<TerosCam> m_terosCam2;

    _SharedPtr<TerosObject> m_terosObject;
    
    _SharedPtr<TerosWindow> m_terosWindow;
    _SharedPtr<TerosWindow> m_terosWindow2;

    _SharedPtr<TRModel> m_trModel;

    void move(double speed, double distance);
    void draw();
    
    int m_direction;
    
    double m_zoom;
    bool m_rotate;
    bool m_objectSelected;
    double m_rotspeed;
    
    double m_camx, m_camy, m_camz;
    double m_camspeed;
    
    
    void update();
    
    Interval m_timeKeeper;
    int m_ticks;
    int m_secondsElapsed;
    
    double Distance(double dX0, double dY0, double dX1, double dY1);

};


#endif /* defined(__warpdriveoverloaded__terostest__) */
