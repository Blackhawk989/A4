#include "msp.h"
#include "delay.h"
#include "LCD.h"
#include "Keypad.h"

int main(void) {
    P2->SEL1 &= ~0xf0;
    P2->SEL0 &= ~0xf0;
    P2->DIR  &= ~0xf0;
    P2->REN  |= 0xf0;
    P2->OUT  &= ~0xf0;

    P5->SEL1 &= ~0x07;
    P5->SEL0 &= ~0x07;
    P5->DIR  |= 0x07;

    P4->SEL1 &= ~0xff;
    P4->SEL0 &= ~0xff;
    P4->DIR  |= 0xff;

    delay_us(500000);
    Initialization();

    Clear_LCD();
    Home_LCD();

    Write_string_LCD("Keypad: ", 8);
    char c;

    while(1)
    {
        c = cycle();
        if (c != '-')
        {
            Write_char_LCD(c);
            delay_us(100000);
        }

    }
}
