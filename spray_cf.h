#ifndef _SPRAY_CF_h
#define _SPRAY_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Spray_cf :
	public Config_base
{

public:

	int8_t check_input(unsigned char* buff) override;
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff
	void power_out(uint32_t last_spray_time, bool &now_power);//计算是否应该喷淋 1上次喷淋距目前的时间 2是否需要喷淋

	Spray_cf(uint8_t cmd_code);
	~Spray_cf();

private:
	uint32_t spray_space;//喷淋间隔(单位秒)
	uint16_t spray_last;//每次喷淋持续时间(单位秒)

};

#endif


