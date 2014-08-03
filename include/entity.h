// entity.h
//
// entity classes for various critters and players.


#include<cstdlib>
#include<iostream>
#include<stringstream>
#include<algorithm>


class player {
	public:
		player( std::string name ) {
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
		void learn( int& pcskill std::string name ) {
			if( pcskill < 101 ) {
				pcskill++;
			}
			else {
				std::cout << "Skill " << name << " already at maximum." << std::endl;
			}
		}
		damageEvent( float Finit, float Fstam );
		move();
	private:
		void die() {
			isAlive = false;
			maxHP = 0;
		}
		void takeDamage( int dmg ) {
			int starthit = health;
			health = starthit - dmg;
			if( health < 1 ) {
				die();
			}
		}
		void repairDamage( int rep ) {
			int starthit = health;
			health = starthit + rep;
			if( health > maxHP ) {
				health = maxHP;
			}
		}
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


class ship {
	public:
		ship( std::string shipName, std::string fshipClass; ) {
			
		}
	private:
		int shieldHP;
		int maxShield;
		float armorMod;
		int armorHP;
		int maxArmor;
		int hullHP;
		int maxHull;
		std::string shipClass;
		std::string name;

};
