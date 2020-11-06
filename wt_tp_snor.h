#ifndef _WT_TP_SNOR_h
#define _WT_TP_SNOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "snor_base.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Wt_tp_snor :
	public Snor_base
{

public:

	int8_t temp;//温度

	void get_date() override;
	uint16_t report_date(unsigned char* buff) override; //返回值为最开始连续字节的长度

	void set_snor_Res();//设置分辨率

	Wt_tp_snor(uint8_t one_wire_pin);
	~Wt_tp_snor();

private:
	DallasTemperature* sensor;//探头
	DeviceAddress adress;//水温探头的地址
	OneWire* poneWire;//总线

};
#endif


