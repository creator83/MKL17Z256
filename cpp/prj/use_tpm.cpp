#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"
#include "tpm.h"

tact frq;
const char pin_t = 0;





void tpm1_init ();

int main()
{

	//tpm1_init ();
	//frq.set_LIRC_div (tact::LIRC_8, tact::div_1,tact::div_1);
	//tact tpm1, set_ch=0, frq timer = 2Mhz
	tpm tpm1_pwm (tpm::TPM_1, tpm::ch0, tpm::div4);

	//Set pwm frq=20kHz
	tpm1_pwm.Set_MOD (100);

	//Set duty
	tpm1_pwm.Set_CNV (0);

	tpm1_pwm.init_edge_pwm (tpm::B, tpm::Alt3, pin_t, tpm::high_pulse);
	tpm1_pwm.start ();

	while (1)
  {
	  for (uint8_t i=0;i<=100;i+=5)
	  {
		  tpm1_pwm.Set_CNV (i);
		  delay_ms(50);
	  }
	  for (uint8_t i=100;i>0;i-=5)
	  {
		  tpm1_pwm.Set_CNV (i);
		  delay_ms(50);
	  }
  }
}

void tpm1_init ()
{
	//settings pins
	gpio tpm_pin (gpio::B);
	tpm_pin.setOutPin(pin_t, gpio::Alt3);
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;
	//MCG->C2 &= ~MCG_C2_IRCS_MASK;
	MCG->SC = MCG_SC_FCRDIV(0);
	//
	/*TPM1->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK;
	TPM1->SC |= TPM_SC_PS(5);*/
	TPM1->SC |= TPM_SC_PS(0);
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	TPM1->MOD = 100;
	TPM1->CONTROLS[0].CnV =0;

	//start counter
	TPM1->SC |= TPM_SC_CMOD(1);
}

