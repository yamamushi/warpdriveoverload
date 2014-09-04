//
//  terostest.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "terostest.h"
#include "terospolygon.h"
#include "logger.h"

#include "SphereModel.h"


void TerosTestInterface::init(){

    // Our variable initialization
    m_rotspeed = 0.1;
    m_camspeed = 0.05;
    m_direction = 5;
    m_zoom = 5.0;
    m_rotate = true;
    m_objectSelected = false;
    
    // Set our camera position
    m_camx = -2.0;
    m_camy = 1.0;
    m_camz = 0.0;
    
    // Clear anything that was on the parent window
    m_mainWindow->clearScreen();
    
    
    // Set up our Widgets First

    // Create a graph controller widget which will take the smallest grid size by default.
    m_graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 0, 0));

    // Add this widget to our parent window widget list
    // We would do this but we are rendering our graph controller by hand
    // m_mainWindow->addWidget(m_graphController);
    
    // Turn off the grid bars on the graph controller widget
    m_graphController->hideBars();
    
    
    // Create a new screen with position 0,0
    m_terosScreen = _SharedPtr<TerosScreen>(new TerosScreen(m_mainWindow, 0, 0, m_graphController));
    
    // Add our teros screen (Which handles our 3d object rendering) to the widget list of our parent.
    m_mainWindow->addWidget(m_terosScreen);
    
    
    // Now we'll create a window for rendering our objects to.
    // Create a new Teros Window with position 2,2
    m_terosWindow = _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth(), m_terosScreen->getheight()/2, 2, 0));
    
    // Create a new Teros Window with a position below our first
    m_terosWindow2 = _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth(), m_terosScreen->getheight()/2, 2, m_terosScreen->getheight()/2));
    
    // Attach these windows as a layer to our screen
    m_terosScreen->addlayer(m_terosWindow);
    m_terosScreen->addlayer(m_terosWindow2);

    
    // Create a Model and set it as our object
    m_trModel = _SharedPtr<SphereModel>(new SphereModel);
    m_terosObject = m_trModel->getModel();
    
    // Create a new camera
    m_terosCam = _SharedPtr<TerosCam>(new TerosCam);
    m_terosCam2 = _SharedPtr<TerosCam>(new TerosCam);

    
    // Add our terosObject from its pointer
    m_terosCam->addobject(m_terosObject.get());
    m_terosCam2->addobject(m_terosObject.get());

    
    // Set our camera position
    m_terosCam->setcampos(m_camx, m_camy, m_camz);
    m_terosCam2->setcampos(-m_camx, -m_camy, m_camz);
    m_terosCam2->rotatecam('y', PI);
    m_terosCam2->rotatecam('x', PI);


    // Adjust the view size for our Camera Render (this means we can fit multiple views in one window
    m_terosCam->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-40);
    m_terosCam2->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-40);

    
    // Draw our objects, this doesn't mean render them, this means lay our 3d image into a 2d space and buffer it.
    m_terosCam->drawobjects();
    m_terosCam2->drawobjects();

    // Apply a zoom factor to our camera
    m_terosCam->setzoomfactor(m_zoom);
    m_terosCam2->setzoomfactor(m_zoom);


    // Tell our Window to load the view that our camera provides
    m_terosWindow->loadfromvector(m_terosCam->putview(), m_mainWindow->getX()-40);
    m_terosWindow2->loadfromvector(m_terosCam2->putview(), m_mainWindow->getX()-40);

    // Display the screen
    // This will cycle through all of the available windows and render them
    // Which gives us the ability to have two windows...
    m_terosScreen->displayscr();

    // Finally we give the all clear that our interface has been initialized.
    m_initialized = true;
    
}




void TerosTestInterface::move(double speedws, double distance){
 
    m_terosCam->moveDir('x', speedws, distance);
    
}



