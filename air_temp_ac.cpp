#include "air_temp_ac.h"

uint16_t Air_temp_ac::report_state(unsigned char* buff) {

	buff[0] = this->power;

	if (this->cp->is_dl) {

		buff[12] = buff[12] + this->dl_alt_code;
		
	}

	return 1;

}

Air_temp_ac::Air_temp_ac(uint8_t tp, uint16_t dl) :Temp_ac(AR_TEMP_AC_CP, AR_TEMP_AC_HP, tp, dl, AR_TEMP_DL_ALT)
{



}

Air_temp_ac::~Air_temp_ac() {


}


