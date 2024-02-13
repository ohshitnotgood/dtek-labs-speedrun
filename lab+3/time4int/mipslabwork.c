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

int prime = 1234567;
int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

int timerCounter = 0;
/* Interrupt Service Routine */
void user_isr(void)
{
    if (check_t2Timer_timeout())
        timerCounter++;

    if (timerCounter == 10)
    {
        time2string(textstring, mytime);
        display_string(3, textstring);
        display_update();
        tick(&mytime);
        timerCounter = 0;
    }
}

/* Lab-specific initialization goes here */
void labinit(void)
{
    // enable interrupt in IEC(0). IEC(0) is T2IE (timer 2 interrupt enable flag)
    // IPC(2) contains T2IP (timer 2 interrupt priority control)
    IEC(0) = 0x1 << 8;
    /// Set priority
    IPC(2) == 0b111 << 26;;
    init_timer_2();
    enable_interrupt();
}

/* This function is called repetitively from the main program */
void labwork(void)
{
    prime = nextprime(prime);
    display_string(0, itoaconv(prime));
    display_update();
}
