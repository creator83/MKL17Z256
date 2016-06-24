#include "MKL17Z4.h"
#include "gpio.h"
#include "tact.h"
#include "delay.h"

tact frq;
const char pin_t = 0;





void tpm1_init ();

int main()
{


  while (1)
  {

  }
}

void tpm1_init ()
{
	//settings pins
	gpio tpm_pin (gpio::B);
	//tpm_pin.setOutPin (pin_t. gpio::Alt3);
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;

	//
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK;

	TPM1->MOD = 121;
	TPM1->CONTROLS[0].CnV = 120;
	TPM1->SC |= TPM_SC_PS(7);
	TPM1->SC |= TPM_SC_CMOD(1);
}

