#include "tact.h"

uint8_t tact::cpu_clock;
uint8_t tact::bus_clock;

tact::tact ()
{
	
	cpu_clock = 100;
	bus_clock = 50;
	init_PEE ();
}
/*
tact::tact (src_tact s)
{
  src = s;
  f_cpu = 48;
}*/

tact::tact (mode m, uint8_t frq)
{

}

void tact::init_FBE ()
{
	/*// If the internal load capacitors are being used, they should be selected
	// before enabling the oscillator. Application specific. 16 pF and 8 pF selected
	// in this example
	OSC_CR = OSC_CR_SC16P_MASK | OSC_CR_SC8P_MASK;*/
	// Enabling the oscillator for 8 MHz crystal
	// RANGE=1, should be set to match the frequency of the crystal being used
	// HGO=1, high gain is selected, provides better noise immunity but does draw
	// higher current
	// EREFS=1, enable the external oscillator
	// LP=0, low power mode not selected (not actually part of osc setup)
	// IRCS=0, slow internal ref clock selected (not actually part of osc setup)
	MCG->C2 = MCG_C2_EREFS0_MASK|MCG_C2_RANGE0(1)|MCG_C2_HGO0_MASK;
	/* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	MCG->C1 = MCG_C1_FRDIV(3)|MCG_C1_CLKS(2);
	// wait for oscillator to initialize
	while (!(MCG->S & MCG_S_OSCINIT0_MASK));

	// wait for Reference clock to switch to external reference
	while (MCG->S & MCG_S_IREFST_MASK);

	// Wait for MCGOUT to switch over to the external reference clock
	while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2);
	/* MCG->C4: DMX32=0,DRST_DRS=0 */
	MCG->C4 &= ~(MCG_C4_DRST_DRS(3)|MCG_C4_DMX32_MASK);
}

void tact::init_PBE (uint8_t div)
{
	// Now configure the PLL and move to PBE mode
	// set the PRDIV field to generate a 4 MHz reference clock (8 MHz /4)
	MCG->C5 = MCG_C5_PRDIV0(div);
}

void tact::init_PEE (uint8_t m)
{
	init_FBE ();
	init_PBE (3);
	// set up the SIM clock dividers BEFORE switching to the PLL to ensure the
	// system clock speeds are in spec.
	// core = PLL (100 MHz), bus = PLL/2 (50 MHz), flexbus = PLL/2 (50 MHz), flash = PLL/4 (25MHz)
	SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(1)
	| SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(3);
	// set the VDIV field to 0, which is x24, giving 4 x 24 = 96 MHz
	// the PLLS bit is set to enable the PLL
	// the clock monitor is enabled, CME=1 to cause a reset if crystal fails
	// LOLIE can be optionally set to enable the loss of lock interrupt
	MCG->C6 = MCG_C6_CME0_MASK| MCG_C6_PLLS_MASK|MCG_C6_VDIV0(m);
	// wait until the source of the PLLS clock has switched to the PLL
	while (!(MCG->S & MCG_S_PLLST_MASK));
	// wait until the PLL has achieved lock
	while (!(MCG->S & MCG_S_LOCK0_MASK));
	// Transition into PEE by setting CLKS to 0
	// previous MCG_C1 settings remain the same, just need to set CLKS to 0
	MCG->C1 &= ~MCG_C1_CLKS_MASK;
	// Wait for MCGOUT to switch over to the PLL
	while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3);
}


void tact::Set_frq (uint8_t frq)
{

  
}



