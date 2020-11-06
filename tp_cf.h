#ifndef _TP_CF_h
#define _TP_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Tp_cf:
	public Config_base
{
public:
	int8_t check_input(unsigned char* buff) override;//检查输入的数据合法性
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff
	void power_out(int8_t temp, int8_t &now_power, bool &alert);//计算是否制冷加热,是否发送警告

	void rpt_ig(unsigned char* buff,uint8_t mask);

	Tp_cf(uint8_t cmd_code);
	~Tp_cf();

private:
	int8_t ht;//设定最高温度（制冷开启温度）
	int8_t cst;//制冷停止温度
	int8_t hst;//加温停止温度
	int8_t lt;//设定最低温度（加温开启温度）
	bool ig;//忽视
};

#endif


