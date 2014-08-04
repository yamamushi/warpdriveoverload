class Entity {
	public:
		entity( std::string type );
		void updatePos( int newX, int newY, int newZ );
		void move( int headX, int headY, int headZ, int speed, int duration );
		
	protected:
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
		std::string type;
};
