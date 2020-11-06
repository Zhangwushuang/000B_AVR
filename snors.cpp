#include "snors.h"

Air_snor* const Snors::in_air(new Air_snor(IN_AR_PIN));  //内部
Air_snor* const Snors::out_air(new Air_snor(OUT_AR_PIN)); //外部

Wt_tp_snor* const Snors::wt_tp(new Wt_tp_snor(WT_TP_PIN)); //水温

Tank* const Snors::mn_tk(new Tank(MN_LV_ALT, MN_HP, MN_LP)); //主水箱水位
Tank* const Snors::hu_tk(new Tank(HU_LV_ALT, HU_HP, HU_LP)); //加湿器水位
Tank* const Snors::in_tk(new Tank(IN_LV_ALT, IN_HP, IN_LP)); //内部水位

void Snors::load_date_loop() {

	Snors::mn_tk->get_date(); //主水箱水位
	Snors::hu_tk->get_date(); //加湿器水位
	Snors::in_tk->get_date(); //内部水位

}

void Snors::load_date_report() {

	Snors::in_air->get_date();  //内部
	Snors::out_air->get_date(); //外部
	Snors::wt_tp->get_date(); //水温

}


