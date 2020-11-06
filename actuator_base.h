// actuator_base.h

#ifndef _ACTUATOR_BASE_h
#define _ACTUATOR_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Actuator_base
{
public:
	virtual uint16_t report_state(unsigned char* buff) = 0;//将状态写入缓存
	virtual void exce() = 0;//执行

};
#endif