void TerosTestInterface::run(){

    m_mainWindow->drawAt((m_mainWindow->getX()-34), 4,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 5,  "        3D Rendering Test        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 6,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 7,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 8,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 9,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 11, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 12, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 16, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 17, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 18, "t - Change Item to Rotate        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 19, "x/y/z: Sphere Rotation           ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 20, "w/a/s/d: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 21, "j/i/k/l: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 22, "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 23, "+/- : Modify camera speed        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 24, "Spacsebar: Pause Rotation         ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "Camera Zoom is: " + std::to_string(m_zoom));




    
    if(m_rotate){
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 9, "Camera Speed is: " + std::to_string(m_camspeed));

        if(m_direction == 0){
            m_terosObject->rot('x', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on X Axis");
        }
        else if(m_direction == 1){
            m_terosObject->rot('x', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse X Axis");
        }
        else if(m_direction == 2){
            m_terosObject->rot('y', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Y Axis");
        }
        else if(m_direction == 3){
            m_terosObject->rot('y', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse Y Axis");
        }
        else if(m_direction == 4){
            m_terosObject->rot('z', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Z Axis");
        }
        else if(m_direction == 5){
            m_terosObject->rot('z', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse Z Axis");
        }
    }
    else{
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotation Paused");
    }
    
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 8, "Camera Zoom is: " + std::to_string(m_zoom));
    

        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "PositionX: " + std::to_string(m_camx));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 11, "PositionY: " + std::to_string(m_camy));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 12, "PositionZ: " + std::to_string(m_camz));
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 13, "Angle X: " + std::to_string(m_terosCam->getAngleX()));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 14, "Angle Y: " + std::to_string(m_terosCam->getAngleY()));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 15, "Angle Z: " + std::to_string(m_terosCam->getAngleZ()));



    m_graphController->refresh();

    m_terosCam->drawobjects();
    m_terosCam2->drawobjects();

    m_terosWindow->loadfromvector(m_terosCam->putview(), m_mainWindow->getX()-40);
    m_terosWindow2->loadfromvector(m_terosCam2->putview(), m_mainWindow->getX()-40);

    m_terosScreen->displayscr();
    
    m_graphController->render();
    
    m_mainWindow->drawAt(3, 1,"Camera 1");
    m_mainWindow->drawAt(3, (m_mainWindow->getY()/2),"Camera 2");
    
    
    
}


void TerosTestInterface::handleKeys(int input){
    switch(input){
            
        case 'x':
            m_direction = 0;
            if(!m_objectSelected)
                m_terosCam->rotatecam('x', 0.05);
            else
                m_terosObject->rot('x', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'X':
            m_direction = 1;
            if(!m_objectSelected)
                m_terosCam->rotatecam('x', -0.05);
            else
                m_terosObject->rot('x', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'y':
            m_direction = 2;
            if(!m_objectSelected)
                m_terosCam->rotatecam('y', 0.05);
            else
                m_terosObject->rot('y', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Y':
            m_direction = 3;
            if(!m_objectSelected)
                m_terosCam->rotatecam('y', -0.05);
            else
                m_terosObject->rot('y', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'z':
            m_direction = 4;
            if(!m_objectSelected)
                m_terosCam->rotatecam('z', 0.05);
            else
                m_terosObject->rot('z', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Z':
            m_direction = 5;
            if(!m_objectSelected)
                m_terosCam->rotatecam('z', -0.05);
            else
                m_terosObject->rot('z', -0.05);
            m_terosCam->drawobjects();
            break;
        case 't':
            m_objectSelected = !m_objectSelected;
            break;

        case 'w':
            move(m_camspeed, 0.6);
            break;
            
        case 's':
            move(m_camspeed, -0.6);
            break;
            
        case 'a':
            m_terosCam->rotatecam('z', 0.05);
            break;
        case 'd':
            m_terosCam->rotatecam('z', -0.05);
            break;
            
            // THIS IS BACKWARDS ON PURPOSE
        case 'k':
            m_terosCam->rotatecam('y', 0.05);
            break;
        case 'i':
            m_terosCam->rotatecam('y', -0.05);
            break;
            
        case 'j':
            m_terosCam->rotatecam('x', 0.05);
            break;
        case 'l':
            m_terosCam->rotatecam('x', -0.05);
            break;
        
            
        case '-':
            if( m_camspeed > 0.0)
                m_camspeed -= 0.01;
            break;
        case '+':
            m_camspeed += 0.01;
            break;
            
            
        case KEY_UP:
            m_zoom += 0.5;
            m_terosCam->setzoomfactor(m_zoom);
            m_terosCam->drawobjects();
            break;
            
        case KEY_DOWN:
            m_zoom -= 0.5;
            m_terosCam->setzoomfactor(m_zoom);
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