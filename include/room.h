class Room {

public:

Room(int x, int y, int z) : m_x(x), m_y(y), m_z(z){};
~Room();

private:

// Dimensions in meters.
int m_x;
int m_y;
int m_z;

};
