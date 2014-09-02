//
//  terostest.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "terostest.h"
#include "terospolygon.h"
#include "terosR3.h"


void TerosTestInterface::init(){
    
    m_mainWindow->clearScreen();
    
    
    m_graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 0, 0));
    m_mainWindow->addWidget(m_graphController);
    m_graphController->hideBars();
    
    
    m_terosScreen = _SharedPtr<TerosScreen>(new TerosScreen(m_mainWindow, 0, 0, m_graphController));
    m_mainWindow->addWidget(m_terosScreen);
    
    m_terosWindow  =  _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth(), m_terosScreen->getheight(), 2, 2));
    
    m_terosScreen->addlayer(m_terosWindow);
    m_mainWindow->drawAt(3, 3, "Testing");
//    m_mainWindow->refresh();
//    l_testWindow->loadfromfile("example.txt");
    m_mainWindow->drawAt(4, 4, "Testing 2");
    
    m_terosObject = _SharedPtr<TerosR3Object>(new TerosR3Object);
    m_terosCam = _SharedPtr<TerosR3Cam>(new TerosR3Cam);
    
    yrotation = 0;
    zrotation = 0;
    xrotation = 0;
    
    m_rotspeed = 0.1;
    direction = 0;
    m_zoom = 10;
    m_rotate = true;

    TerosPolygon ls1;
	TerosPolygon ls2;
	TerosPolygon rs1;
	TerosPolygon rs2;
	TerosPolygon bs1;
	TerosPolygon bs2;
	TerosPolygon fs1;
	TerosPolygon fs2;
	TerosPolygon ts1;
	TerosPolygon ts2;
	TerosPolygon us1;
	TerosPolygon us2;
    
    
    ls1.modp (0, 2.5, -0.5, -0.5);
	ls1.modp (1, 3.5, -0.5, -0.5);
	ls1.modp (2, 3.5, -0.5, 0.5);
	ls1.setfill ('@');
    m_terosPolygons.push_back(ls1);

	ls2.modp (0, 3.5, -0.5, 0.5);
	ls2.modp (1, 2.5, -0.5, 0.5);
	ls2.modp (2, 2.5, -0.5, -0.5);
	ls2.setfill ('@');
    m_terosPolygons.push_back(ls2);

	rs1.modp (0, 2.5, 0.5, -0.5);
	rs1.modp (1, 3.5, 0.5, -0.5);
	rs1.modp (2, 3.5, 0.5, 0.5);
	rs1.setfill ('@');
    m_terosPolygons.push_back(rs1);

	rs2.modp (0, 3.5, 0.5, 0.5);
	rs2.modp (1, 2.5, 0.5, 0.5);
	rs2.modp (2, 2.5, 0.5, -0.5);
	rs2.setfill ('@');
    m_terosPolygons.push_back(rs2);

	bs1.modp (0, 3.5, -0.5, -0.5);
	bs1.modp (1, 3.5, 0.5, -0.5);
	bs1.modp (2, 3.5, 0.5, 0.5);
	bs1.setfill ('#');
    m_terosPolygons.push_back(bs1);

	bs2.modp (0, 3.5, 0.5, 0.5);
	bs2.modp (1, 3.5, -0.5, 0.5);
	bs2.modp (2, 3.5, -0.5, -0.5);
	bs2.setfill ('#');
    m_terosPolygons.push_back(bs2);

	fs1.modp (0, 2.5, -0.5, -0.5);
	fs1.modp (1, 2.5, 0.5, -0.5);
	fs1.modp (2, 2.5, 0.5, 0.5);
	fs1.setfill ('#');
    m_terosPolygons.push_back(fs1);

	fs2.modp (0, 2.5, 0.5, 0.5);
	fs2.modp (1, 2.5, -0.5, 0.5);
	fs2.modp (2, 2.5, -0.5, -0.5);
	fs2.setfill ('#');
    m_terosPolygons.push_back(fs2);

	ts1.modp (0, 3.5, -0.5, 0.5);
	ts1.modp (1, 3.5, 0.5, 0.5);
	ts1.modp (2, 2.5, 0.5, 0.5);
	ts1.setfill ('X');
    m_terosPolygons.push_back(ts1);

	ts2.modp (0, 2.5, 0.5, 0.5);
	ts2.modp (1, 2.5, -0.5, 0.5);
	ts2.modp (2, 3.5, -0.5, 0.5);
	ts2.setfill ('X');
    m_terosPolygons.push_back(ts2);

	us1.modp (0, 3.5, -0.5, -0.5);
	us1.modp (1, 3.5, 0.5, -0.5);
	us1.modp (2, 2.5, 0.5, -0.5);
	us1.setfill ('X');
    m_terosPolygons.push_back(us1);

	us2.modp (0, 2.5, 0.5, -0.5);
	us2.modp (1, 2.5, -0.5, -0.5);
	us2.modp (2, 3.5, -0.5, -0.5);
	us2.setfill ('X');
    m_terosPolygons.push_back(us2);

    
    for(int x = 0; x < m_terosPolygons.size(); x++){
        m_terosObject->addside(&m_terosPolygons.at(x));
    }
    
    m_terosCam->setviewsize(40,m_mainWindow->getX()-1);
    m_terosCam->addobject(m_terosObject.get());

    //m_terosCam->cambasisx;
    //m_terosCam->applyrotation(1, 1, 1, p1, p2, *m_terosObject);

    m_terosCam->drawobjects();
    
    m_terosObject->ctrscaleoff(0.00, 0.00, 0.00);
    //m_terosObject->rot('x', 1.0);

    m_terosScreen->displayscr();
    
    m_terosObject->saveobj("Test.tr3");

    
    m_initialized = true;
}


