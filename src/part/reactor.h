// reactor.h reactor class declaration file
#ifndef __REACTOR_H
#define __REACTOR_H
class reactor : protected part {
	public:
		reactor();
		void run();
		bool adjustOutput( const float &fnewpercent, const bool &overloadenabled );
	protected:
		float p_coreUtilization;
		int p_maxPGridMod;
		int p_coreTemp;
		bool p_isRunning;
		bool p_inMeltDown;
		int p_powerDraw;
	private:
		void meltdown();
};
#endif
