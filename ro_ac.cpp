#include "ro_ac.h"

uint16_t Ro_ac::report_state(unsigned char* buff) {

	return 0;

}

void Ro_ac::exce() {

	if (this->need_add) {
	
		digitalWrite(RO_PUMP_PIN, HIGH);
	
	}
	else 
	{

		digitalWrite(RO_PUMP_PIN, LOW);
	
	}

}

Ro_ac::Ro_ac() {

	pinMode(RO_PUMP_PIN,OUTPUT);
	digitalWrite(RO_PUMP_PIN, LOW);

}

Ro_ac::~Ro_ac() {


}

