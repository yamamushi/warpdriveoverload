// ship.cpp
// defintion for the ship class

#include<cstdlib>
#include<iostream>

#include "Ship.h" 

Ship::Ship( std::string shipName, std::string fshipClass ) {
    
	m_shipClass = fshipClass;
	m_shipName = shipName;
	if( fshipClass == "Wolf" ) {
		m_maxShieldHP = 500;
		m_shieldHP = m_maxShieldHP;
		m_armorMod = 1;
		m_maxArmorHP = 100;
		m_maxPartSize = 2;
		m_shipSizeClass = 2; // "Frigate" size. 1 is a single-man fighter. a frigate is the smallest multi-man ship.
		m_armorHP = m_maxArmorHP;
		m_reactorSlots.resize(1);
		m_thrusterSlots.resize(4);
		m_weaponSlots.resize(3);
		m_shieldSlots.resize(4);
		m_sensorSlots.resize(1);
		m_commSlots.resize(2);
		m_armorSlots.resize(2);
        
        /*
		m_reactorSlots[0] = 110;
		m_sensorSlots[0] = 510;
		for( int i = 0; i < 4; i++ ) {
			m_thrusterSlots[i] = 210;
			m_shieldSlots[i] = 410;
		}
		for( int i = 0; i < 3; i++ ) {
			m_weaponSlots[i] = 310;
		}
		for( int i = 0; i< 1; i++ ) {
			m_commSlots[i] = 610;
			m_armorSlots[i] = 710;
		}
         
         */
		m_maxHull = 200;
		m_hullHP = m_maxHull;
		m_pGridMax = 50;
		m_powerGrid = 0;
	}
}

void Ship::setClassDefaults( std::string shipClass ) {
    ;
}
