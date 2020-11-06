// hdw_cf.h

#ifndef _HDW_CF_h
#define _HDW_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Hdw_cf :
	public Config_base
{
public:

	uint8_t lt_type;//灯光类型

	uint8_t ar_con;//空调类型
	uint16_t ar_p_t;//空调压缩机延时启动时间

	uint8_t wt_con;//水温调节器类型
	uint16_t wt_p_t;//水温压缩机延时启动时间

	int8_t check_input(unsigned char* buff) override;//合法性检查
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	Hdw_cf(uint8_t cmd_code);
	~Hdw_cf();

};

#endif


