#include "MKL17Z4.h"                    // Device header
#include "gpio.h"
#include "delay.h"
#include "pit.h"
#include "tact.h"
#include "segled.h"
#include "max6675.h"

tact frq;
const char led = 0;
gpio D(gpio::D);
pit del(pit::ch0, 1, pit::ms);
segled indicator(segled::B);
const char adc_ch = 4;


void init_adc ();
uint16_t conv_adc(uint8_t pin);

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;


extern "C"
{
	void PIT_IRQHandler();
}

void PIT_IRQHandler()
{
	del.clear_flag();
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}

}

uint16_t result [4];

int main()
{
	uint16_t abs_result;
	D.setOutPin(led);
	init_adc ();


	while (1)
	{
		indicator.get_buffer (conv_adc(adc_ch));
		delay_ms(200);
	}
}

void init_adc ()
{
	//tact ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	//Set busclock
	ADC0->CFG1 &= ~ADC_CFG1_ADICLK_MASK;
	//Set divider - 8
	ADC0->CFG1 |= ADC_CFG1_ADIV(3);
	ADC0->SC3 |= ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(3);
	ADC0->SC2 &= ~ ADC_SC2_ADTRG_MASK;
	ADC0->SC3 |= ADC_SC3_CAL_MASK ;
	while (!(ADC0->SC1[0]&ADC_SC1_COCO_MASK));

	ADC0->CFG1|= ADC_CFG1_ADLSMP_MASK|ADC_CFG1_MODE(0);

}

uint16_t conv_adc(uint8_t pin)
{
	//Select 4 channal and start conversation
	ADC0->SC1[0] |= ADC_SC1_ADCH(pin);
	while (!(ADC0->SC1[0]&ADC_SC1_COCO_MASK));
	uint16_t result = ADC0->R[0];
	return result;
}