#ifndef _TIME_SWICH_CF_h
#define _TIME_SWICH_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"
#include "clock.h"

class Time_swich_cf :
	public Config_base
{
public:

	int8_t check_input(unsigned char* buff) override;//检查输入的数据合法性
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	uint8_t max;//开启时的最大值

	void power_out(uint8_t &now_power);//判断开关状态

	Time_swich_cf(uint8_t cmd_code);
	~Time_swich_cf();

private:

	uint8_t on_h;//开时
	uint8_t on_m;//开分
	uint8_t off_h;//关时
	uint8_t off_m;//关分

	uint32_t on_sec;//开时刻在今天的秒数
	uint32_t off_sec;//关时刻在今天的秒数

};

#endif


