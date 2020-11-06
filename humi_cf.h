#ifndef _HUMI_CF_h
#define _HUMI_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Humi_cf :
	public Config_base
{
public:

	int8_t check_input(unsigned char* buff) override;//检查输入的数据合法性
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	void power_out(uint8_t humi, int8_t &now_power, bool &alert);

	Humi_cf(uint8_t cmd_code);
	~Humi_cf();

private:
	uint8_t hh;//设定最高湿度（除湿开启湿度）
	uint8_t rsh;//除湿停止湿度
	uint8_t ash;//加湿停止湿度
	uint8_t lh;//设定最低湿度（加湿开启湿度）
	bool ig;//是否忽视
};

#endif


