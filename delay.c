#include "delay.h"
#include "msp.h"

void setup_DCO(int freq)
{
    CS->KEY   = CS_KEY_VAL;
    CS->CTL0  = freq;
    CS->CTL1 |= CS_CTL1_SELM__DCOCLK | CS_CTL1_DIVM__1; // MCLK = DCO_CLK (freq) / 1
    CS->CTL1 |= CS_CTL1_SELS__DCOCLK | CS_CTL1_DIVS__2; // SMCLK = DCO_CLK (freq) / 2
    CS->KEY   = 0;
}

void delay_us(uint32_t time){
    // Assumes DCO clk is in-use.
    // (time)(freq) = number of clock cycles needed

    // Grab bits related to CLK rate, from the CS->CTL0 register.
    uint32_t freqBitsMasked = (CS->CTL0 & CS_CTL0_DCORSEL_MASK);

    // Shift the bits so they are the least significant bits.
    // (This val is used to determine how many times 3 should be multiplied by 2)
    uint32_t freqBitsShifted = freqBitsMasked >> CS_CTL0_DCORSEL_OFS;

    // divide by 2, so 1.5 can become 3 by multiplication
    uint32_t cycles = (time >> 1) * (3 << freqBitsShifted);
    cycles >>= 2;

    if(time > 10000){
        cycles += 300*(freqBitsShifted)+100;
    }

    uint32_t i;
    for (i = 0; i < cycles; ++i){
        __delay_cycles(1);
    }
}
