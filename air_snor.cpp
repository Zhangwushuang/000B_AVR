#include "air_snor.h"

void Air_snor::get_date() {

	this->temp = dht->readTemperature();
	this->humi = dht->readHumidity();
	
}

uint16_t Air_snor::report_date(unsigned char* buff) {

	buff[0] = this->temp;
	buff[1] = this->humi;

	return 2;

}

Air_snor::Air_snor(uint8_t pin):dht(new DHT(pin, DHT22))
{

	dht->begin();

}

Air_snor::~Air_snor() {

	delete this->dht;

}


