////////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        Lab 1
// File name:       main.c
// Description:     This program displays a 4 bit number using the PIC32 LEDs.
//                  Pressing button 1 increments the number by 1 and pressing
//                  button 2 displays the complement of the current number.
//                  I think the program meets the requirements. 
// Resources:       main.c uses Timer2 to generate interrupts at intervals of 1 ms.
//					delay.c uses Timer1 to provide delays with increments of 1 ms.
//					PmodOLED.c uses SPI1 for communication with the OLED.
// Written by:      Michael Feneley
// Last modified:   9/1/2014
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

// Global variables
unsigned int sec1000; // This is updated 1000 times per second by the interrupt handler
bool Button1Pressed = false;
bool Button2Pressed = false;

bool StateMachineUpdated = false;


   enum state {
   state0000,
   state0001,
   state0010,
   state0011,
   state0100,
   state0101,
   state0110,
   state0111,
   state1000,
   state1001,
   state1010,
   state1011,
   state1100,
   state1101,
   state1110,
   state1111
   };


   unsigned char Button1History = 0x00;
   unsigned char Button2History = 0x00;

   unsigned char max = 0xff;
   unsigned char min = 0x00;

// Interrupt handler - respond to timer-generated interrupt
#pragma interrupt InterruptHandler_2534 ipl1 vector 0
void InterruptHandler_2534( void )
{
    if(INTGetFlag(INT_T2))
    {
        sec1000++;
        Button1History <<= 1;
        Button2History <<= 1;

        // Check button history.
        if(PORTG & 0x40) {
            Button1History |= 0x01;
        }
        if(PORTG & 0x80) {
            Button2History |= 0x01;
        }


        // Turn button on after debouncing.
        if(Button1History ==  max) {
            Button1Pressed = true;
        }
        if(Button2History ==  max) {
            Button2Pressed = true;
            
        }

        // Turn button off after debouncing.
        if(Button1History == min) {

            if(Button1Pressed) {
                StateMachineUpdated = false;
            }
            Button1Pressed = false;
        }
        if(Button2History == min) {
            if(Button2Pressed) {
                StateMachineUpdated = false;
            }
            Button2Pressed = false;
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



   // Set initial machine state.
   enum state machine_state = state0000;

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
   OledPutString("MichaelFeneley1");
   OledUpdate();

   // Main processing loop
    while (1)
    {
        // Display millisecond count value
        sprintf(buf, "%16d", sec1000);
        OledSetCursor(0, 3);
        OledPutString(buf);
        OledUpdate();

        /*Alter the display on the LEDs based on the current state and button
          pressed */
        switch(machine_state)
        {
            case state0000:
                LATGCLR = (1 << 15) | (1 << 14) | (1 << 13) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0001;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1111;
                    StateMachineUpdated = true;
                }
                break;

            case state0001:
                LATGSET = 1 << 12;
                LATGCLR = (1 << 15) | (1 << 14) | (1 << 13);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0010;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1110;
                    StateMachineUpdated = true;
                }
                break;
                
            case state0010:
                LATGSET = 1 << 13;
                LATGCLR = (1 << 15) | (1 << 14) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0011;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1101;
                    StateMachineUpdated = true;
                }
                break;
                
            case state0011:
                LATGSET = (1 << 12) | (1 << 13);
                LATGCLR = (1 << 15) | (1 << 14);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0100;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1100;
                    StateMachineUpdated = true;
                }
                break;

            case state0100:
                LATGSET = 1 << 14;
                LATGCLR = (1 << 15) | (1 << 13) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0101;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1011;
                    StateMachineUpdated = true;
                }
                break;

            case state0101:
                LATGSET = (1 << 12) | (1 << 14);
                LATGCLR = (1 << 15) | (1 << 13);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0110;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1010;
                    StateMachineUpdated = true;
                }
                break;

            case state0110:
                LATGSET = (1 << 13) | (1 << 14);
                LATGCLR = (1 << 15) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0111;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1001;
                    StateMachineUpdated = true;
                }
                break;

            case state0111:
                LATGSET = (1 << 13) | (1 << 14) | (1 << 12);
                LATGCLR = (1 << 15);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1000;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state1000;
                    StateMachineUpdated = true;
                }
                break;
            case state1000:
                LATGSET = (1 << 15);
                LATGCLR = (1 << 13) | (1 << 14) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1001;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0111;
                    StateMachineUpdated = true;
                }
                break;

            case state1001:
                LATGSET = (1 << 15) | (1 << 12);
                LATGCLR = (1 << 13) | (1 << 14);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1010;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0110;
                    StateMachineUpdated = true;
                }
                break;

            case state1010:
                LATGSET = (1 << 15) | (1 << 13);
                LATGCLR = (1 << 12) | (1 << 14);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1011;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0101;
                    StateMachineUpdated = true;
                }
                break;
            case state1011:
                LATGSET = (1 << 15) | (1 << 12) | (1 << 13);
                LATGCLR = (1 << 14);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1100;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0100;
                    StateMachineUpdated = true;
                }
                break;

            case   state1100:
                LATGSET = (1 << 15) | (1 << 14);
                LATGCLR = (1 << 13) | (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1101;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0011;
                    StateMachineUpdated = true;
                }
                break;

            case   state1101:
                LATGSET = (1 << 15) | (1 << 14) | (1 << 12);
                LATGCLR = (1 << 13);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1110;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0010;
                    StateMachineUpdated = true;
                }
                break;

            case  state1110:
                LATGSET = (1 << 15) | (1 << 13) | (1 << 14);
                LATGCLR = (1 << 12);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state1111;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0001;
                    StateMachineUpdated = true;
                }
                break;

            case  state1111:
                LATGSET = (1 << 15) | (1 << 12) | (1 << 13) | (1 << 14);
                if(Button1Pressed && !StateMachineUpdated) {
                    machine_state = state0000;
                    StateMachineUpdated = true;
                } else if(Button2Pressed && !StateMachineUpdated) {
                    machine_state = state0000;
                    StateMachineUpdated = true;
                }
                break;
                
            default:
               LATGSET = (1 << 15) | (1 << 12) | (1 << 13) | (1 << 14);
               break;
        }
   }

   return 0;
}

