// sht_cf.h

#ifndef _SHT_CF_h
#define _SHT_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Sht_cf:
	public Config_base
{
 public:

	 uint32_t space;//间隔时间
	 uint8_t mode;//0:不拍摄.1:仅开灯时拍摄.2:所有时间都拍摄

	 int8_t check_input(unsigned char* buff) override;//合法性检查
	 void load_confi() override;//读取设置
	 uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	 Sht_cf(uint8_t cmd_code);
	 ~Sht_cf();

};

#endif

