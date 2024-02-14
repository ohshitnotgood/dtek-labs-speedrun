/// @brief Writes 11111111 (eight 1s in a row) to signify success of a task.
void write_success_to_led(void) {
    volatile int *TRISe = (volatile int *)0xbf886100;
    *TRISe = 0x00;
    volatile int *PORTe = (volatile int *)0xbf886110;
    *PORTe = 0xFF;
}

/// @brief Writes 10101010 (1s and 0s in alternating pattern) to signify failure of a process.
void write_fail_to_led(void) {
    volatile int *TRISe = (volatile int *)0xbf886100;
    *TRISe = 0x00;
    volatile int *PORTe = (volatile int *)0xbf886110;
    *PORTe = 0xAA;
}