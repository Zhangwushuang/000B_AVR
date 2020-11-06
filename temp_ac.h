#ifndef _TEMP_AC_h
#define _TEMP_AC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actuator_base.h"

#define COOL_ONLY 0 //单冷
#define HEAT_ONLY 1 //单热
#define TEC 2 //制冷片
#define CMP_ELE 3 //压缩机+电热
#define CMP_TAP 4 //压缩机+四通阀


class compressor 
{

public: 

	bool is_dl;//是否处于延时保护状态

	bool turn_on();//开机
	bool turn_off();//关机

	compressor(uint8_t cp,uint16_t delay);
	~compressor();

private:
	uint8_t const pin;//控制引脚
	uint32_t const delay_ms;//延时,单位毫秒

	bool is_on;//压缩机是否开机
	uint32_t off_ms;//压缩机关闭的millis

	void get_dl_sta();//获取压缩机保护状态

};

class Temp_ac :
	public Actuator_base
{
public:
	/*w唯一不同的是power的配置,水温依赖下水箱水位,判断制冷加热,气温根据加湿器水箱状态,判断加热*/
	int8_t power;//制冷加热状态,首先从设定获取,然后根据水位延时等情况修改

	virtual uint16_t report_state(unsigned char* buff) = 0;//报告状态

	void type_ad();//根据温控器类型调节power
	void exce() override;//执行

	Temp_ac(uint8_t c_pin, uint8_t h_pin, uint8_t tp , uint16_t dl, uint8_t dl_code);
	~Temp_ac();

protected:
	compressor* const cp;//压缩机
	uint8_t const dl_alt_code;//警告码,用于位运算发送报告

private:
	uint8_t const hp;//加热pin
	uint8_t const type;//类型

	void heat();//加热(动作根据类型选择)
	void cool();//制冷(制冷时动作是一样的)
	void stop();//停止
};
#endif

