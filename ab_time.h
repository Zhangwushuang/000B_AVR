#ifndef _AB_TIME_h
#define _AB_TIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "clock.h"

class Ab_time
{
 public:
	
	static void get_ab_time();//计算异常持续时间(参数:是否异常,是否过去了1秒)
	static uint16_t report_ab(unsigned char* buff);//输出时间到报告

	static bool mn_tk_alt;//主水箱无水
	static bool ar_tp_alt; //气温异常
	static bool wt_tp_alt; //水温异常
	static bool hu_alt; //湿度异常

private:
	static uint32_t ab_timestamp;//异常发生的时间戳,归0则为正常
	static uint32_t ab_last;//异常持续的时间

};

#endif


