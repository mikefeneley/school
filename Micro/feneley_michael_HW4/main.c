////////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        HW 4
// File name:       main.c
// Description:     This program functions as a stopwatch. When loaded to the
//                  diligent board it starts a timer when button 1 is pushed,
//                  stops when it is pushed again, and restarts when pushed
//                  a third time.
//                  I think I do meet project requirements. The spec said not
//                  to use an iterrupt for the clock and I did not. I did
//                  use an interrupt to debounce the button but I think that is
//                  allowed.
// Written by:      Michael Feneley
// Last modified:   10/2/2014
#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include <stdbool.h>
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

enum state {
       start,
       press1,
       press2,
};



unsigned char Button1History = 0x00;
bool Button1Pressed = false;
bool StateUpdated = false;

// Interrupt handler - respond to timer-generated interrupt
#pragma interrupt InterruptHandler_2534 ipl1 vector 0
void InterruptHandler_2534( void )
{
    if(INTGetFlag(INT_T2))
    {

        Button1History <<= 1;

        // Check button history.
        if(PORTG & 0x40) {
            Button1History |= 0x01;
        }

         // Signal to update state
         if(Button1History == 0xFF) {
            Button1Pressed = true;
         }

          if(Button1History == 0x00) { /*Restart so we update state on next press*/
             if(Button1Pressed) {
                StateUpdated = false;
             }
             Button1Pressed = false;
          }

        INTClearFlag(INT_T2);
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
   
   // Set up Timer3 to roll over every ms
   OpenTimer3(T3_ON         |
             T3_IDLE_CON    |
             T3_SOURCE_INT  |
             T3_PS_1_256     |
             T3_GATE_OFF,
             39063);  // freq = 10MHz/256/39064 = 1 Hz


   // Initialize intial time to 00:00
   unsigned int seconds = 0;
   unsigned int minutes = 0;


      OledClearBuffer();
   OledSetCursor(0, 0);
   OledPutString("ECE 2534");
   OledSetCursor(0, 1);
   OledPutString("MichaelFeneley");
   OledSetCursor(0, 2);
   OledPutString("Stopwatch");
   sprintf(buf, "%.2u:%.2u", minutes, seconds);
   OledSetCursor(0, 3);
   OledPutString(buf);
   OledUpdate();

   // Control booleans
   enum state press_state = start;
   bool updated = false;
   bool values_updated = false;

   // Main processing loop
   while (1) {

       if(Button1Pressed & !StateUpdated) { /*Update button state*/
          if(press_state == start) {
             press_state = press1;
          } else if(press_state == press1) {
              press_state = press2;
          } else if(press_state == press2) {
              press_state = start;
          }
          StateUpdated = true;
      }


      /* Reset values for start and on third button press */
      if(press_state == start) {
          if(minutes != 0 || seconds != 0) { /* Reset only once */
             minutes = 0;
             seconds = 0;
             sprintf(buf, "%.2u:%.2u", minutes, seconds);
             OledSetCursor(0, 3);
             OledPutString(buf);
             OledUpdate();
          }
      }
      else if(press_state == press1) {
          if(!updated && TMR3 < 15000) {/*Check if we need to update value*/
              seconds++;
              if(seconds == 60) {
                  seconds = 0;
                  minutes++;
              }
              if(minutes == 60) {
                  minutes = 0;
              }
              /* Set so we don't continue incrementing, and that we update display*/
              values_updated = true;
              updated = true;

          } else if(TMR3 >= 15000){/*Update in last half of second so change is made*/
              updated = false;
          }

          if(values_updated) { /* Update clock display*/
             sprintf(buf, "%.2u:%.2u", minutes, seconds);
             OledSetCursor(0, 3);
             OledPutString(buf);
             OledUpdate();
             values_updated = false;
          }
      }
   }
   return 0;
}

