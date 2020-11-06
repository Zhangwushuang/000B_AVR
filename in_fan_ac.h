#ifndef _IN_FAN_AC_h
#define _IN_FAN_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define IN_FAN_CP 10 //控制引脚 fan_a

class In_fan_ac :
	public Actuator_base
{
public:

	uint8_t power;

	void adjust_power(int8_t temp_ctrl);//根据温控状态计算输出

	uint16_t report_state(unsigned char* buff) override;//报告状态
	void exce() override;//执行

	In_fan_ac();
	~In_fan_ac();

};

#endif


