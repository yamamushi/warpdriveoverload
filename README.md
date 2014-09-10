Warp Drive Overload
=================

#The Game: 

Warp Drive Overload is a (massive) multiplayer project focused around the piloting of warp enabled spacecraft from within the spacecraft themselves. 

The focus of the game is not the graphics from outside of the spacecraft, rather players will be expected to pilot their craft from the computer consoles onboard their craft using live sensor information being provided to them to do everything from navigation, managing the power consumption onboard, maintaining life support, or even manually docking at a spaceport and having to communicate with traffic control to guide them to their assigned docking bays. 

Ships will be customizable, and they will also come in various sizes. However larger ships will require real-player crews to manage the various systems onboard in order to safely navigate the stars. Getting into a fight might may mean certain death to an untrained crew.

Players will not not limited to flying around on spacecraft as there will also be options for simply hiring a crew to fly them to destinations, or to hire ships to carry cargo for them. 


# The Library

In order to facilitate the user interfaces ideal for this project, an extensible 2D graphics library for terminal applications is being developed that supports the rendering of 3D objects in a 2D environment based on prior work done by [TEROS Engine](https://github.com/SighoftheSecond/TEROS-ENGINE). A short demo of this capability can be seen here: [https://www.youtube.com/watch?v=WhxibkLnjdE](https://www.youtube.com/watch?v=WhxibkLnjdE) .

Aims for the library are cross-platform support, a reusable widgets library, and an extensive windowing system. 

Currently support for Ncurses has been implemented, and the following support is planned:

* SDL2 - [https://www.libsdl.org/](https://www.libsdl.org/) (In Development)
* aalib - [http://aa-project.sourceforge.net/aalib/](http://aa-project.sourceforge.net/aalib/)
* pdcurses - [http://pdcurses.sourceforge.net/](http://pdcurses.sourceforge.net/)
* libcaca - [http://caca.zoy.org/wiki/libcaca](http://caca.zoy.org/wiki/libcaca)
     


#Building

##Dependencies:

    Boost (There is no guarantee anything less than version 1.52 will work properly)
    GCC 4.7+ or Clang (Needs to be fully C++11 Compatible)
    Sqlite3
    Google Protobufs
    pkgconfig


**Ncurses Mode**

This is currently the default mode built:

    Ncursesw 

**SDL2 Mode**

    sdl2
    sdl2_image
    sdl2_mixer
    sdl2_ttf

**OS X Users** 

If you are on OSX using [homebrew](http://brew.sh/), you can install all of these dependencies with: 

    brew install ncurses sdl2 sdl2_mixer sdl2_image sdl2_ttf
    brew install sqlite protobuf boost pkgconfig  
    brew install ncurses && link ncurses --force



##Compiling

**Getting the source:**
    
    git clone https://github.com/yamamushi/warpdriveoverload
    cd warpdriveoverload
    git checkout develop

**Choosing a Client:**

You will need to edit this file:

     src/config.h.in

Uncomment the graphics mode you want to compile support for. Only choose one option, or -strange- things can happen. 

*There are currently plans to fix this to autodetect which you have support for, and to allow for compiling support for all rendering types.*


**Compiling:**

You will need to be in the project root directory to follow these directions (which would be warpdriveoverload if you followed the default instructions above).

    mkdir build
    cd build
    cmake .. && make
    bin/warpclient


#Reporting Issues

Please open an [issue on Github](https://github.com/yamamushi/warpdriveoverload/issues), or contact the primary project owner at yamamushi [at] gmail [dot] com . We'll work as fast as possible to resolve any issues, as we want to maintain a good track record of maintenance for this project.
    

#Development:

We're a very small group, and we're always looking for help. Everything from idea makers, storywriters, musicians to coders and people who can write documentation. 

Please contact yamamushi [at] gmail [dot] com if you'd like to contribute in any way, or just have general questions about the project. 



