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
    m_camspeed = 1.0;
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

    // We would add this widget to our parent window widget list
    // But we are rendering our graph controller by hand in our run() loop.
    // m_mainWindow->addWidget(m_graphController);
    
    // Turn off the grid bars on the graph controller widget
    m_graphController->hideBars();
    
    
    // Create a new screen with position 0,0
    m_terosScreen = _SharedPtr<TerosScreen>(new TerosScreen(m_mainWindow, 0, 0, m_graphController));
    
    // Add our teros screen (Which handles our 3d object rendering) to the widget list of our parent.
    m_widgetManager->addWidget(m_terosScreen);
    
    
    // Now we'll create a window for rendering our objects to.
    // Create a new Teros Window with position 2,2
    m_terosWindow = _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth()-1, m_terosScreen->getheight()/2, 1, 0));
    
    // Create a new Teros Window with a position below our first
    m_terosWindow2 = _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth()-1, m_terosScreen->getheight()/2, 1, m_terosScreen->getheight()/2));
    
    // Attach these windows as a layer to our screen
    m_terosScreen->addlayer(m_terosWindow);
    m_terosScreen->addlayer(m_terosWindow2);

    
    // Create a Model and set it as our object
    m_trModel = _SharedPtr<SphereModel>(new SphereModel(2));
    m_terosObject = m_trModel->getModel();
    
    // Create a new camera
    m_terosCam1 = _SharedPtr<TerosCam>(new TerosCam);
    m_terosCam2 = _SharedPtr<TerosCam>(new TerosCam);
    
    m_terosCam = m_terosCam1;
    
    // Add our terosObject from its pointer
    m_terosCam1->addobject(m_terosObject.get());
    m_terosCam2->addobject(m_terosObject.get());

    
    // Set our camera position
    m_terosCam1->setcampos(m_camx, m_camy, m_camz);
    m_terosCam2->setcampos(-m_camx, -m_camy, m_camz);
    m_terosCam2->rotatecam('y', PI);
    m_terosCam2->rotatecam('x', PI);


    // Adjust the view size for our Camera Render (this means we can fit multiple views in one window
    m_terosCam1->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-41);
    m_terosCam2->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-41);

    
    // Draw our objects, this doesn't mean render them, this means lay our 3d image into a 2d space and buffer it.
    m_terosCam1->drawobjects();
    m_terosCam2->drawobjects();

    // Apply a zoom factor to our camera
    m_terosCam1->setzoomfactor(m_zoom);
    m_terosCam2->setzoomfactor(m_zoom);


    // Tell our Window to load the view that our camera provides
    m_terosWindow->loadfromvector(m_terosCam1->putview(), m_mainWindow->getX()-41);
    m_terosWindow2->loadfromvector(m_terosCam2->putview(), m_mainWindow->getX()-41);

    // Display the screen
    // This will cycle through all of the available windows and render them
    // Which gives us the ability to have two windows...
    m_terosScreen->displayscr();
    draw();

    // Finally we give the all clear that our interface has been initialized.
    m_initialized = true;
    
}




void TerosTestInterface::move(double speedws, double distance){
 
    m_terosCam->moveForward( speedws, distance);
    
}



void TerosTestInterface::run(){
    
    //m_mainWindow->refresh();
    //redrawwin(m_mainWindow->get());


    m_terosCam1->drawobjects();
    m_terosCam2->drawobjects();

    m_terosWindow->loadfromvector(m_terosCam1->putview(), m_mainWindow->getX()-41);
    m_terosWindow2->loadfromvector(m_terosCam2->putview(), m_mainWindow->getX()-41);

    m_terosScreen->displayscr();
    
    m_graphController->render();
    
    draw();
    refresh();

}



