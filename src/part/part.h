// Part class definition file.
// defines the 'part' class as a subclass of 'ship'


class Part : protected Ship {
	public:
		Part( int typeId, std::string PartName, int metaLevel, int partID );
	protected:
		std::string m_partName;
		int p_slotSize;
		int p_typeID;
		float p_sigRadMod;
		int p_partHullHP;
		int p_pGridDraw;
		int p_mass;
		int p_width;
		int p_length;
		int p_height;
		int p_addService;		
	private:
		int p_metaLevel;
		int p_partID;
};
