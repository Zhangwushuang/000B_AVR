// snors.h

#ifndef _SNORS_h
#define _SNORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "air_snor.h"
#include "wt_tp_snor.h"
#include "tank.h"

#define IN_AR_PIN 40
#define OUT_AR_PIN 42
#define WT_TP_PIN 38

#define IN_LV_ALT 1
#define MN_LV_ALT 2
#define HU_LV_ALT 4

#define MN_HP  41
#define MN_LP  39

#define IN_HP  47
#define IN_LP  45

#define HU_HP  53
#define HU_LP  51

class Snors
{
 public:
	static Air_snor* const in_air;  //内部
	static Air_snor* const out_air; //外部

	static Wt_tp_snor* const wt_tp; //水温

	static Tank* const mn_tk; //主水箱水位
	static Tank* const hu_tk; //加湿器水位
	static Tank* const in_tk; //内部水位

	static void load_date_loop();//每次循环读取水箱数据
	static void load_date_report();//每次15秒读取温湿度数据

};

#endif


