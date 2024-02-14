a) Two/three buttons pressed at the same time. Nothing happens because the checks for button presses are hardcoded. No if clause is executed (or in assembly language, no branch is taken).

b) TRISE is the general register, TRISESET can only be written to to write stuff in TRISE register, TRISECLR can be written to to set bits in TRISE to 0.

c) Registers v0 and v1 which are used by MIPS to store return values from procedures.

d) Check reference sheets for the chip kit board and the IO sheild. For instance, if a pin is marked as RF1 in the chip kit data sheet, then that means we need to access PORTF pin 1.
