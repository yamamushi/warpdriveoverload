// shield.h shield class declaration

class shield : protected part {
	public:
		shield();
		void run();
	protected:
		int p_regenSpeed;
		int p_maxShieldMod;
	private:
		void regen( int maxShield, int currentShield );
};
