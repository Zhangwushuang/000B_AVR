#include "ab_time.h"

bool Ab_time::mn_tk_alt = false;//主水箱无水
bool Ab_time::ar_tp_alt = false; //气温异常
bool Ab_time::wt_tp_alt = false; //水温异常
bool Ab_time::hu_alt = false; //湿度异常

uint32_t Ab_time::ab_timestamp = 0;
uint32_t Ab_time::ab_last = 0;

void Ab_time::get_ab_time() {

	bool is_ab = Ab_time::mn_tk_alt || Ab_time::ar_tp_alt || Ab_time::wt_tp_alt || Ab_time::hu_alt;
    
	if (!is_ab) { //如果正常

		Ab_time::ab_timestamp = 0;
		Ab_time::ab_last = 0;
		return;

	}

	if (Ab_time::ab_timestamp == 0 && is_ab) {//如果第一次检测到异常

		Ab_time::ab_timestamp = Clock::timestamp_2000;//记录时间戳
		Ab_time::ab_last = 1;//持续时间为1
		return;

	}

	if (!Clock::rpt_flag) {//只有report时,才计算持续时间
	
		return;

	}

	//防止对时后混乱
	if (Ab_time::ab_timestamp > Clock::timestamp_2000) {

		Ab_time::ab_timestamp = Clock::timestamp_2000;

	}

	Ab_time::ab_last = Clock::timestamp_2000 - Ab_time::ab_timestamp;

}

uint16_t Ab_time::report_ab(unsigned char* buff) {

	*((uint32_t*)buff) = Ab_time::ab_last;
	return 4;

}


