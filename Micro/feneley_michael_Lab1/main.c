////////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        Lab 1
// File name:       main.c
// Description:     Test the Digilent board by writing a short message to the OLED.
//                  Also display a counter that updates every millisecond.
//                  Test on screen LEDs by having all 4 LEDs light when either
//                  BTN1 or BTN2 but not both BTN1 and BTN2 are pressed.
// Resources:       main.c uses Timer2 to generate interrupts at intervals of 1 ms.
//					delay.c uses Timer1 to provide delays with increments of 1 ms.
//					PmodOLED.c uses SPI1 for communication with the OLED.
// Written by:      Michael Feneley
// Last modified:   9/1/2014
#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"

// Digilent board configuration
#pragma config ICESEL       = ICS_PGx1  // ICE/ICD Comm Channel Select
#pragma config DEBUG        = OFF       // Debugger Disabled for Starter Kit
#pragma config FNOSC        = PRIPLL	// Oscillator selection
#pragma config POSCMOD      = XT	// Primary oscillator mode
#pragma config FPLLIDIV     = DIV_2	// PLL input divider
#pragma config FPLLMUL      = MUL_20	// PLL multiplier
#pragma config FPLLODIV     = DIV_1	// PLL output divider
#pragma config FPBDIV       = DIV_8	// Peripheral bus clock divider
#pragma config FSOSCEN      = OFF	// Secondary oscillator enable

// Global variables
unsigned int sec1000; // This is updated 1000 times per second by the interrupt handler

// Interrupt handler - respond to timer-generated interrupt
#pragma interrupt InterruptHandler_2534 ipl1 vector 0
void InterruptHandler_2534( void )
{
   if( INTGetFlag(INT_T2) )             // Verify source of interrupt
   {
      sec1000++;                        // Update global variable
      INTClearFlag(INT_T2);             // Acknowledge interrupt
   }
   return;
}

int main()
{
   char buf[17];        // Temp string for OLED display

   // Initialize GPIO for BTN1 and LED1
   TRISGSET = 0xc0;     // For BTN1: configure PortG bit for input
   TRISGCLR = 0xf000;   // For LED1: configure PortG pin for output
   ODCGCLR  = 0xf000;   // For LED1: configure as normal output (not open drain)






   // Initialize Timer1 and OLED
   DelayInit();
   OledInit();

   // Set up Timer2 to roll over every ms
   OpenTimer2(T2_ON         |
             T2_IDLE_CON    |
             T2_SOURCE_INT  |
             T2_PS_1_16     |
             T2_GATE_OFF,
             624);  // freq = 10MHz/16/625 = 1 kHz

   // Set up CPU to respond to interrupts from Timer2
   INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_1);
   INTClearFlag(INT_T2);
   INTEnable(INT_T2, INT_ENABLED);
   INTConfigureSystem(INT_SYSTEM_CONFIG_SINGLE_VECTOR);
   INTEnableInterrupts();

   // Send a welcome message to the OLED display
   OledClearBuffer();
   OledSetCursor(0, 0);
   OledPutString("ECE 2534");
   OledSetCursor(0, 2);
   OledPutString("MichaelFeneley");
   OledUpdate();

   // Main processing loop
   while (1)
   {
      // Display millisecond count value
      sprintf(buf, "%16d", sec1000);
      OledSetCursor(0, 3);
      OledPutString(buf);
      OledUpdate();

      // Update LED1
      if(PORTG & 0x40 && !(PORTG & 0x80)) { // Check BTN1 and !BTN2
         LATGSET = 15 << 12; // Set to 0x1111b << 12 to turn on all LEDs.
      } else if(!(PORTG & 0x40) && (PORTG & 0x80)) { // Check BTN2 and !BTN1
         LATGSET = 15 << 12; // Set to 0x1111b << 12 to turn on all LEDs.
      } else {
         LATGCLR = 15 << 12; // Set to 0x1111b << 12 to turn off all LEDs.
      }
   }

   return 0;
}

