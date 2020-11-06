#include "wt_temp_ac.h"

void Wt_temp_ac::cp_power(bool mn_lv_alt) {//如果缸体内部缺水,那么就不能调节水温

	if (mn_lv_alt) {
	
		this->power = 0;
	
	}

}

uint16_t Wt_temp_ac::report_state(unsigned char* buff) {

	buff[0] = this->power;

	if (this->cp->is_dl) {
	
		buff[11] = buff[11] + this->dl_alt_code;

	}

	return 1;

}

Wt_temp_ac::Wt_temp_ac(uint8_t tp, uint16_t dl) :Temp_ac(WT_TEMP_AC_CP, WT_TEMP_AC_HP, tp, dl, WT_TEMP_DL_ALT)
{



}

Wt_temp_ac::~Wt_temp_ac() {


}


