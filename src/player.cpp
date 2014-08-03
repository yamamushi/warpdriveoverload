#include "player.h"

void Player::learn(int& pcskill std::string name)
{
                        if( pcskill < 101 ) {
                                pcskill++;
                        }
                        else {
                                std::cout << "Skill " << name << " already at maximum." << std::endl;
                        }
                }


                void Player::die() {
                        isAlive = false;
                        maxHP = 0;
                }
                void Player::takeDamage( int dmg ) {
                        int starthit = health;
                        health = starthit - dmg;
                        if( health < 1 ) {
                                die();
                        }
                }
                void Player::repairDamage( int rep ) {
                        int starthit = health;
                        health = starthit + rep;
                        if( health > maxHP ) {
                                health = maxHP;
                        }
                }
