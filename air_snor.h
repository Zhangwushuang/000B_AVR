#ifndef _AIR_SNOR_h
#define _AIR_SNOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "clock.h"
#include "snor_base.h"
#include <DHT.h>

class Air_snor :
	public Snor_base
{
public:
	void get_date() override;
	uint16_t report_date(unsigned char* buff) override; //返回值为最开始连续字节的长度

	int8_t temp;//温度
	uint8_t humi;//湿度

	Air_snor(uint8_t pin);
	~Air_snor();

private:
	DHT* const dht;

};
#endif


