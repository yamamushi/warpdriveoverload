/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#include "TreasureChest.h"

TreasureChest::TreasureChest ()
{
	chest.loadobj ("chest.tr3"); //Loading the 3D model for the chest (without the lid) from file.
	lid.loadobj ("lid.tr3"); //Loading the 3D model for the lid from file.
    
	lid.ctrscaleoff (3.00, 2.50, 2.00); //Setting the lid to pivot about the hinge point of the chest.
    
	lidbuffer = lid.permcpy (); //Copying the unrotated lid data to the Polygon buffer vector.
    
	for (int i = 0; i < lidbuffer.size (); i++)
	{
		chest.addside (&lidbuffer [i]); //Adding the unrotated lid data to the main body of the chest.
	}
    
	chest.ctrscaleoff (chest.centerx (), chest.centery (), chest.centerz ()); //Setting the whole chest (lid and main body) to rotate about the geometric center of an idealized, unopened chest.
    
	chest.addolink (&lid, true); //Object linking the R3Object containing the whole chest with the R3Object containing the untransformed lid data.
}

void TreasureChest::openlid (double angle)
{
	lid.basisreset (); //Resetting the rotation basis for the lid, such that the lid opens to the angle specified, rather than the last angle plus the current specified angle.
    
	lid.rot ('y', angle); //Rotating the lid to the specified angle about the hinge position.
    
	lidbuffer.resize (0); //Clearing the lidbuffer.
    
	lidbuffer = lid.permcpy (); //Filling the lidbuffer with new transformed/opened lid data.
    
	for (int i = chest.sidenum () - lidbuffer.size (); i < chest.sidenum (); i++) //Updating the 'chest' R3Object to reference the refreshed lid data.
	{
		chest.modside (i, &lidbuffer [i + lidbuffer.size () - chest.sidenum ()]);
	}
}

void TreasureChest::movechest (double xdisp, double ydisp, double zdisp)
{
	double scalepchest [3]; //Declaring a 3-tuple double array to hold the scaling and rotation point (unopened geometric center) specified for the chest.
	double scaleplid [3]; //Declaring a 3-tuple double array to hold the scaling and rotation point (hinge coordinates) specified for the lid.
    
	chest.cpyscalep (scalepchest); //Loading the coordinates of the chest scaling and rotation point.
	lid.cpyscalep (scaleplid); //Loading the coordinates of the lid scaling and rotation point.
    
	chest.shiftctr (xdisp, ydisp, zdisp); //Repositioning the chest and, due to the object linkage, the lid the specified distance on each coordinate axis.
    
	chest.ctrscaleoff (scalepchest [0] + xdisp, scalepchest [1] + ydisp, scalepchest [2] + zdisp); //Updating the scaling and rotation point of the chest to compensate for the positional shift.
	lid.ctrscaleoff (scaleplid [0] + xdisp, scaleplid [1] + ydisp, scaleplid [2] + zdisp); //Updating the scaling and rotation point of the lid to compensate for the positional shift.
}

void TreasureChest::rotchest (char axis, double angle) //The simplicity of this function makes it a bit redundant, but, nevertheless, it is defined for parallelism's sake.
{
	chest.rot (axis, angle); //Rotating the chest R3Object about the specified axis through a given angle (in radians).
}

TerosR3Object * TreasureChest::putchest ()
{
	return &chest; //Returning a pointer to the chest R3Object.
}

TerosR3Object * TreasureChest::putlid ()
{
	return &lid; //Returning a pointer to the lid R3Object.
}


void TreasureChest::reset(){
    
    lid.basisreset();
    chest.basisreset();
    
}
