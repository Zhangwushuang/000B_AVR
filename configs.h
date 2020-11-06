#ifndef _CONFIGS_h
#define _CONFIGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//设置
#include "hdw_cf.h"
#include "humi_cf.h"
#include "in_fan_cf.h"
#include "lt_auto_cf.h"
#include "lt_man_cf.h"
#include "spray_cf.h"
#include "time_swich_cf.h"
#include "tp_cf.h"
#include "sht_cf.h"

class Configs
{

public:
	static Hdw_cf* const hdw;
	static Humi_cf* const humi;
	static In_fan_cf* const in_fan;
	static Lt_auto_cf* const lt_auto;
	static Lt_man_cf* const lt_man;

	static Spray_cf* const spray;
	static Time_swich_cf* const co2;
	static Time_swich_cf* const add_wt; //缸体内部是否需要加水
	static Tp_cf* const wt_tp;
	static Tp_cf* const ar_tp;
	static Sht_cf* const sht;

	static void load_all_config();//读取所有配置

};
#endif


