#ifndef _TANK_h
#define _TANK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "snor_base.h"

class Tank:
	public Snor_base
{
	//开关一律仰装，水位到达时开关断开，读到高电平,不装时也是高电平
 public:
	void get_date() override;
	uint16_t report_date(unsigned char* buff) override;

	bool need_add;//是否需要加水
	bool adding;//是否正在加水
	bool alt;//是否水位警告

	Tank(uint8_t code, uint8_t h_pin, uint8_t l_pin);
	~Tank();

private:
	uint8_t const alt_code;//alert的代号,不同位置水箱代号不同,通过位操作加在一起

	uint8_t const hp;//上开关pin
	uint8_t const lp;//下开关pin

};
#endif


