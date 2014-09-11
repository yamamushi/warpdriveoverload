#pragma once
/*

  BitmapFont Class - Used for generating our font "sprite sheet".

  Note:: This will ONLY work with a full Unicode font (65,535
  characters).

  The font supplied with with the project (font.png) was generated for
  use with this loader.

  -Yamamushi (Jon Rumion)
  12-09-12

 */

#include "SDLManager.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDLTextureWrapper.h"

class SDLTextureWrapper;

//Our bitmap font
class SDLBitmapFont
{
public:
    //The default constructor
    SDLBitmapFont();

    //Generates the font
    bool buildFont( SDLTextureWrapper *bitmap );

    //Shows the text
    void renderText( int x, int y, std::string text );

    int getsizeX(std::string text);
    int getsizeY(std::string text);

    int getsizeX();
    int getsizeY();

private:
    //The font texture
    SDLTextureWrapper* mBitmap;

    //The individual characters in the surface
    SDL_Rect mChars[ 256 ];

    //Spacing Variables
    int mNewLine, mSpace;
};


#endif