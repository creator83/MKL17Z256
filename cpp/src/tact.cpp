#include "tact.h"

uint8_t tact::cpu_clock;
uint8_t tact::bus_clock;

tact::tact ()
{
	
	cpu_clock = 48;
	bus_clock = 24;
	init_HIRC ();
}


void tact::init_HIRC ()
{
	/* SIM->SOPT2: USBSRC=0 */
	SIM->SOPT2 &= ~SIM_SOPT2_USBSRC_MASK; /* USB_CLKIN is clock source for USB FS  (applicable only for derivatived with USB)*/
	/* SIM->CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
	SIM_CLKDIV1_OUTDIV4(0x01); /* Set system prescalers */
	/* MCG->SC: FCRDIV=1 */
	MCG->SC = MCG_SC_FCRDIV(0x01);       /* LIRC1 divider not used - leave the default value*/
	/* MCG->MC: HIRC=1,LIRC_DIV2=0 */
	MCG->MC = MCG_MC_HIRCEN_MASK;    /* Enable HIRC clock source*/
	/* OSC0->CR: ERCLKEN=0,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	OSC0->CR = (uint32_t)0x00u;         /* Disable External reference */
	/* MCG->C2: RANGE0=0,HGO0=0,EREFS0=0,IRCS=1 */
	MCG->C2 = MCG_C2_IRCS_MASK;         /* Not used - leave default value */
	/* Switch to HIRC Mode */
	/* MCG->C1: CLKS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG->C1 = MCG_C1_CLKS(0x00) |
	MCG_C1_IRCLKEN_MASK;       /* Leave LIRC enabled and select HIRC as a clock source */
	while((MCG->S & MCG_S_CLKST_MASK) != 0x00u) ; /* Check that the clock source is the HIRC clock. */

}
