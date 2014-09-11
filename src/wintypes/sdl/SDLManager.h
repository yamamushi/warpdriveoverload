#pragma once

/*

An SDL Driver Management handler

- Yamamushi

 */

// We're wrapping this is a giant ifdef for clarity
#include "config.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include "managers/GraphicsDriverManager.h"
#include "sdlwindow.h"
#include "SDL.h" // Header inclusion follows the current standard, which is “SDL.h”, not <SDL2/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "BitmapFont.h"
#include "SDLTextureWrapper.h"

class SDLTextureWrapper;



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

    int getSDLWidth();
    int getSDLHeight();

protected:

    friend class SDLWindow;

    _SharedPtr<SDLTextureWrapper> getBitmapFontHandler();
    _SharedPtr<SDLBitmapFont> getMainFont();

    SDL_Surface *getMainScreen();

    SDL_Renderer *getRenderer();

    void renderToMainScreen(SDL_Texture *texture);
    void render();

private:


    // The screen that ultimately pops up on the display
    SDL_Window *m_window;

    SDL_Surface *m_mainScreen;

    SDL_Texture *m_mainTexture;

    SDL_Renderer *m_renderer;

    // Our Font file (unicode.png as used here)
    _SharedPtr<SDLBitmapFont> m_fontFile;

    _SharedPtr<SDLTextureWrapper> m_mainFontObject;

    int m_frameCounter;
    SDL_Event m_event;

};



#endif