void TerosTestInterface::draw(){
    
    m_mainWindow->drawAt(3, 1,"Camera 1");
    m_mainWindow->drawAt(3, (m_mainWindow->getY()/2),"Camera 2");
    
    m_mainWindow->drawAt((m_mainWindow->getX()-10), 1, "           ");
    std::string fpscount(std::to_string(m_owner->getfps()) + " fps");
    m_mainWindow->drawAt((m_mainWindow->getX()-2)-(int)fpscount.length(), 1, fpscount);
    
    m_mainWindow->drawAt((m_mainWindow->getX()-8), 2, "        ");
    std::string termSize( "Size: " + std::to_string(m_owner->getWidth()) + " x " + std::to_string(m_owner->getHeight()) );
    m_mainWindow->drawAt((m_mainWindow->getX()-(int)termSize.length()-2), 2, termSize);
    
    
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 5,  "        3D Rendering Test        ");
    
    if(m_objectSelected){
        
        m_mainWindow->drawAt((m_mainWindow->getX()-40), 7, "Camera 2 Selected");
        
    }
    else{
        
        m_mainWindow->drawAt((m_mainWindow->getX()-40), 7, "Camera 1 Selected");
        
    }
    
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 8,  "                                 ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 9,  "                                 ");

    if(m_rotate){
        
        
        if(m_direction == 0){
            m_terosObject->rot('x', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on X Axis");
        }
        else if(m_direction == 1){
            m_terosObject->rot('x', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on reverse X Axis");
        }
        else if(m_direction == 2){
            m_terosObject->rot('y', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on Y Axis");
        }
        else if(m_direction == 3){
            m_terosObject->rot('y', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on reverse Y Axis");
        }
        else if(m_direction == 4){
            m_terosObject->rot('z', m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on Z Axis");
        }
        else if(m_direction == 5){
            m_terosObject->rot('z', -m_rotspeed);
            m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotating on reverse Z Axis");
        }
    }
    else{
        m_mainWindow->drawAt((m_mainWindow->getX()-40), 9, "Rotation Paused");
    }
    
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 11,  "Camera Zoom is: " + std::to_string(m_zoom));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 12,  "Camera Speed is: " + std::to_string(m_camspeed));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 14, "PositionX: " + std::to_string(m_terosCam->putcamx()));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 15, "PositionY: " + std::to_string(m_terosCam->putcamy()));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 16, "PositionZ: " + std::to_string(m_terosCam->putcamz()));
    
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 18, "Yaw   : " + std::to_string(m_terosCam->getAngleX().x()) + ", " + std::to_string(m_terosCam->getAngleX().y()) + ", " + std::to_string(m_terosCam->getAngleX().z()));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 19, "Roll  : " + std::to_string(m_terosCam->getAngleY().x()) + ", " + std::to_string(m_terosCam->getAngleY().y()) + ", " + std::to_string(m_terosCam->getAngleY().z()));
    m_mainWindow->drawAt((m_mainWindow->getX()-40), 20, "Pitch : " + std::to_string(m_terosCam->getAngleZ().x()) + ", " + std::to_string(m_terosCam->getAngleZ().y()) + ", " + std::to_string(m_terosCam->getAngleZ().z()));


    
    
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-11), "t - Change Selected Camera       ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-10), "x/y/z: Sphere Rotation           ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-9), "w/a/s/d: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-8), "j/i/k/l: Move Camera             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-7), "Up/Down: Zoom in/out             ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-6), "+/- : Modify camera speed        ");
    m_mainWindow->drawAt((m_mainWindow->getX()-40), (m_mainWindow->getY()-5), "Spacebar: Pause Rotation         ");
    
    


    m_mainWindow->drawLine((m_mainWindow->getX()-42), 1, (m_mainWindow->getX()-42), (m_mainWindow->getY()-1), "|", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    m_mainWindow->drawLine(1, (m_mainWindow->getY()/2)-1, (m_mainWindow->getX()-43), (m_mainWindow->getY()/2)-1, "-", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    
}


void TerosTestInterface::resize(){

    m_terosCam1->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-41);
    m_terosCam2->setviewsize(m_mainWindow->getY()/2,m_mainWindow->getX()-41);
    m_terosScreen->resize(m_mainWindow->getX()-44, m_mainWindow->getY());
    m_terosWindow2->setypos(m_terosScreen->getheight()/2);
}


void TerosTestInterface::handleKeys(int input){
    switch(input){
            
        case 'x':
            m_direction = 0;
            run();
            break;
        case 'X':
            m_direction = 1;
            run();
            break;
        case 'y':
            m_direction = 2;
            run();
            break;
        case 'Y':
            m_direction = 3;
            run();
            break;
        case 'z':
            m_direction = 4;
            run();
            break;
        case 'Z':
            m_direction = 5;
            run();
            break;
            
        case 't':
            if(!m_objectSelected){
                m_terosCam = m_terosCam2;
                m_objectSelected = true;
                run();
            }else{
                m_terosCam = m_terosCam1;
                m_objectSelected = false;
                run();
            }
            
            break;

        case 'w':
            move(m_camspeed, 0.05);
            run();
            break;
            
        case 's':
            move(m_camspeed, -0.05);
            run();
            break;
            
        case 'a':
            m_terosCam->rotatecam('z', 0.05);
            run();
            break;
        case 'd':
            m_terosCam->rotatecam('z', -0.05);
            run();
            break;
            
            // THIS IS BACKWARDS ON PURPOSE
        case 'k':
            m_terosCam->rotatecam('y', 0.05);
            run();
            break;
        case 'i':
            m_terosCam->rotatecam('y', -0.05);
            run();
            break;
            
        case 'j':
            m_terosCam->rotatecam('x', 0.05);
            run();
            break;
        case 'l':
            m_terosCam->rotatecam('x', -0.05);
            run();
            break;
        
            
        case '-':
            if( m_camspeed > 0.0)
                m_camspeed -= 0.01;
            run();
            break;
        case '+':
            m_camspeed += 0.01;
            run();
            break;
            
            
        case KEY_UP:
            m_zoom += 0.5;
            m_terosCam->setzoomfactor(m_zoom);
            //m_terosCam->drawobjects();
            run();
            break;
            
        case KEY_DOWN:
            m_zoom -= 0.5;
            m_terosCam->setzoomfactor(m_zoom);
            //m_terosCam->drawobjects();
            run();
            break;
        case ' ':
            m_rotate = !m_rotate;
            //m_terosCam->drawobjects();
            run();
            break;
            
        default:
            m_widgetManager->handleKeys(input);
            run();
            break;
    }
    
    
}