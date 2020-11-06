#ifndef _LT_AUTO_CF_h
#define _LT_AUTO_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"
#include "clock.h"

class Lt_auto_cf:
	public Config_base
{
public:

	int8_t check_input(unsigned char* buff) override;//检查输入的数据合法性
	void load_confi() override;//读取设置
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	void power_out(uint8_t &now_power, uint8_t &now_mode);//计算模式和灯光强度

	Lt_auto_cf(uint8_t cmd_code);
	~Lt_auto_cf();

private:
	uint8_t on_h;//开灯时
	uint8_t on_m;//开灯分
	uint8_t off_h;//关灯时
	uint8_t off_m;//关灯分

	uint32_t on_delay;//淡入时间
	uint32_t off_delay;//淡出时间

	uint8_t max;//自动模式最大值
	uint8_t mode;//0为白灯，1为色灯

	uint32_t on_ms;//开灯时在一天中的毫秒数
	uint32_t off_ms;//关灯时在一天中的毫秒数

	uint8_t on_power(uint32_t oned_ms);//开灯时计算渐变亮度
	uint8_t off_power(uint32_t offed_ms);//关灯时计算渐变亮度

};
#endif


