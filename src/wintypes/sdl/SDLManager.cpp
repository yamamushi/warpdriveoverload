#include "SDLManager.h"
#ifdef _WARPDRIVE_SDLCLIENT_

#include "util/version.h"
#include "BitmapFont.h"
#include <iostream>
#include <SDL/SDL.h>
#include "util/asciicodes.h"
#include "util/Clock.h"


bool SDLManager::start(){

    std::cout << "SDL Mode Started" << std::endl;

    m_width = 640;
    m_height = 480;

    m_frameCounter = 0;
    m_maxfps = 60;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error:" <<  SDL_GetError() << std::endl;
        return false;
    }
    else{
        std::string WinTitle("Warp Drive Overload " + global_version_string);
        m_window = SDL_CreateWindow( WinTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN );

       // m_fontFile = IMG_Load("data/fonts/unicode.png");
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);




        if(!m_window || !m_renderer){
            std::cout <<  "SDL could not initialize! SDL_Error:" <<  SDL_GetError() << std::endl;
            return false;
        }
        else{
            std::cout <<  "SDL Initialized" << std::endl;

            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            SDL_RenderPresent(m_renderer);

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
            SDL_RenderSetLogicalSize(m_renderer, 640, 480);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                return false;
            }

            m_mainFontObject = _SharedPtr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer));

            m_mainFontObject->loadFromFile("data/fonts/terminal8x8_aa_ro.png");
            m_fontFile = m_mainFontObject->getBitmapFont();
            //Build font from texture
            m_fontFile->buildFont( m_mainFontObject.get() );

            //SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            //SDL_RenderClear( m_renderer );
            //m_fontFile->renderText( 10, 10, "Bitmap Font:\n\nABDCEFGHIJKLMNOPQRSTUVWXYZ\n\nabcdefghijklmnopqrstuvwxyz\n\n0123456789" );
            //SDL_RenderPresent( m_renderer );
/*
            // An Event Handler
            SDL_Event e;

            //m_mainFontObject->setColor(100, 100, 100);
            //m_mainFontObject->setAlpha(100);
            while( true  )
            {
                SDL_PollEvent( &e );
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    return false;
                }

                //Clear screen
                SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( m_renderer );


                m_fontFile->renderText( 10, 10, "Bitmap Font:\n\nABDCEFGHIJKLMNOPQRSTUVWXYZ\n\nabcdefghijklmnopqrstuvwxyz\n\n0123456789" );
                //Update screen
                //SDL_RenderCopy(m_renderer, m_mainTexture, NULL, NULL);

                SDL_RenderPresent( m_renderer );

            }
*/
            return true;
            //SDL_Delay( 5000 );
        }
    }

    return false; // If we got here, something clearly went wrong

}

int SDLManager::getWidth() {
    return m_width/m_fontFile->getsizeX();
}

int SDLManager::getHeight() {
    return m_height/m_fontFile->getsizeY();
}


int SDLManager::getSDLWidth(){

    return m_width;
}
int SDLManager::getSDLHeight(){
    return m_height;

}

int SDLManager::getfps() {
    //return 1000/m_maxfps;
    return FpsCounter::Instance()->get();

}

void SDLManager::setmaxfps(int fps) {

    if(fps < 1)
        fps = 1;

    if(fps > 1000)
        fps = 1000;

    m_maxfps = fps;

}

_SharedPtr<GenericWindow> SDLManager::getNewWindow() {
    return _SharedPtr<SDLWindow>(new SDLWindow(getHeight(), getWidth(), 0, 0, this));
}

_SharedPtr<SDLTextureWrapper> SDLManager::getBitmapFontHandler(){

    return m_mainFontObject;
}


_SharedPtr<SDLBitmapFont> SDLManager::getMainFont(){

    return m_fontFile;
}


SDL_Surface * SDLManager::getMainScreen(){

    return m_mainScreen;
}


SDL_Renderer *SDLManager::getRenderer(){

    return m_renderer;
}

int SDLManager::getInput() {


//    SDL_StartTextInput();


    SDL_PollEvent( &m_event );

    if(m_event.type == SDL_QUIT){
        exit(0);
    }

    else if(m_event.type == SDL_KEYDOWN){

        SDL_Keycode keyPressed = m_event.key.keysym.sym;

        switch(keyPressed){

            case SDLK_TAB:
                SDL_Event newEvent;
                m_event = newEvent;
                return KEY_TAB;
            case SDLK_ESCAPE:
                exit(0);
            case SDLK_a:
                return 'a';
            case SDLK_d:
                return 'd';
            case SDLK_r:
                return 'r';
            case SDLK_SPACE:
                return ' ';

        }
    }
    else{
        /*if(FpsCounter::Instance()->get() > m_maxfps){
            SDL_Delay( 100 );
        }*/
        return -1;

    }
}

void SDLManager::startRawInputFeed() {
    GraphicsDriverManager::startRawInputFeed();
}

void SDLManager::stopRawInputFeed() {
    GraphicsDriverManager::stopRawInputFeed();
}

void SDLManager::shutdown() {
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    SDL_Quit();
}

void SDLManager::render(){


    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderPresent( m_renderer );

}

void SDLManager::renderToMainScreen(SDL_Texture *texture){


    SDL_RenderCopy(m_renderer, texture, NULL, NULL);
    SDL_RenderPresent( m_renderer );

}






// The end of our _WARPDRIVE_SDLCLIENT_ ifdef
#endif