#include "SDLManager.h"
#ifdef _WARPDRIVE_SDLCLIENT_

#include "util/version.h"
#include "BitmapFont.h"
#include <iostream>


bool SDLManager::start(){

    std::cout << "SDL Mode Started" << std::endl;

    m_width = 640;
    m_height = 480;

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


            //SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &m_window, &m_renderer);

            /*
            SDL_Texture *tempSurface = SDL_CreateTexture(m_renderer,
                    SDL_PIXELFORMAT_ARGB8888,
                    SDL_TEXTUREACCESS_STREAMING,
                    640, 480);
            */
            /*
            m_mainTexture = SDL_CreateTexture(m_renderer,
                    SDL_PIXELFORMAT_ARGB8888,
                    SDL_TEXTUREACCESS_STATIC,
                    m_width, m_height);
            */

            m_mainFontObject = _SharedPtr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer));

            m_mainFontObject->loadFromFile("data/fonts/terminal8x8_aa_ro.png");
            m_fontFile = m_mainFontObject->getBitmapFont();
            //Build font from texture
            m_fontFile->buildFont( m_mainFontObject.get() );

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

            return true;
            //SDL_Delay( 5000 );
        }
    }

    return false; // If we got here, something clearly went wrong

}

int SDLManager::getWidth() {
    return GraphicsDriverManager::getWidth();
}

int SDLManager::getHeight() {
    return GraphicsDriverManager::getHeight();
}

int SDLManager::getfps() {
    return GraphicsDriverManager::getfps();
}

void SDLManager::setmaxfps(int fps) {
    GraphicsDriverManager::setmaxfps(fps);
}

_SharedPtr<GenericWindow> SDLManager::getNewWindow() {
    return _SharedPtr<SDLWindow>(new SDLWindow(640,480,0,0, this));
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
    return GraphicsDriverManager::getInput();
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








// The end of our _WARPDRIVE_SDLCLIENT_ ifdef
#endif


/*


        std::cout << "SDL Mode Running" << std::endl;

        SDL_Window *screen = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        SDL_Surface *surface;

        if (!screen) {

            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;

        } else {



            //SDL_Init(SDL_INIT_EVERYTHING);
            surface = SDL_GetWindowSurface(screen);
            SDL_UpdateWindowSurface(screen);

            SDL_Delay(2000);
            SDL_Quit();
        }

        std::cout << "SDL Mode Ended" << std::endl;


    return 0;

}
 */