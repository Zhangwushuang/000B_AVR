#ifndef _CO2_AC_h
#define _CO2_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define CO2_TAP_PIN 34 //ac-c

class Co2_ac :
	public Actuator_base
{
public:

	uint8_t need_co2;//是否需要加co2(来源于时间设定)

	uint16_t report_state(unsigned char* buff) override;//报告状态
	void exce() override;//执行

	Co2_ac();
	~Co2_ac();

};

#endif


