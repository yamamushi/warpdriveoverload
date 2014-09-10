#include "SDLManager.h"
#ifdef _WARPDRIVE_SDLCLIENT_


#include <iostream>


bool SDLManager::start(){

    std::cout << "SDL Mode Started" << std::endl;



    return GraphicsDriverManager::start();

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
    return GraphicsDriverManager::getNewWindow();
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
    GraphicsDriverManager::shutdown();
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