// entity.h
//
// entity classes for various critters and players.


#include<cstdlib>
#include<iostream>
#include<stringstream>
#include<algorithm>


class player {
	public:
		player() {
			
		}

	private:
		int health;
		float stamina;
		int encumbrance;
		int skillPiloting;
		int skillGunnery;
		int skillEngineering;
		int skillMedicine;
		int skillScience;
		int skillMarksman;
		int skillTactics;
}
