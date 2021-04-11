#include "delay.h"
#include "LCD.h"
#include "msp.h"

void Clear_LCD();
void Home_LCD();
void Second_Line_LCD();
void Write_char_LCD(char c);
void Write_string_LCD(char * s, int length);
void Initialization();

// BIT ORDER
// 0b00000000
// Bits 7-4 <- Data Pins D7 - D4
// Bit 3 <- X
// Bit 2 <- Enable
// Bit 1 <- Read/Write Pin
// Bit 0 <- RS Pin

void send_command(char A)
{
    P4->OUT = A;
    delay_us(100);
    P4->OUT |= BIT2;
    delay_us(100);
    P4->OUT &= ~BIT2;
    delay_us(100);
}

void Clear_LCD()
{
    send_command(0b00000000);
    send_command(0b00010000);
    delay_us(2000);
}

void Home_LCD()
{
    send_command(0b00000000);
    send_command(0b00100000);
    delay_us(2000);
}

void Second_Line_LCD()
{
    send_command(0b11000000);
    send_command(0b00000000);
    delay_us(2000);
}

void Initialization()
{
    // Initial 4-Bit Operation Function Set
    send_command(0b00100000);

    // 4-Bit Operation and 2-Line/5x8 Font
    send_command(0b00100000);
    send_command(0b10000000);

    // Display on/off control
    send_command(0b00000000);
    send_command(0b11110000);

    // Entry Mode Set
    send_command(0b00000000);
    send_command(0b01100000);

    Clear_LCD();
}

void Write_char_LCD(char c)
{
    char first_half = (c & 0xf0) + 0b0001;
    char second_half = ((c & 0x0f) << 4) + 0b0001;

    send_command(first_half);
    send_command(second_half);
}

void Write_string_LCD(char * s, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        Write_char_LCD(s[i]);
    }
}
