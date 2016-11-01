////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        HW5
//
// File name:       ADC_Example_main - A simple demonstration of the ADC
// Description:     Samples and displays the right and left movement of a stick
// Resources:       timer2 is configured to interrupt every 1.0ms.
//                  ADC is configuered to sample from two channels, AN2 and AN3.
//                  The information is stored in two seperate buffers.

//                  Connections:   Use JA-1
//                                 Red = L/R+
//                                 Black = Ground
//                                 Yellow = U/D+
//                                 Green = U/D
//                                 Brown = L/R

// Note: I wasn't exactly sure if you wanted to display LEFT, RIGHT, UP or DOWN
//       whenever the joystick was in that area, or only when it was being
//       actively moved in that direction. I chose to do the latter because it
//       was more difficult. LEFT, RIGHT, UP or DOWN only lights up if it is
//       being moved in that direction, not when it is returning to center or
//       not moving in the LEFT, RIGHT, UP, or DOWN

//       This homework meets all requirements.
// Written by:      Michael Feneley
// Last modified:   28 October 2015

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

// Definitions for the ADC averaging. How many samples (should be a power
// of 2, and the log2 of this number to be able to shift right instead of
// divide to get the average.
#define NUM_ADC_SAMPLES 32
#define LOG2_NUM_ADC_SAMPLES 5

// Global variable to count number of times in timer2 ISR
unsigned long timer2_ms_value = 0;

// Position and position signal variables
int x, y;
int prev_x, prev_y;
int left, right, up, down;

// The interrupt handler for the ADC
// IPL7 highest interrupt priority
// Takes the average to eliminate noise.
// Sets signal so OLED sets appropriate movement lights
void __ISR(_ADC_VECTOR, IPL7SRS) _ADCHandler(void) {
    static unsigned int current_reading = 0;
    unsigned int i;
    int x_total = 0;
    int y_total = 0;
    static unsigned int left_right[NUM_ADC_SAMPLES];
    static unsigned int up_down[NUM_ADC_SAMPLES];

    // Get current values
    int buff = ReadActiveBufferADC10();
    if(buff == 0) {
        left_right[current_reading] = ReadADC10(8);
        up_down[current_reading] = ReadADC10(9);
    } else if(buff == 1) {
        left_right[current_reading] = ReadADC10(0);
        up_down[current_reading] = ReadADC10(1);
    }

    // Update counter and calculate average to stabalize value.
    current_reading++;
    if (current_reading == NUM_ADC_SAMPLES) {
        current_reading = 0;

        for (i = 0; i < NUM_ADC_SAMPLES; i++) {
            y_total += up_down[i];
            x_total += left_right[i];
        }

        // Divide to get average
        int x_holder = x_total >> LOG2_NUM_ADC_SAMPLES;
        int y_holder = y_total >> LOG2_NUM_ADC_SAMPLES;

        // Check difference to correct for unwanted noise.
        if(abs(x_holder - x) > 2) {

            // Check if the joystick is being moved to either left or right.
            if(x <= 500 && x_holder < x) {
                left = 1;
                right = 0;
            } else if (x >=530 && x_holder > x) {
                right = 1;
                left = 0;
            }
            x = x_holder;
        }

        // Check difference to correct for unwanted noise.
        if(abs(y_holder - y) > 2) {
            // Check if the joystick is being moved to either left or right.
            if(y <= 500 && y_holder < y) {
                down = 1;
                up = 0;
            } else if (y >=530 && y_holder > y) {
                up = 1;
                down = 0;
            }
            y = y_holder;
        }
    }
    
    INTClearFlag(INT_AD1);
}

// The interrupt handler for timer2
// IPL4 medium interrupt priority
// SOFT|AUTO|SRS refers to the shadow register use
void __ISR(_TIMER_2_VECTOR, IPL4AUTO) _Timer2Handler(void) {
    timer2_ms_value++; // Increment the millisecond counter;
    seconds = timer2_ms_value / 1000;
    INTClearFlag(INT_T2); // Acknowledge the interrupt source by clearing its flag.
}

//***********************************************
//* IMPORTANT: THE ADC CONFIGURATION SETTINGS!! *
//***********************************************

// ADC MUX Configuration
// Using MUXA AND MUXB, as positive input, VREFL as negative input
#define AD_MUX_CONFIG ADC_CH0_POS_SAMPLEA_AN2 | ADC_CH0_NEG_SAMPLEA_NVREF | \
                      ADC_CH0_POS_SAMPLEB_AN3 | ADC_CH0_NEG_SAMPLEB_NVREF
