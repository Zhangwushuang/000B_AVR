#include "co2_ac.h"

uint16_t Co2_ac::report_state(unsigned char* buff) {

	buff[0] = this->need_co2;
	return 1;

}

void Co2_ac::exce() {

	if (this->need_co2) {

		digitalWrite(CO2_TAP_PIN, HIGH);

	}
	else
	{

		digitalWrite(CO2_TAP_PIN, LOW);

	}

}

Co2_ac::Co2_ac() {

	this->need_co2 = 0;
	pinMode(CO2_TAP_PIN, OUTPUT);
	digitalWrite(CO2_TAP_PIN, LOW);

}

Co2_ac::~Co2_ac() {


}


