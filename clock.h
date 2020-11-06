#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <int64_DS3231.h>

#define RPT_SEND_SPACE 15

class Clock
{

public:

	static int64_DS3231* const rtc;//时钟模块

	static uint32_t now_sec; //今天的秒数
	static uint16_t now_ms; //现在在这一秒中的毫秒数
	static int64_t timestamp_2000;//自2000年1月1日以来的秒数

	static void begin();//初始化时钟和wire,并设置中断
	static void get_time();//获取时间信息,返回值为此次是否过去了1秒
	static uint16_t report_time(unsigned char* buff);//输出时间到报告

	static bool rpt_flag;//是否需要发送报告
	static bool pass_flag;//是否过去了1秒,用于计算时

	static int8_t get_IC_temp();//获取芯片温度

	static void set_flag();

private:
	static DateTime* const now_data;

	static uint32_t int_millis;//中断时的时间戳,用于计算毫秒数
	static volatile bool flag;//中断时设置为true,读取RTC并将ms归0后设置回false

	static int64_t rpt_send_time;//上次发送报告的时间

};

#endif


