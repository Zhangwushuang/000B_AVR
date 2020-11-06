// sht_cf.h

#ifndef _SHT_CF_h
#define _SHT_CF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config_base.h"

class Sht_cf:
	public Config_base
{
 public:

	 uint32_t space;//���ʱ��
	 uint8_t mode;//0:������.1:������ʱ����.2:����ʱ�䶼����

	 int8_t check_input(unsigned char* buff) override;//�Ϸ��Լ��
	 void load_confi() override;//��ȡ����
	 uint16_t report_config(unsigned char* buff)  override;//������cp��report��buff

	 Sht_cf(uint8_t cmd_code);
	 ~Sht_cf();

};

#endif

