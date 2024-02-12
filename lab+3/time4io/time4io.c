#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/// Returns data from the switches.
///
/// Data from switches are, apparently, returned as 0s and 1s. 
///
/// Bits 11-8 store the data from the buttons.
/// 
/// This data is then shifted and filtered to return a 4 bit value. The 3 bits represent SW3, SW2, SW1 and 
/// SW0 from MSB to LSB
int get_switch_values(void) {
    return (PORTD >> 8) & 0x000F;
}

/// Returns the value returned by the buttons in the IO shield
///
///
/// Bits 7-5 store the data from the buttons.
///
/// Data from buttons are, apparently, returned as 0s and 1s. 
int get_button_values(void) {
    return PORTD >> 5 & 0x0007;
}