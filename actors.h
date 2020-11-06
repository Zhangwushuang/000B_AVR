// actors.h

#ifndef _ACTORS_h
#define _ACTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "configs.h"

#include "co2_ac.h"
#include "humi_add_ac.h"
#include "in_fan_ac.h"
#include "light_ac.h"

#include "ro_ac.h"
#include "spray_ac.h"
#include "wt_temp_ac.h"
#include "air_temp_ac.h"

#define TEC_PUMP 25//dc-H,TECÀÆ¿‰±√º∞∑Á…»

class Actors
{
public:
	static Co2_ac* const co2;
	static Humi_add_ac* const humi_add;
	static In_fan_ac* const in_fan;
	static Light_ac* const light;

	static Ro_ac* const ro;
	static Spray_ac* const spray;
	static Wt_temp_ac* const wt_temp;
	static Air_temp_ac* const air_temp;

};
#endif


