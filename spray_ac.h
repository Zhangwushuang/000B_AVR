#ifndef _SPRAY_AC_h
#define _SPRAY_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "configs.h"
#include "actuator_base.h"
#include "clock.h"

//均为常闭阀
#define SP_PUMP_PIN 32 //水泵控制pin dc-f

#define SP_TAP_PIN 28 //喷淋阀 dc-d
#define IN_TAP_PIN 24 //内部加水阀 dc-b
#define HU_TAP_PIN 26 //加湿器水箱加水阀 dc-c

class Spray_ac:
	public Actuator_base
{

 public:

	 bool need_sp;//是否需要喷淋(由时间判断获得)
	 bool need_in;//缸体内部是否需要加水(水箱浮子开关或定时加水设置)
	 bool need_hu;//加湿器水箱是否需要加水(水箱浮子开关获得)

	 bool mn_lv_alert;//主水箱水位是否不足(水箱浮子开关获得)
	 int64_t last_sp_time;//上次喷淋的时间戳(自 2000-1-1)

	 uint32_t get_sp_dist();//计算上次喷淋距现在时间,获取的值用于判断 need_sp及用于发送报告

	 uint16_t report_state(unsigned char* buff) override;//报告状态
	 void exce() override;//执行

	 Spray_ac();
	 ~Spray_ac();

private:
	
	uint32_t sp_distance;//距上次喷淋的时间
	bool spraying;//是否正在喷淋

	void close_all();//关闭所有电磁阀及水泵
	void open_spray();//打开喷淋
	void open_in();//缸补水
	void open_humi();//加湿器补水

};

#endif


