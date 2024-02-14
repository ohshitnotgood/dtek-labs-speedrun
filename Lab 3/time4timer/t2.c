#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/// ## Assignment 2: (b)
///
/// 
/// To initialise the timer, 
void init_timer_2(void) {
    disable_t2_timer();
    clear_t2_timer();
    set_t2_timer_scaling();
    enable_t2con();
    // T2CON = 0x0;
    // T2CON = 0x4070;


    // T2CON = 0;TMR2 = 0xffff;PR2 = (80000000/2560);T2CON = 0x8070;
}

/// According to the timers data sheet (page 9, https://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf)
/// setting bit 15 to 1 enables the T2 timer module.
void enable_t2con(void) {
    T2CON = 0x1 << 15 | T2CON;
}

/// According to the timers data sheet (page 9, https://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf)
/// setting bit 15 to 0 disables the T2 timer module.
void disable_t2_timer(void) {
    T2CON = 0x0 << 15;
}

/// Applies 1:8 scaling on the timer. This is done by setting 111 to bits <6::4> in T2CON.
///
/// We are using the timer in 16 bit mode 
///
/// For this assignment, the clock speed was set to 80MHz. This means every second, 1 million clock cycles are executed.
/// If we divide this by 1.000, this means it takes 100.000 clock cycles for the timer to timeout.
///
/// This would mean after every 100.000 timeouts, one second will have passed.
void set_t2_timer_scaling(void) {
    T2CONSET = 0x70;
    PR2 = ((80000000 / 256) / 10);
}

void start_t2_timer(void) {
    T2CON = 0b1 << 15 | T2CON;
}

void clear_t2_timer(void) {
    TMR2 = 0xffff;
}

/// Checks if T2CON timer has timed out.
///
/// If a timeout has occurred, the interrupt flag is automatically reset.
///
/// @returns 0 if timeout has not been reached.
/// @returns 1 if timeout HAS been reached.
int check_t2Timer_timeout(void) {
    if (IFS(0) & 0x100) {
        IFSCLR(0) = 0x100;
        return 1;
    }
    return 0;
}

/// According to the timers data sheet (page 9, https://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf)
/// bits, <6::4> are used for configuring the timer scale.
///
///
/// 
void configure_timer_preScale() {

}