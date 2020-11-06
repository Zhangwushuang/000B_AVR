#ifndef _CTRLOR_h
#define _CTRLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//状态
#include "Ab_time.h"

//时间
#include "clock.h"
#include "configs.h"
#include "snors.h"
#include "actors.h"

class Ctrlor
{
public:
	static void adjust_lt(bool imme = false);//计算并调节灯光(每loop)
	static void adjust_all();//计算并调节灯光以外(每中断)

	static void creat_rpt(unsigned char* rpt_buff);//创建报告(178字节，不含开头的编号和来源)

	//-----以下在收到命令时使用
	static void adjust_ar();//调节空气（温度、湿度及通风,因为耦合，合并调节）

	static void adjust_co2();//计算co2
	static void adjust_ro();//计算ro
	static void adjust_spray();//计算喷淋、内部加水、加湿器加水

	static void adjust_wt_tp();//计算水温控制
};
#endif


