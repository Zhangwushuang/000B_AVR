// config_base.h

#ifndef _CONFIG_BASE_h
#define _CONFIG_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <stdint.h>
#include <EEPROM.h>

#define  CMD_LEN 32 //32字节

//命令标号 
#define  AR_TP_CF 0x01
#define  IN_FAN_CF 0x02
#define  SPRAY_CF 0x03
#define  AUTO_LT_CF 0x04
#define  CO2_CF 0x05
#define  WT_CIRCLE_CF 0x06
#define  WT_TP_CF 0x07
#define  HUMI_CF 0x08
#define  HW_CF 0x09
#define  MAN_LT_CF 0x0a
//0b 0c为修改序列号,仅simple wifi型具有
#define  AT_ST_CF 0x0d//自动拍摄设定

class Config_base
{

public:
	bool save_confi(unsigned char* buff);//保存设置,buff*为cmd保存的缓存（不包含头部两个字节）


	virtual int8_t check_input(unsigned char* buff);//不包含头部两个字节的长度
	virtual void load_confi() = 0;//读取设置
	virtual uint16_t report_config(unsigned char* buff) = 0;//将设置cp进buff,返回值为最开始连续字节的长度

	Config_base(uint8_t cmd_code);
	~Config_base();

protected:
	uint16_t const begin;//epprom开始的字节数

};

#endif


