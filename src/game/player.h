// player.h
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#include "entity.h"




class Player : public Entity {

public:

	Player( std::string name );
	void learn( int& pcskill, std::string name );
	void damageEvent( double Finit, double Fstam );
	bool move();

    std::string getName(){return m_playerName;}

private:

	void die();
	void takeDamage( int dmg );
	void repairDamage( int rep );

	int m_xPos;
	int m_yPos;
	int m_zPos;
	std::string m_playerName;
	bool m_isAlive;
	int m_health;
	int m_maxHP;
	double m_stamina;
	int m_encumbrance;
	int m_skillPiloting;
	int m_skillGunnery;
	int m_skillEngineering;
	int m_skillMedicine;
	int m_skillScience;
	int m_skillMarksman;
	int m_skillTactics;

};


