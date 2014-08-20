// reactor.h reactor class declaration file

class reactor : protected part {
	public:
		reactor();
		void run( );
	protected:
		int p_maxPGridMod;
		int p_coreTemp;
		bool p_isRunning;
		bool p_inMeltDown;
		int p_powerDraw;
	private:
		void meltdown();
};
