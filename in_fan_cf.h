#ifndef _IN_FAN_CF_h
#define _IN_FAN_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class In_fan_cf :
	public Config_base
{

public:
	int8_t check_input(unsigned char* buff) override;//检查输入的数据合法性
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	void power_out(int8_t temp, uint8_t &now_power);//计算风扇出力

	In_fan_cf(uint8_t cmd_code);
	~In_fan_cf();

private:
	int8_t ht;//全速温度
	int8_t lt;//怠速温度

	uint8_t hs;//全速温度时的速度
	uint8_t ls;//怠速温度时的速度

};

#endif


