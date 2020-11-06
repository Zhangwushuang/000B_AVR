#ifndef _AIR_TEMP_AC_h
#define _AIR_TEMP_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "temp_ac.h"

#define AR_TEMP_AC_CP 33 //ac-e
#define AR_TEMP_AC_HP 36 //ac-f

#define AR_TEMP_DL_ALT 1

class Air_temp_ac :
	public Temp_ac
{
public:

	uint16_t report_state(unsigned char* buff) override;//报告状态

	Air_temp_ac(uint8_t tp, uint16_t dl);
	~Air_temp_ac();

};

#endif


