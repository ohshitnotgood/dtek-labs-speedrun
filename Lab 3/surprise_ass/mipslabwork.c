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

int check_external_interrupt(void) {
    if (IFS(0) >> 11 & 0x1) {
        IFSCLR(0) = 0x1 << 11;
        return 1;
    }
    return 0;
}


int get_switch_values(void) {
    return (PORTD >> 8) & 0x000F;
}

/* Interrupt Service Routine */
void user_isr(void)
{
    if (check_t2Timer_timeout()) {
        // display_string(0, "hello")
        timerCounter++;
    }

    if (check_external_interrupt()){
        mytime +=0x03;

    }

    // if (IFS(0) << 11 | 0x1) {
    //     int sw = get_switch_values();

    //     if (sw == 0x10)  {
    //         mytime = 0x1234;
    //         IFSCLR(0) = 0x1 << 11;
    //     }
    // }


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
    TRISD = 0x7F << 5;

    // enable interrupt in IEC(0). IEC(0) is T2IE (timer 2 interrupt enable flag)
    // IPC(2) contains T2IP (timer 2 interrupt priority control)
    IEC(0) = 0x1 << 11 | IEC(0);
    IEC(0) = 0x1 << 8 | IEC(0);
    /// Set priority
    IPC(2) = 0b111 << 2 | IPC(2);
    IPC(2) = 0b11 | IPC(2);

    // Set priority for INT2
    IPC(2) = 0b111 << 26 | IPC(2);
    IPC(2) = 0b11 << 24 | IPC(2);
    init_timer_2();
    enable_interrupt();
}

void enable_external_interrupts() {
    // Enable INT2IE in IEC0
    IEC(0) = 0x1 << 11 | IEC(0);

    // Check for interrupts in IFS0@<11>
    
}

/* This function is called repetitively from the main program */
void labwork(void)
{
    prime = nextprime(prime);
    display_string(0, itoaconv(prime));
    display_update();
}
