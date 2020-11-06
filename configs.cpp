#include "configs.h"

Hdw_cf*  const Configs::hdw(new Hdw_cf(HW_CF));
Humi_cf* const Configs::humi(new Humi_cf(HUMI_CF));
In_fan_cf* const Configs::in_fan(new In_fan_cf(IN_FAN_CF));
Lt_auto_cf* const Configs::lt_auto(new Lt_auto_cf(AUTO_LT_CF));
Lt_man_cf* const Configs::lt_man(new Lt_man_cf(MAN_LT_CF));

Spray_cf* const Configs::spray(new Spray_cf(SPRAY_CF));
Time_swich_cf* const Configs::co2(new Time_swich_cf(CO2_CF));
Time_swich_cf* const Configs::add_wt(new Time_swich_cf(WT_CIRCLE_CF));
Tp_cf* const Configs::wt_tp(new Tp_cf(WT_TP_CF));
Tp_cf* const Configs::ar_tp(new Tp_cf(AR_TP_CF));

Sht_cf* const Configs::sht(new Sht_cf(AT_ST_CF));

void Configs::load_all_config() {

	//硬件配置因为和生成act有关,所以已经先读取,而不是等到setup函数内调用

	Configs::humi->load_confi();
	Configs::in_fan->load_confi();
	Configs::lt_auto->load_confi();
	Configs::lt_man->load_confi();

	Configs::spray->load_confi();
	Configs::co2->load_confi();
	Configs::add_wt->load_confi();
	Configs::wt_tp->load_confi();

	Configs::ar_tp->load_confi();
	Configs::sht->load_confi();

}


