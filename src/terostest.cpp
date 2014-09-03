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

#include "SphereModel.h"


void TerosTestInterface::init(){
    
    m_mainWindow->clearScreen();
    
    
    m_graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 0, 0));
    m_mainWindow->addWidget(m_graphController);
    m_graphController->hideBars();
    
    
    m_terosScreen = _SharedPtr<TerosScreen>(new TerosScreen(m_mainWindow, 0, 0, m_graphController));
    m_mainWindow->addWidget(m_terosScreen);
    
    m_terosWindow  =  _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth(), m_terosScreen->getheight(), 2, 2));
    
    m_terosScreen->addlayer(m_terosWindow);
//  l_testWindow->loadfromfile("example.txt");
    
    m_trModel = _SharedPtr<SphereModel>(new SphereModel);
    m_terosObject = m_trModel->getModel();
    m_terosCam = _SharedPtr<TerosR3Cam>(new TerosR3Cam);
    
    
    yrotation = 0;
    zrotation = 0;
    xrotation = 0;
    
    m_tool = true;
    
    xpos = 0.0;
    ypos = 0.0;
    zpos = 0.0;
    
    m_rotspeed = 0.1;
    direction = 5;
    m_zoom = 9.5;
    m_rotate = true;
    
    //m_treasurechest = _SharedPtr<TreasureChest>(new TreasureChest); //Declaring an example TreasureChest object.
    
	//m_terosCam->setcampos(-5.00, 3, 1.50); //Adjusting the camera position to center its view of the object.
    m_terosCam->rotatecam('x', 3.1415926535897932384626433); // Rotate our camera as close to pi as I can remember right now
    m_terosCam->setcampos(-2, 1, 0);
    m_terosCam->rotatecam('z', -0.7);
    //m_terosCam->rotatecam('x', -0.2);

    //m_terosObject->rot('z', -1);
    //m_terosObject->rot('x', 1.0);
    
    //m_terosObject->rot('y', -1.0);


	//m_terosCam->addobject (_treasurechest->putchest()); //Adding the instantaneous R3Object data for chest0 to the camera's field of vision.
    m_terosCam->addobject(m_terosObject.get());
    // Adjust the view size for our Camera Render (this means we can fit multiple views in one window
    m_terosCam->setviewsize(m_mainWindow->getY()-1,m_mainWindow->getX()-40);
    
    // Draw our objects, this doesn't mean render them, this means lay our 3d image into a 2d space and buffer it.
    m_terosCam->drawobjects();
    
    
   // m_terosObject->ctrscaleoff(m_terosObject->centerx(), m_terosObject->centery(), m_terosObject->centerz());  // Unlock an Object
    //m_terosCam->rotatecam('x', 3.14159);
    m_terosCam->setzoomfactor(m_zoom);

    
    m_terosScreen->displayscr();  // Render our screen our to our GraphController
    
    //m_terosObject->saveobj("Test.tr3");
    //m_treasurechest->movechest(xpos, ypos, zpos);

    // Finally we give the all clear that our interface has been initialized.
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
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 11, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 12, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 16, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 17, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 18, "t - Change Item to Rotate        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 19, "x/X: Rotate Camera on X axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 20, "y/Y: Rotate Camera on Y axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 21, "z/Z: Rotate Camera on Z axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 22, "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 23, "+/- : Modify rotation speed      ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 24, "Spacebar: Pause Rotation         ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "Camera Zoom is: " + std::to_string(m_zoom));




    
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
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotation Paused");
    }
    
    if(!m_tool){
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 9, "Camera Selected");
    }
    else{
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 9, "Object Selected");
    }

    m_graphController->refresh();

    m_terosCam->drawobjects();

    m_terosWindow->loadfromvector(m_terosCam->putview(), m_mainWindow->getX()-40);

    m_terosScreen->displayscr();

    //m_mainWindow->clearScreen();
    
    //m_mainWindow->render();

//    l_testWindow->loadfromfile("example.txt");
    
}


void TerosTestInterface::handleKeys(int input){
    switch(input){
            
        case 'x':
            direction = 0;
            if(!m_tool)
                m_terosCam->rotatecam('x', 0.05);
            else
                m_terosObject->rot('x', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'X':
            direction = 1;
            if(!m_tool)
                m_terosCam->rotatecam('x', -0.05);
            else
                m_terosObject->rot('x', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'y':
            direction = 2;
            if(!m_tool)
                m_terosCam->rotatecam('y', 0.05);
            else
                m_terosObject->rot('y', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Y':
            direction = 3;
            if(!m_tool)
                m_terosCam->rotatecam('y', -0.05);
            else
                m_terosObject->rot('y', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'z':
            direction = 4;
            if(!m_tool)
                m_terosCam->rotatecam('z', 0.05);
            else
                m_terosObject->rot('z', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Z':
            direction = 5;
            if(!m_tool)
                m_terosCam->rotatecam('z', -0.05);
            else
                m_terosObject->rot('z', -0.05);
            m_terosCam->drawobjects();
            break;
        case 't':
            m_tool = !m_tool;
            break;

        case 'j':
            xpos -= 0.5;
            break;
        case 'k':
            ypos -= 0.5;
            break;
        case 'l':
            zpos -= 0.5;
            break;
            
        case 'J':
            xpos += 0.5;
            break;
        case 'K':
            ypos += 0.5;
            break;
        case 'L':
            zpos += 0.5;
            break;
        case '-':
            if( m_rotspeed > 0)
                m_rotspeed -= 0.05;
            break;
        case '+':
            m_rotspeed += 0.05;
            break;
        case 'o':
           // m_treasurechest->openlid(1);
            break;
        case 'c':
            //m_treasurechest->openlid(0.0);
            break;
        case '\n':
            //m_treasurechest->movechest(xpos, ypos, zpos);
            xpos = 0;
            ypos = 0;
            zpos = 0;
            break;
            
        case KEY_UP:
            m_terosCam->setzoomfactor(m_zoom);
            m_zoom += 0.5;
            m_terosCam->drawobjects();
            break;
            
        case KEY_DOWN:
            m_terosCam->setzoomfactor(m_zoom);
            m_zoom -= 0.5;
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