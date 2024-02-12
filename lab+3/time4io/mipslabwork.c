/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define NADA void

int my_time = 0x5957;

char text_string[] = "text, more text, and even more text!";

/// @brief
/// Initialises the LEDs.
///
///
/// According to the problem sheet, the LEDs are controlled by PORTe.
///
/// This function configures PORTe to be in output mode by setting 0 in TRISe.
void init_led(NADA)
{
    volatile int *TRISe = (volatile int *)0xbf886100;
    *TRISe = 0x00;
}

/// @brief
/// Stores the number to be displayed on the LEDs.
///
/// In Assignment 1, this variable is incremented.
int __c = 0b0;

/// @brief
/// According to the problem sheet, the LEDs are controlled by PORTe.
///
/// This function defines PORTe by address and sends a value to PORTe.
///
///
/// In assignment 1, this function is called every 'tick'.
void led_count(NADA)
{
    volatile int *PORTe = (volatile int *)0xbf886110;
    *PORTe = __c;
    __c++;
}

/* Interrupt Service Routine */
void user_isr(void)
{
    return;
}

/* Lab-specific initialization goes here */
void lab_init(void)
{
    init_led();
}

/* This function is called repetitively from the main program */
void lab_work(void)
{
    // delay(1000);
    //   time2string( text_string, my_time );
    display_string(3, text_string);
    display_update();
    quick_sleep(10000);
    led_count();
    //   tick( &my_time );
    display_image(96, icon);
}
