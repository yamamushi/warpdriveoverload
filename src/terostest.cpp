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
//  l_testWindow->loadfromfile("example.txt");
    
    m_terosObject = _SharedPtr<TerosR3Object>(new TerosR3Object);
    m_terosCam = _SharedPtr<TerosR3Cam>(new TerosR3Cam);
    
    yrotation = 0;
    zrotation = 0;
    xrotation = 0;
    
    m_tool = false;
    
    xpos = 0.0;
    ypos = 0.0;
    zpos = 0.0;
    
    m_rotspeed = 0.1;
    direction = 0;
    m_zoom = 10;
    m_rotate = true;
    
    m_treasurechest = _SharedPtr<TreasureChest>(new TreasureChest); //Declaring an example TreasureChest object.
    
    
	/*Insert TreasureChest class commands, such as openlid, movechest, and rotchest here to view the effects of these functions.*/
    
    
	//primary.addlayer (&cartesian); //Adding the 3D output window to the screen.
    
	//camera.setviewsize (40, 78); //Setting the view size of the 3D camera object.
    
	m_terosCam->setcampos(-5.00, 3, 1.50); //Adjusting the camera position to center its view of the object.
    
	m_terosCam->addobject (m_treasurechest->putchest()); //Adding the instantaneous R3Object data for chest0 to the camera's field of vision.
    
	//m_terosCam->drawobjects (); //Calculating and drawing the 3D perspective to the camera's output vector.
    
	//m_terosWindow->loadfromvector(m_terosCam->putview (), 78); //Dumping the newly constructed camera image to the window.
    
	//m_terosWindow->displayscr (); //Outputting the screen contents to the terminal.
    


    /*
    for(int x = 0; x < m_terosPolygons.size(); x++){
        m_terosObject->addside(&m_terosPolygons.at(x));
    } */
    
    m_terosCam->setviewsize(40,m_mainWindow->getX()-40);
    //m_terosCam->addobject(m_terosObject.get());

    //m_terosCam->cambasisx;
    //m_terosCam->applyrotation(1, 1, 1, p1, p2, *m_terosObject);

    m_terosCam->drawobjects();
    
    m_terosObject->ctrscaleoff(0.00, 0.00, 0.00);
    //m_terosObject->rot('x', 1.0);
    m_terosCam->rotatecam('x', 3.14159);

    m_terosScreen->displayscr();
    
    m_terosObject->saveobj("Test.tr3");

    m_treasurechest->movechest(xpos, ypos, zpos);

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
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 11,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 12,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 13, " X Buffer: " + std::to_string(xpos) + " ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 14, " Y Buffer: " + std::to_string(ypos) + " ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 15, " Z Buffer: " + std::to_string(zpos) + " ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 16, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 17, "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 18, "t - Change Item to Rotate        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 19, "x/X: Rotate Camera on X axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 20, "y/Y: Rotate Camera on Y axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 21, "z/Z: Rotate Camera on Z axis     ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 22, "c/o: close/open chest ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 23, "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 24, "j/k/l (and caps): modify buffer  ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 25, "Enter: Commit Buffer             ");





    
    if(m_rotate){
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 8, "Rotation Speed is: " + std::to_string(m_rotspeed));

        if(direction == 0){
            //m_terosObject->rot('x', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on X Axis");
        }
        else if(direction == 1){
            //m_terosObject->rot('x', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse X Axis");
        }
        else if(direction == 2){
           // m_terosObject->rot('y', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Y Axis");
        }
        else if(direction == 3){
          //  m_terosObject->rot('y', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on reverse Y Axis");
        }
        else if(direction == 4){
          //  m_terosObject->rot('z', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-34), 7, "Rotating on Z Axis");
        }
        else if(direction == 5){
          //  m_terosObject->rot('z', -m_rotspeed);
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
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 9, "Chest Selected");
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
                m_treasurechest->rotchest('x', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'X':
            direction = 1;
            if(!m_tool)
                m_terosCam->rotatecam('x', -0.05);
            else
                m_treasurechest->rotchest('x', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'y':
            direction = 2;
            if(!m_tool)
                m_terosCam->rotatecam('y', 0.05);
            else
                m_treasurechest->rotchest('y', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Y':
            direction = 3;
            if(!m_tool)
                m_terosCam->rotatecam('y', -0.05);
            else
                m_treasurechest->rotchest('y', -0.05);
            m_terosCam->drawobjects();
            break;
        case 'z':
            direction = 4;
            if(!m_tool)
                m_terosCam->rotatecam('z', 0.05);
            else
                m_treasurechest->rotchest('z', 0.05);
            m_terosCam->drawobjects();
            break;
        case 'Z':
            direction = 5;
            if(!m_tool)
                m_terosCam->rotatecam('z', -0.05);
            else
                m_treasurechest->rotchest('z', -0.05);
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
            m_treasurechest->openlid(1);
            break;
        case 'c':
            m_treasurechest->openlid(0.0);
            break;
        case '\n':
            m_treasurechest->movechest(xpos, ypos, zpos);
            xpos = 0;
            ypos = 0;
            zpos = 0;
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