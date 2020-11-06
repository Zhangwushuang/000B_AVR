#ifndef _LT_MAN_CF_h
#define _LT_MAN_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"
#include "clock.h"

class Lt_man_cf :
	public Config_base
{
public:

	uint32_t  time_left;//手动灯光模式剩下的时间（留驻内存,此值为0时为自动模式）
	uint8_t max;//手动模式灯光亮度
	uint8_t mode;//0为白灯，1为色灯

	bool power_out(uint8_t &now_power, uint8_t &now_mode, bool imme);//计算模式和灯光强度

	int8_t check_input(unsigned char* buff) override;
	void load_confi() override;//读取配置（亮度和模式）
	uint16_t report_config(unsigned char* buff)  override;//将设置cp进report的buff

	void set_shoot_tp(unsigned char* buff);//设置临时开灯的时间戳

	Lt_man_cf(uint8_t cmd_code);
	~Lt_man_cf();

private:
	uint32_t get_time_left(bool is_cmd);//计算倒计时(cmd时将马上重新计时,不再等到下一秒)

	uint32_t tar_stamp;//目标时间戳
	uint32_t lt_tp;//拍摄临时开灯的目标时间戳(由shoot命令确定)

};

#endif


