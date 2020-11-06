#ifndef _HUMI_ADD_AC_h
#define _HUMI_ADD_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define HU_ADD_PIN 23 //dc-g

class Humi_add_ac :
	public Actuator_base
{
public:
	int8_t hu_ct;//是否需要加除湿(来自于config)

	void adjust_power_lv(bool lv_alt);//根据水箱情况计算是否能够加湿
	void adjust_power(bool lv_alt, int8_t &is_heat);//根据制冷加热和水位状态计算是否应该加湿

	uint16_t report_state(unsigned char* buff) override;//报告状态
	void exce() override;//执行

	Humi_add_ac();
	~Humi_add_ac();

};

#endif


