// comm.h class declaration for comm unit parts

class comm : protected part {
	public:
		comm( bool isDish );
		void run();
	protected:
		int p_commRange;
		bool p_isDish;
		int p_currentTarget;
	private:
		bool transmit( int targetID );
};
