#ifndef _LIGHT_AC_h
#define _LIGHT_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define LT_PWM_PIN 11 //强度调节引脚
#define LT_EN_PIN 37  //使能引脚
#define LT_MODE_PIN 35 //模式切换引脚

class Light_ac:
	public Actuator_base
{

 public:

	 uint8_t mode; //0白光 ,1补光
	 uint8_t power; //亮度输出

	 uint16_t report_state(unsigned char* buff) override;//报告状态
	 void exce() override;//执行

	 Light_ac(uint8_t ac_tp);//类型
	 ~Light_ac();

private:

	const uint8_t type;//灯类型
	void off();
	void on();

};

#endif


