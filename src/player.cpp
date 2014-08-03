#include "player.h"

void Player::Player(std::string name ) 
{
        m_playerName = name;
        m_isAlive = true;
        m_health = 100;
        m_maxHP = 100;
        m_stamina= 1.0;
        m_encumbrance = 1;
        m_skillPiloting = 5;
        m_skillGunnery = 5;
        m_skillEngineering = 5;
        m_skillMedicine = 5;
        m_skillScience = 5;
        m_skillMarksman = 5;
}



void Player::learn(int& pcskill std::string name)
{
        if( pcskill < 1001 ) {
                pcskill++;
        }
        else {
                std::cout << "Skill " << name << " already at maximum." << std::endl;
        }
}


void Player::die() {
        m_isAlive = false;
        m_maxHP = 0;
}


void Player::takeDamage( int dmg ) {
        int starthit = m_health;
        m_health = starthit - dmg;
        if( m_health < 1 ) {
                die();
        }
}

                
void Player::repairDamage( int rep ) {
        int starthit = m_health;
        m_health = starthit + rep;
        if( m_health > m_maxHP ) {
                m_health = m_maxHP;
        }
}
