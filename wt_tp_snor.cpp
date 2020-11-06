#include "wt_tp_snor.h"

void Wt_tp_snor::get_date() {

	this->sensor->setResolution(this->adress, 9);//设置分辨率

	this->sensor->requestTemperatures();//发送探测温度的命令
	this->temp = this->sensor->getTempC(this->adress);//读取温度

}

void Wt_tp_snor::set_snor_Res() {

	this->sensor->begin();
	this->sensor->getAddress(this->adress, 0);//获取探头地址
	this->sensor->setResolution(this->adress, 9);//设置分辨率

}

uint16_t Wt_tp_snor::report_date(unsigned char* buff) {

	buff[0] = this->temp;
	return 1;

}

Wt_tp_snor::Wt_tp_snor(uint8_t one_wire_pin)
{
	
	this->poneWire = new OneWire(one_wire_pin);//申请一个单总线
	this->sensor = new DallasTemperature(this->poneWire);//启动一个探头

}

Wt_tp_snor::~Wt_tp_snor() {

	this->poneWire->~OneWire();
	this->sensor->~DallasTemperature();

}


