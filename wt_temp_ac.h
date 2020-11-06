#ifndef _WT_TEMP_AC_h
#define _WT_TEMP_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "temp_ac.h"

#define WT_TEMP_AC_CP 27 //ac-a
#define WT_TEMP_AC_HP 29 //ac-b

#define WT_TEMP_DL_ALT 2

class Wt_temp_ac:
	public Temp_ac
{
public:
	void cp_power(bool mn_lv_alt);//如果缸体内部缺水,那么就不能调节水温
	uint16_t report_state(unsigned char* buff) override;//报告状态

	Wt_temp_ac(uint8_t tp, uint16_t dl);
	~Wt_temp_ac();

};

#endif


