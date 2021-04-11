#ifndef DELAY_H_
#define DELAY_H_

#include "msp.h"

#define FREQ_1_5MHZ CS_CTL0_DCORSEL_0
#define FREQ_3MHZ   CS_CTL0_DCORSEL_1
#define FREQ_6MHZ   CS_CTL0_DCORSEL_2
#define FREQ_12MHZ  CS_CTL0_DCORSEL_3
#define FREQ_24MHZ  CS_CTL0_DCORSEL_4

void setup_DCO(int freq);
void delay_us(uint32_t time);

#endif /* DELAY_H_ */
