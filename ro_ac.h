#ifndef _RO_AC_h
#define _RO_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define RO_PUMP_PIN 30 //dc-e

class Ro_ac:
	public Actuator_base
{

public:

	bool need_add;//是否需要补水(来于主水箱浮子开关)

	uint16_t report_state(unsigned char* buff) override;//报告状态
	void exce() override;//执行

	Ro_ac();
	~Ro_ac();

};

#endif


