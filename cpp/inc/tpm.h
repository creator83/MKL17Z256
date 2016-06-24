#include "MKL17Z4.h"
#include "tact.h"



#ifndef TPM_H
#define TPM_H


class tpm
{
  //variables
public:
	enum channel {ch0, ch1, ch2, ch3, ch4, ch5};
	enum N_TPM {TPM_0, TPM_1,TPM_2};
	enum mode_clock {TPM_disable, TPM_inc, TPM_ext};
	enum MODE {Input, Output_toggle, Output_pulse, Edge_Pwm, Center_Pwm, Software_compare};
	enum division {div1, div2, div4, div8, div16, div32, div64, div128};
	enum mode {khz, hz, ms, us};
private:
	uint8_t n_ch;

public:
	tpm(channel ch, uint16_t n, mode m = ms);
	void clear_flag ();
private:
	void khz_set (uint16_t val);
	void hz_set (uint16_t val);
	void ms_set (uint16_t val);
	void us_set (uint16_t val);
};

#endif /* PIT_H */