// ADC Config1 settings
// Data stored as 16 bit unsigned int
// Internal clock used to start conversion
// ADC auto sampling (sampling begins immediately following conversion)
#define AD_CONFIG1 ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

// ADC Config2 settings
// Using internal (VDD and VSS) as reference voltages
// Do not scan inputs
// Two samples per interrupt
// Uses two 16 bit buffers
// Alternate sample mode off (use just MUXA)
#define AD_CONFIG2 ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_OFFSET_CAL_DISABLE \
                   | ADC_SAMPLES_PER_INT_2 | ADC_BUF_16 | ADC_ALT_INPUT_ON \
                   | ADC_ALT_BUF_ON


// ADC Config3 settings
// Autosample time in TAD = 8
// Prescaler for TAD:  the 20 here corresponds to a
// ADCS value of 0x27 or 39 decimal => (39 + 1) * 2 * TPB = 8.0us = TAD
// NB: Time for an AD conversion is thus, 8 TAD for aquisition +
//     12 TAD for conversion = (8+12)*TAD = 20*8.0us = 160us.
#define AD_CONFIG3 ADC_SAMPLE_TIME_15 | ADC_CONV_CLK_20Tcy

// ADC Port Configuration (PCFG)
// Not scanning, so nothing need be set here..

#define AD_CONFIGPORT ENABLE_AN2_ANA | ENABLE_AN3_ANA


// ADC Input scan select (CSSL) -- skip scanning as not in scan mode
#define AD_CONFIGSCAN SKIP_SCAN_ALL

// Initialize the ADC using my definitions
// Set up ADC interrupts
void initADC(void) {

    // Configure and enable the ADC HW
    SetChanADC10(AD_MUX_CONFIG);
    OpenADC10(AD_CONFIG1, AD_CONFIG2, AD_CONFIG3, AD_CONFIGPORT, AD_CONFIGSCAN);
    EnableADC10();

    // Set up, clear, and enable ADC interrupts
    INTSetVectorPriority(INT_ADC_VECTOR, INT_PRIORITY_LEVEL_7);
    INTClearFlag(INT_AD1);
    INTEnable(INT_AD1, INT_ENABLED);
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
    unsigned long last_oled_update = 0;
    unsigned long ms_since_last_oled_update;

    // Initialize GPIO for LEDs
    TRISGCLR = 0xf000; // For LEDs: configure PortG pins for output
    ODCGCLR = 0xf000; // For LEDs: configure as normal output (not open drain)
    LATGCLR = 0xf000; // Initialize LEDs to 0000

    // Set U/D+ pin to high.
    PORTSetPinsDigitalOut(IOPORT_B, BIT_6);
    PORTSetBits(IOPORT_B, BIT_6);

    // Initialize Timer1 and OLED for display
    DelayInit();
    OledInit();

    // Initialize GPIO for debugging
    DBG_INIT();

    // Initial Timer2 and ADC
    initTimer2();
    initADC();

    // Configure the system for vectored interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Enable the interrupt controller
    INTEnableInterrupts();

    x = 0;
    y = 0;
    prev_x = 0;
    prev_y = 0;
    left = 0;
    right = 0;
    up = 0;
    down = 0;

    while (1) {

       
        ms_since_last_oled_update = timer2_ms_value - last_oled_update;
        if (ms_since_last_oled_update >= 100) {
            OledSetCursor(0, 0);
            sprintf(oledstring, "L/R = %.4d  %.4d", x, timer2_ms_value / 1000);
            OledPutString(oledstring);
            OledSetCursor(0, 1);
            sprintf(oledstring, "U/D = %.4d", y);
            OledPutString(oledstring);

            // Set cursor and update if joystick is being moved left or right
            OledSetCursor(0, 2);
            if(left) {
                sprintf(oledstring, "LEFT        ");
                OledPutString(oledstring);
                left = 0;
            } else if(right) {
                sprintf(oledstring, "       RIGHT");
                OledPutString(oledstring);
                right = 0;
            } else {
                sprintf(oledstring, "             ");
                OledPutString(oledstring);
            }
            
            // Set cursor and update if joystick is being moved up or down
            OledSetCursor(0, 3);
            if(up) {
                sprintf(oledstring, "UP          ");
                OledPutString(oledstring);
                up = 0;
            } else if(down) {
                sprintf(oledstring, "       DOWN");
                OledPutString(oledstring);
                down = 0;
            } else {
                sprintf(oledstring, "             ");
                OledPutString(oledstring);
            }
            OledUpdate();
        }
    }
    return (EXIT_SUCCESS);
}
