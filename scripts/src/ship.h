#include <vector>
#include <string>


#include "room.h"

class Ship : public Room {
    
public:
    
    Ship( std::string shipName, std::string fshipClass );
    
    std::string getName(){return m_shipName;}
    
private:
    
    void takeDamage( int dXPos, int dYPos, int dZPos, int dmg );
    void setClassDefaults( std::string shipClass );
    void addPart( int slot, int pID );
    
    
    
    int m_scanStrength;
    float m_sigRadius;
    int m_vol;
    int m_mass;
    int m_maxPartSlots;
    int m_maxPartSize;
    int m_shipSizeClass;
    
    std::vector<Room> m_roomsList;
    
    
    std::vector<std::vector<int> > m_thrusterSlots;
    std::vector<std::vector<int> > m_reactorSlots;
    std::vector<std::vector<int> > m_weaponSlots;
    std::vector<std::vector<int> > m_shieldSlots;
    std::vector<std::vector<int> > m_sensorSlots;
    std::vector<std::vector<int> > m_commSlots;
    std::vector<std::vector<int> > m_armorSlots;
    std::vector<std::vector<int> > m_warpDriveSlots;
    std::vector<std::vector<int> > m_deckPos;
    
    
    
    int m_shieldHP;
    int m_maxShieldHP;
    float m_armorMod;
    int m_armorHP;
    int m_maxArmorHP;
    int m_hullHP;
    int m_maxHull;
    int m_powerGrid;
    int m_pGridMax;
    std::string m_shipClass;
    std::string m_shipName;
    int m_thrust;
    int m_maxThrust;
    bool m_accelerate();
    
};
