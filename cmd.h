#ifndef _CMD_h
#define _CMD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ctrlor.h"
#include "HardwareSerial.h"

#define SHOOT_UPLOAD 0xFE
#define SPRAY_MAN_CD 0xFD
#define CHK_TIME_CD 0xFB
#define RPT_LEN 180//包含头部的报告总长度

class Cmd
{
public:
	static void snd_rpt(HardwareSerial* port, bool is_cmd = true);//第二个参数 是否被动回复命令(被动时使用解析出的code和from)

	static bool rec_cmd(HardwareSerial* port);//接受命令
	static void exec_cmd(bool lc = false);//执行命令(参数为是否为调试口)

private:
	static unsigned char cmd_buff[128];
	static unsigned char rpt_buff[RPT_LEN];

	static uint8_t code;//代码
	static int8_t from;//来源

};

#endif


