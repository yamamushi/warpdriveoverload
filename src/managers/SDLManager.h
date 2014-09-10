/*

An SDL Driver Management handler

- Yamamushi

 */

// We're wrapping this is a giant ifdef for clarity
#include "config.h"
#ifdef _WARPDRIVE_SDLCLIENT_

#include "SDL.h" // Header inclusion follows the current standard, which is “SDL.h”, not <SDL2/SDL.h>
#include "GraphicsDriverManager.h"


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

    friend class Shell;



private:


};



#endif
