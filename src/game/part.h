// Part class definition file.
// defines the 'part' class as a subclass of 'ship'

#ifndef __PART_H
#define __PART_H
class Part : protected Ship {
	public:
		Part( int typeId, std::string PartName, int metaLevel, int partID );
	protected:
		
	private:
		bool loadProperties( const std::string &ptype );
		std::string m_PartName;
		int m_typeID;
		int m_metaLevel;
		int m_partID;
		int m_slotSize;
		double m_sigRadMod;
		
};
#endif
