#ifndef _SNOR_h
#define _SNOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Snor_base
{

 public:

	virtual void get_date() = 0;//读取数据
	virtual uint16_t report_date(unsigned char* buff) = 0;//发送数据到buff

};
#endif


