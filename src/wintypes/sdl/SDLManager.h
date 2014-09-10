#pragma once

/*

An SDL Driver Management handler

- Yamamushi

 */

// We're wrapping this is a giant ifdef for clarity
#include "config.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include "managers/GraphicsDriverManager.h"
#include "SDL.h" // Header inclusion follows the current standard, which is “SDL.h”, not <SDL2/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"


class SDLManager : public GraphicsDriverManager {

public:

    bool start();

    int getWidth();
    int getHeight();
    int getfps();
    void setmaxfps(int fps);

    _SharedPtr<GenericWindow> getNewWindow();

    int getInput();

    void startRawInputFeed();
    void stopRawInputFeed();

    void shutdown();


protected:



private:

    // Our "Global" Font file (font.png as used here)
    SDL_Surface *fontFile;

    // The screen that ultimately pops up on the display
    SDL_Window *m_window;


};


#endif
