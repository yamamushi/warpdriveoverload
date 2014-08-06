class Ship : protected entity {
        public:
                Ship( std::string shipName, std::string fshipClass );
        protected:
		void takeDamage( int dXPos, int dYPos, int dZPos, int dmg );
		void setClassDefaults( std::string shipClass );
		int m_scanStrength;
		float m_sigRadius;
		int m_vol;
		void addPart( int slot, int pID );
		int m_mass;
		int m_maxPartSlots;
		int m_maxPartSize;
		int m_shipSizeClass;
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
		int m_thrust;
		int m_maxThrust;
		bool m_accelerate();

};
