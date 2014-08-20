#include <string>

class Entity {
    
public:
    
    Entity( std::string type ) : m_type(type){}
    
    bool updatePos( int newX, int newY, int newZ );
    bool move( int headX, int headY, int headZ, int speed, int duration ){return false;}
    
    virtual std::string getName(){return "";}
    
private:
    
    int m_xPos;
    int m_yPos;
    int m_zPos;
    
    float m_height;
    float m_width;
    float m_mass;
    float m_length;
    
    int m_xHeading;
    int m_yHeading;
    int m_zHeading;
    
    std::string m_type;
    
};
