#pragma once
#include "SDLManager.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "BitmapFont.h"


class SDLBitmapFont;


//Texture wrapper class
class SDLTextureWrapper
{
public:
    //Initializes variables
    SDLTextureWrapper(SDL_Renderer *renderer);

    //Deallocates memory
    ~SDLTextureWrapper();

    _SharedPtr<SDLBitmapFont> getBitmapFont();

    // We actually shouldn't need to grab this information because this object
    // Will handle our rendering for us by talking to m_renderer (the renderer
    // in the constructor)
/*
    SDL_Texture *getTexture();
    void setDrawOn(SDL_Texture *surface);
*/
    //Loads image at specified path
    bool loadFromFile( std::string path );

        //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

    //Pixel manipulators
    bool lockTexture();
    bool unlockTexture();
    void* getPixels();
    int getPitch();
    Uint32 getPixel32( unsigned int x, unsigned int y );

private:

    // Our SDL Window Renderer
    SDL_Renderer *m_renderer;
    _SharedPtr<SDLBitmapFont> m_sdlfontObject;

    TTF_Font *m_ttfFont;

    //The actual hardware texture
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
};



#endif