/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */


#ifndef __warpdriveoverloaded__TreasureChest__
#define __warpdriveoverloaded__TreasureChest__


#include "teros.h"
#include "terospolygon.h"
#include "terosR3.h"

#include <vector>

class TreasureChest //Declaring a new class, derivative of the R3Object class, for our advanced 'TreasureChest' object.
{
private:
    TerosR3Object chest; //Declaring an R3Object within the TreasureChest class template to hold the dynamic, instantaneous 3D data for our whole TreasureChest object.
    TerosR3Object lid; //Declaring another R3Object to hold the static 3D data for the lid of the chest--the moving component of this advanced 3D object.
    
    std::vector <TerosPolygon> lidbuffer; //Declaring a vector of Polygons to temporarily hold the instantaneous, transformed lid polygons.
public:
    TreasureChest (); //Prototyping a constructor function for our TreasureChest class.
    
    void openlid (double); //Prototyping a function for opening the lid of the chest to a certain angle (in radians).
    void movechest (double, double, double); //Prototyping a function for moving the entire chest object and its hidden static component, 'lid,' about a 3D Cartesian coordinate system.
    void rotchest (char, double); //Prototyping a function for rotating the instanteous 3D model for the chest about a given axis and through a specified angle.
    
    TerosR3Object * putchest (); //Prototyping a function for returning a pointer to the 'chest' R3Object contained within a given TreasureChest object.
    TerosR3Object * putlid (); //Prototyping a function for returning a pointer to the 'lid' R3Object contained within a given TreasureChest object.
    
    void reset();
};
#endif /* defined(__warpdriveoverloaded__TreasureChest__) */
