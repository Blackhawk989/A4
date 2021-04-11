#ifndef LCD_H_
#define LCD_H_

#include "msp.h"

void Clear_LCD();
void Home_LCD();
void Second_Line_LCD();
void Write_char_LCD(char c);
void Write_string_LCD(char * s, int length);
void Initialization();

#endif /* LCD_H_ */
