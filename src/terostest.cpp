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

#include "logger.h"

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
    m_camspeed = 0.05;
    direction = 5;
    m_zoom = 9.5;
    m_rotate = true;
    
    m_camx = -2.0;
    m_camy = 1.0;
    //m_camx = 0.0;
    //m_camy = 0.0;
    m_camz = 0.0;
    
    
    
    // Create our identity matrices
    
    
    //m_treasurechest = _SharedPtr<TreasureChest>(new TreasureChest); //Declaring an example TreasureChest object.
    
	//m_terosCam->setcampos(-5.00, 3, 1.50); //Adjusting the camera position to center its view of the object.
    // MEASURE IN RADIANS
    //m_terosCam->rotatecam('x', 3.1415926535897932384626433); // Rotate our camera as close to pi as I can remember right now
    m_terosCam->setcampos(m_camx, m_camy, m_camz);
    //m_terosCam->rotatecam('z', -0.7);
    
    m_camPosition.set(m_camx, m_camy, m_camz, 1.0);
    m_camRotation.set(m_terosCam->getAngleX(), m_terosCam->getAngleY(), m_terosCam->getAngleZ(), 0.0f);
    
    

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




void TerosTestInterface::move(double speedws, double distance){
 
    logger logwatch("log.txt", 0);

    //vmml::matrix<4, 4, double> matrixRot = vmml::matrix<4, 4, double> rotate_x(m_camRotation->PositionX);
    vmml::matrix<4, 4, double> identity;
    identity.set_row(0,  vmml::vector<4, double>(1.0, 0.0, 0.0, 0.0));
    identity.set_row(1,  vmml::vector<4, double>(0.0, 1.0, 0.0, 0.0));
    identity.set_row(2,  vmml::vector<4, double>(0.0, 0.0, 1.0, 0.0));
    identity.set_row(3,  vmml::vector<4, double>(0.0, 0.0, 0.0, 1.0));

    
    vmml::matrix<4, 4, double> matrixRot_X = identity;

    matrixRot_X = matrixRot_X.rotate_x(m_camRotation.x());
    
    vmml::matrix<4, 4, double> matrixRot_Y = identity;
    matrixRot_Y = matrixRot_Y.rotate_y(m_camRotation.y());
    
    vmml::matrix<4, 4, double> matrixRot_Z = identity;
    matrixRot_Z = matrixRot_Z.rotate_z(m_camRotation.z());

    vmml::matrix<4, 4, double> matrixRot_final = matrixRot_X * matrixRot_Y * matrixRot_Z;

    vmml::vector<4, double> translation = matrixRot_final * vmml::vector<4, double>(distance, 0.0, 0.0, 0.0);
    
    translation = translation * m_camspeed;
    
    m_camPosition = m_camPosition + translation;
    
    m_camx = m_camPosition.x();
    m_camy = m_camPosition.y();
    m_camz = m_camPosition.z();

    m_terosCam->setcampos(m_camx, m_camy, m_camz);
    
    m_camPosition.set(m_camx, m_camy, m_camz, 1.0f);
    m_camRotation.set(m_terosCam->getAngleX(), m_terosCam->getAngleY(), m_terosCam->getAngleZ(), 1.0f);
    
    logwatch.logToFile("Cam Position: " + std::to_string(m_camx) + " " + std::to_string(m_camy) + " " + std::to_string(m_camz), 0);
    logwatch.logToFile("Move completed", 0);
    
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
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 19, "x/y/z: Sphere Rotation           ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 20, "w/a/s/d: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 21, "j/i/k/l: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 22, "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 23, "+/- : Modify rotation speed      ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 24, "Spacsebar: Pause Rotation         ");
    m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "Camera Zoom is: " + std::to_string(m_zoom));




    
    if(m_rotate){
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 8, "Camera Speed is: " + std::to_string(m_camspeed));

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
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 10, "PositionX: " + std::to_string(m_camx));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 11, "PositionY: " + std::to_string(m_camy));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 12, "PositionZ: " + std::to_string(m_camz));
        
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 13, "Angle X: " + std::to_string(m_terosCam->getAngleX()));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 14, "Angle Y: " + std::to_string(m_terosCam->getAngleY()));
        m_mainWindow->drawAt((m_mainWindow->getX()-34), 15, "Angle Z: " + std::to_string(m_terosCam->getAngleZ()));

    }

    m_graphController->refresh();

    m_terosCam->setcampos(m_camx, m_camy, m_camz);

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

        case 'w':
            //m_camx += 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            move(m_camspeed, 0.6);
            break;
            
        case 's':
            // m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            move(m_camspeed, -0.6);
            break;
            
        case 'a':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('z', 0.05);
            break;
        case 'd':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('z', -0.05);
            break;
            
            // THIS IS BACKWARDS ON PURPOSE
        case 'k':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('y', 0.05);
            break;
        case 'i':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('y', -0.05);
            break;
            
        case 'j':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('x', 0.05);
            break;
        case 'l':
            //m_camx -= 0.05;
            //m_terosCam->setcampos(m_camx, m_camy, m_camz);
            m_terosCam->rotatecam('x', -0.05);
            break;
        
            
        case '-':
            if( m_camspeed > 0.0)
                m_camspeed -= 0.01;
            break;
        case '+':
            m_camspeed += 0.01;
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