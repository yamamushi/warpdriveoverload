#include "SDLTextureWrapper.h"


#ifdef _WARPDRIVE_SDLCLIENT_

#include "SDL_ttf.h"
#include "SDL_image.h"

#include <iostream>

SDLTextureWrapper::SDLTextureWrapper(SDL_Renderer *renderer){

    m_renderer = renderer;

    m_sdlfontObject = _SharedPtr<SDLBitmapFont>(new SDLBitmapFont());

    mTexture = NULL;

}

SDLTextureWrapper::~SDLTextureWrapper() {

}

bool SDLTextureWrapper::loadFromFile(std::string path) {

//Get rid of preexisting texture
    std::cout << "Here" << std::endl;

    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );


    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to display format
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
        if( formattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
        }
        else
        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture( m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( newTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Enable blending on texture
                SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

                //Lock texture for manipulation
                SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch );

                //Copy loaded/formatted surface pixels
                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                //Get image dimensions
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;

                //Get pixel data in editable format
                Uint32* pixels = (Uint32*)mPixels;
                int pixelCount = ( mPitch / 4 ) * mHeight;

                //Map colors
                Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0, 0xFF, 0xFF );
                Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00 );

                //Color key pixels
                for( int i = 0; i < pixelCount; ++i )
                {
                    if( pixels[ i ] == colorKey )
                    {
                        pixels[ i ] = transparent;
                    }
                }

                //Unlock texture to update
                SDL_UnlockTexture( newTexture );
                mPixels = NULL;
            }

            //Get rid of old formatted surface
            SDL_FreeSurface( formattedSurface );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;

}

bool SDLTextureWrapper::loadFromRenderedText(std::string textureText, SDL_Color textColor) {

//Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( m_ttfFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( m_renderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    //Return success
    return mTexture != NULL;

}



_SharedPtr<SDLBitmapFont> SDLTextureWrapper::getBitmapFont(){

    return m_sdlfontObject;

}

/*
SDL_Texture *SDLTextureWrapper::getTexture(){

    return mTexture;

}


void SDLTextureWrapper::setDrawOn(SDL_Texture *surface){

    mTexture = surface;

}
*/

void SDLTextureWrapper::free() {
    //Free texture if it exists
    if( mTexture != nullptr )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mPixels = NULL;
        mPitch = 0;
    }
}

void SDLTextureWrapper::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );

}

void SDLTextureWrapper::setBlendMode(SDL_BlendMode blending) {
    //Set blending function

    SDL_SetTextureBlendMode( mTexture, blending );

}

void SDLTextureWrapper::setAlpha(Uint8 alpha) {
    //Modulate texture alpha

    SDL_SetTextureAlphaMod( mTexture, alpha );

}

void SDLTextureWrapper::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {

//Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( m_renderer, mTexture, clip, &renderQuad, angle, center, flip );

}

int SDLTextureWrapper::getWidth() {
    return mWidth;
}

int SDLTextureWrapper::getHeight() {
    return mHeight;
}

bool SDLTextureWrapper::lockTexture() {
    bool success = true;

    //Texture is already locked
    if( mPixels != NULL )
    {
        printf( "Texture is already locked!\n" );
        success = false;
    }
        //Lock texture
    else
    {
        if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
        {
            printf( "Unable to lock texture! %s\n", SDL_GetError() );
            success = false;
        }
    }

    return success;
}

bool SDLTextureWrapper::unlockTexture() {
    bool success = true;

    //Texture is not locked
    if( mPixels == NULL )
    {
        printf( "Texture is not locked!\n" );
        success = false;
    }
        //Unlock texture
    else
    {
        SDL_UnlockTexture( mTexture );
        mPixels = NULL;
        mPitch = 0;
    }

    return success;
}

void *SDLTextureWrapper::getPixels() {
    return mPixels;
}

int SDLTextureWrapper::getPitch() {
    return mPitch;
}

Uint32 SDLTextureWrapper::getPixel32(unsigned int x, unsigned int y) {

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32*)mPixels;

    //Get the pixel requested
    return pixels[ ( y * ( mPitch / 4 ) ) + x ];

}



#endif