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
#include "test.h"

#define NADA void

int my_time = 0x5957;

char text_string[] = "text, more text, and even more text!";

/// ## Assignment 1: (c)
///
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

/// ## Assignment 1: (d)
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

/// ## Assignment 1: (e)
///
/// Configures PORTd bits 11 to 5 into input mode.
///
/// According to the data sheet (page 3, https://ww1.microchip.com/downloads/en/DeviceDoc/60001120F.pdf)
/// setting TRISx bit to 1 configures it to input mode.
void init_buttons_and_switches(NADA)
{
    TRISD = 0x7F << 5;
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
    init_buttons_and_switches();
    clear_display();
}

/// ## Assignment 1: (h)
///
/// At this stage, we still haven't implemented the ticker from lab 2 which means we cannot update the clock
void time_updater(void)  {
    int sw = get_switch_values();
    int btn = get_button_values();
    char* time = "16:42";

    if (btn == 0b001) {
        time = "btn2";
        write_success_to_led();
    } else if (btn == 0b010) {
        time = "btn3";
        write_success_to_led();
    } else if (btn == 0b100) {
        time = "btn4";
        write_success_to_led();
    } 
    
    display_string(0, time);
    display_update();
}

/* This function is called repetitively from the main program */
void lab_work(void)
{
    time_updater();
}
