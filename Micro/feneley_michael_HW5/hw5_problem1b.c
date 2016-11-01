////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        ADC Glyph Example
//
// File name:       ADC_Glyph_Ex_main - A simple demonstration of a
//                  user-defined character
//
// Description:     Can be modified to draw other characters!
//
// How to use:      A logic analyzer can be used to see
//                  exactly what is happening in the ISR and the OLED
//                  update (header JB, pins 1, 2, and 3).
//
// Notes:           Note that the function "OledPutChar()" is the "public"
//                  function that calls an internal function "OledDrawGlyph()".
//                  You can call the latter, but the compiler will complain
//                  about it being implicitly defined (as it is does not have
//                  a prototype in the "OledChar.h" header file). You can use
//                  this function (it seems to be about twice as fast), but
//                  note that one must then explicitly call "OledUpdate()."
//                  One disadvantage of calling "OledPutChar()" is that the
//                  screen "flashes" when one erases something and redraws it
//                  (as with this example).
//
// Written by:      PEP
// Last modified:   20 October 2015

// Comment this define out to *not* use the OledDrawGlyph() function
#define USE_OLED_DRAW_GLYPH

#ifdef USE_OLED_DRAW_GLYPH
// forward declaration of OledDrawGlyph() to satisfy the compiler
void OledDrawGlyph(char ch);
#endif

#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"

// Configure the microcontroller
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_8         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF           // Debugger Disabled for Starter Kit

// Intrumentation for the logic analyzer (or oscilliscope)
#define MASK_DBG1  0x1;
#define MASK_DBG2  0x2;
#define MASK_DBG3  0x4;
#define DBG_ON(a)  LATESET = a
#define DBG_OFF(a) LATECLR = a
#define DBG_INIT() TRISECLR = 0x7

// Return value check macro
#define CHECK_RET_VALUE(a) { \
  if (a == 0) { \
    LATGSET = 0xF << 12; \
    return(EXIT_FAILURE) ; \
  } \
}

// Global variable to count number of times in timer2 ISR
unsigned int timer2_ms_value = 0;

// Global definitions of our user-defined characters
BYTE diamond[8] = {0xff, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x18};
char diamond_char = 0x00;
BYTE blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char blank_char = 0x01;

BYTE pumpkin[8] = {0x00, 0xe6, 0x84, 0x90, 0x90, 0x86, 0xe4, 0x00};
char pumpkin_char = 0x02;

// The interrupt handler for timer2
// IPL4 medium interrupt priority
// SOFT|AUTO|SRS refers to the shadow register use
void __ISR(_TIMER_2_VECTOR, IPL4AUTO) _Timer2Handler(void) {
    DBG_ON(MASK_DBG1);
    timer2_ms_value++; // Increment the millisecond counter.
    DBG_OFF(MASK_DBG1);
    INTClearFlag(INT_T2); // Acknowledge the interrupt source by clearing its flag.
}

// Initialize timer2 and set up the interrupts

void initTimer2() {
    // Configure Timer 2 to request a real-time interrupt once per millisecond.
    // The period of Timer 2 is (16 * 625)/(10 MHz) = 1 s.
    OpenTimer2(T2_ON | T2_IDLE_CON | T2_SOURCE_INT | T2_PS_1_16 | T2_GATE_OFF, 624);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTClearFlag(INT_T2);
    INTEnable(INT_T2, INT_ENABLED);
}

int main() {
    char oledstring[17];
    unsigned int timer2_ms_value_save;
    unsigned int last_oled_update = 0;
    unsigned int ms_since_last_oled_update;
    unsigned int glyph_pos_x = 0, glyph_pos_y = 2;
    int retValue = 0;

    // Initialize GPIO for LEDs
    TRISGCLR = 0xf000; // For LEDs: configure PortG pins for output
    ODCGCLR = 0xf000; // For LEDs: configure as normal output (not open drain)
    LATGCLR = 0xf000; // Initialize LEDs to 0000

    // Initialize Timer1 and OLED for display
    DelayInit();
    OledInit();

    // Set up our user-defined characters for the OLED
    retValue = OledDefUserChar(blank_char, blank);
    CHECK_RET_VALUE(retValue);
    retValue = OledDefUserChar(diamond_char, diamond);
    CHECK_RET_VALUE(retValue);
    retValue = OledDefUserChar(pumpkin_char, pumpkin);
    CHECK_RET_VALUE(retValue);

    // Initialize GPIO for debugging
    DBG_INIT();

    // Initial Timer2
    initTimer2();

    // Configure the system for vectored interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Enable the interrupt controller
    INTEnableInterrupts();

    // Send a welcome message to the OLED display
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("Glyph Example");
    OledUpdate();



    while (1) {
        ms_since_last_oled_update = timer2_ms_value - last_oled_update;
        if (ms_since_last_oled_update >= 100) {
            DBG_ON(MASK_DBG2);
            LATGSET = 1 << 12; // Turn LED1 on
            timer2_ms_value_save = timer2_ms_value;
            last_oled_update = timer2_ms_value;
            sprintf(oledstring, "T2 Val: %6d", timer2_ms_value_save / 100);
            OledSetCursor(0, 1);
            OledPutString(oledstring);
            DBG_OFF(MASK_DBG2);
            DBG_ON(MASK_DBG3);
            OledSetCursor(glyph_pos_x, glyph_pos_y);
#ifdef USE_OLED_DRAW_GLYPH
            OledDrawGlyph(blank_char);
#else
            OledPutChar(blank_char);
#endif
            // Update the glyph position
            glyph_pos_x++;
            if (glyph_pos_x > 15) {
                glyph_pos_x = 0;
                glyph_pos_y++;
                if (glyph_pos_y > 3) {
                    glyph_pos_y = 2;
                }
            }
            OledSetCursor(glyph_pos_x, glyph_pos_y);
#ifdef USE_OLED_DRAW_GLYPH
            OledDrawGlyph(pumpkin_char);
            OledUpdate();
#else
            OledPutChar(pumpkin_char);
#endif
            DBG_OFF(MASK_DBG3);
            LATGCLR = 1 << 12; // Turn LED1 off
        }
    }
    return (EXIT_SUCCESS);
}