void TerosTestInterface::run(){

    //m_mainWindow->clearScreen();
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 4,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 5,  "        3D Rendering Test        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 6,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 7,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 8,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 9,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "R - Reset                        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 11, "x/X: Rotate on X axis            ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 12, "y/Y: Rotate on Y axis            ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 13, "z/Z: Rotate on Z axis            ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 14, "spacebar: Pause/Unpause rotation ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 15, "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 16, "                                 ");



    
    if(m_rotate){
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 8, "Rotation Speed is: " + std::to_string(m_rotspeed));

        if(direction == 0){
            m_terosObject->rot('x', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on X Axis");
        }
        else if(direction == 1){
            m_terosObject->rot('x', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse X Axis");
        }
        else if(direction == 2){
            m_terosObject->rot('y', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Y Axis");
        }
        else if(direction == 3){
            m_terosObject->rot('y', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse Y Axis");
        }
        else if(direction == 4){
            m_terosObject->rot('z', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Z Axis");
        }
        else if(direction == 5){
            m_terosObject->rot('z', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse Z Axis");
        }
    }
    else{
        m_graphController->refresh();
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotation Paused");
    }


    m_terosCam->drawobjects();

    m_terosWindow->loadfromvector(m_terosCam->putview(), m_mainWindow->getX()-1);

    m_terosScreen->displayscr();

    //m_mainWindow->clearScreen();
    
    m_mainWindow->render();

//    l_testWindow->loadfromfile("example.txt");
    
}


void TerosTestInterface::handleKeys(int input){
    switch(input){
            
        case 'x':
            direction = 0;
            m_terosObject->rot('x', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'X':
            direction = 1;
            m_terosObject->rot('x', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'y':
            direction = 2;
            m_terosObject->rot('y', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Y':
            direction = 3;
            m_terosObject->rot('y', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'z':
            direction = 4;
            m_terosObject->rot('z', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Z':
            direction = 5;
            m_terosObject->rot('z', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'R':
            direction = 0;
            m_terosObject->basisreset();
            m_terosCam->basisreset();
            m_rotate = false;
            break;
        case '-':
            if( m_rotspeed > 0)
                m_rotspeed -= 0.05;
            break;
        case '+':
            m_rotspeed += 0.05;
            break;
        case KEY_UP:
            m_terosCam->setzoomfactor(m_zoom + 5);
            m_zoom += 5;
            m_terosCam->drawobjects();
            break;
            
        case KEY_DOWN:
            m_terosCam->setzoomfactor(m_zoom - 5);
            m_zoom -= 5;
            m_terosCam->drawobjects();
            break;
        case ' ':
            m_rotate = !m_rotate;
            m_terosCam->drawobjects();
            break;
            
        default:
            m_mainWindow->handleKeys(input);
            break;
    }
    
    
}