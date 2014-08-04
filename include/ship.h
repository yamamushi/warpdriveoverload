class Ship : protected entity {
        public:
                ship( std::string shipName, std::string fshipClass );
        private:
		void takeDamage( int dXPos, int dYPos, int dZPos, int dmg );
		void setClassDefaults( std::string shipClass );
		int m_scanStrength;
		int m_sigRadius;
		int m_vol;
		void addPart( int slot, int mass );
		int m_mass;
		int m_maxPartSlots;
		int m_maxPartSize;
		int m_shipSizeClass;
		std::vector<int> m_thrusterSlots;
		std::vector<int> m_reactorSlots;
		std::vector<int> m_weaponSlots;
		std::vector<int> m_shieldSlots;
		std::vector<int> m_sensorSlots;
		std::vector<int> m_commSlots;
		std::vector<int> m_armorSlots;
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
