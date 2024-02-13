/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
    return;
}

/* Lab-specific initialization goes here */
void lab_init(void)
{
    // enable interrupt in IEC(0). IEC(0) is T2IE (timer 2 interrupt enable flag)
    // IPC(2) contains T2IP (timer 2 interrupt priority control)


    /// Enables interrupt
    IEC(0) = 0x1 << 8;

    /// Set priority
    IPC(2) == 0b111 << 26;
    init_timer_2();
}

int timerCounter = 0;
int timerFalse = 0;
/* This function is called repetitively from the main program */
void lab_work(void)
{
    if (check_t2Timer_timeout())
        timerCounter++;

    if (timerCounter == 3125)
    {
        time2string(textstring, mytime);
        display_string(3, textstring);
        display_update();
        tick(&mytime);
        timerCounter = 0;
    }
}
