/*
 * Keypad.c
 *
 *  Created on: Apr 9, 2021
 *      Author: Daniel
 */

#include "msp.h"
#include "delay.h"

int detect_keypress()
{
    P5->OUT |= 0x07;
    if (P2->IN & BIT7) {
        return 0;
    }
    else if (P2->IN & BIT6) {
        return 1;
    }
    else if (P2->IN & BIT5) {
        return 2;
    }
    else if (P2->IN & BIT4) {
        return 3;
    }
    else {
        return 4;
    }
}

char cycle()
{
    // 1  2  3
    // 4  5  6
    // 7  8  9
    // *  0  #
    int row = 4;
    char arr[12] = {'1', '4', '7', '*', '2', '5', '8', '0', '3', '6', '9', '#'};

    row = detect_keypress();
    if (row != 4) {
        P5->OUT |= BIT0;
        P5->OUT &= ~(BIT1 | BIT2);
        if (P2->IN & 0xf0) {
            return arr[row];
        }

        P5->OUT |= BIT1;
        P5->OUT &= ~(BIT2 | BIT0);
        if (P2->IN & 0xf0) {
            return arr[4 + row];
        }

        P5->OUT |= BIT2;
        P5->OUT &= ~(BIT1 | BIT0);
        if (P2->IN & 0xf0) {
            return arr[8 + row];
        }
    }
    return '-';
    // arr[col*4 + row];
}


