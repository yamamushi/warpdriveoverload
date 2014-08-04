// entity.cpp
// definitions for entity class in entity.h.

#include"entity.h"
#include<iostream>
#include<cstdlib>
#include<cmath>

entity::entity( std::string type ) {
	
}

void entity::updatePos( int newX, int newY, int newZ ) { // used for teleporting to a new system from that origin systems jump point
	m_xPos =  newX;
	m_yPos = newY;
	m_zPos = newZ;
	m_xHeading = 0;
	m_yHeading = 0;
	m_zHeading = 0;
}

void entity::move( int headX, int headY, int headZ, int speed, int duration ){
	// T = duration
	// D = distance
	// V = Initial velocity
	// G = Acceleration due to gravity
	// Vh = horizontal velocity at start
	// Vv = initial vertical velocity.
	// Ay = y rotational angle
	// Ax = x rotational angle
	// Az = z Rotational angle
	// tan(T) = (y2 - y1) / (x2 - x1)
	// D = SQRT[(x2 - x1)^2 + (y2 - y1)^2]
	// Vh = V * cos(Ax) = V * SQRT(2)/2
	// Vv = V * sin(Ax) = V * SQRT(2)/2
	// D = Vh * T
	// Vv = G *(T/2)
	// T = D/Vh
	// Vv = G * ((D/Vh)/2)
	// V = SQRT(G * D )
	//
	// FUCKING MATH HOW DOES IT WORK
}
