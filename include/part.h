// Part class definition file.
// defines the 'part' class as a subclass of 'ship'


class Part : protected Ship {
	public:
		Part( int typeId, std::string PartName, int metaLevel, int partID );
	protected:
		
	private:
		std::string m_PartName;
		int m_typeID;
		int m_metaLevel;
		int m_partID;
		int m_slotSize;
		float m_sigRadMod;
		
};
