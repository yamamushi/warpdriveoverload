// entity.h
//
// entity classes for various critters and players.


#include<cstdlib>
#include<iostream>
#include<stringstream>
#include<algorithm>


class Player : public Entity {

public:
		Player( std::string name ) {
			playerName = name;
			isAlive = true;
			health = 100;
			maxHP = 100;
			stamina= 1.0;
			encumbrance = 1;
			skillPiloting = 5;
			skillGunnery = 5;
			skillEngineering = 5;
			skillMedicine = 5;
			skillScience = 5;
			skillMarksman = 5;
		}
		void learn( int& pcskill std::string name );
		damageEvent( float Finit, float Fstam );
		move();
	private:
		void die();
		void takeDamage( int dmg );
		void repairDamage( int rep );

		int xPos;
		int yPos;
		int zPos;
		std::string playerName;
		bool isAlive;
		int health;
		int maxHP;
		float stamina;
		int encumbrance;
		int skillPiloting;
		int skillGunnery;
		int skillEngineering;
		int skillMedicine;
		int skillScience;
		int skillMarksman;
		int skillTactics;
};


