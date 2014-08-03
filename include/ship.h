class Ship {
        public:
                ship( std::string shipName, std::string fshipClass; ) {
                }
		bool move( int impulse, int mass );
        private:
		void takeDamage( int dXPos, int dYPos, int dZPos, int dmg );
		int m_scanStrength;
		int m_sigRadius;
		int m_vol;
		void addPart( int slot, int mass );
		int m_mass;
		int m_maxPartSlots;
		std::vector<bool> m_partSlots;
                int m_shieldHP;
                int m_maxShield;
                float m_armorMod;
                int m_armorHP;
                int m_maxArmor;
                int m_hullHP;
                int m_maxHull;
		int m_powerGrid;
		int m_pGridMax;
                std::string m_shipClass;
                std::string m_name;
		int m_xPos;
		int m_yPos;
		int m_zPos;
		int m_thrust;
		int m_maxThrust;
		bool m_accelerate();

};
