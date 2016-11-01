// ECE 2534:        Lab2 -- Hangman
//                  This progam meets all the requirements.
//
// Purpose:         Implement the game hangman where users input
//                  characters through a terminal and their result is sent
//                  back after being processed by the Dilligent board.
//
//                  Display the char received on the OLED.
// Resources:       main.c uses Timer2 to generate interrupts at intervals of 1 ms.
//                  UART is configured via PLIB functions.
// Written by:      Michael Feneley
// Last modified:   7 October 2015

#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"
#include "stdbool.h"


/* Input and output UART function defintions*/
int myputs ( const char * str );
int mygetchar (void);

// These are options for the configuration of your board.
// Do not modify these without the guidance of your instructor or GTA.
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

// Programs can use GLOBAL VARIABLES when a variable
// needs be visible to the main function and to a function
// outside of main. In this case the main function uses a
// millisecond counter that the interrupt handler function
// updates. But the interrupt handler cannot receive arguments from main.
// This is updated once per millisecond by the interrupt handler.
// It is updated once per second because that is the way timer 2 was
// initialized. In general, global variables should be avoided.
unsigned int millisec;

#define MAXCHAR 256
#define MAXWORDLENGTH 20
#define NUMWORDS 10
char words[NUMWORDS][MAXWORDLENGTH] =
{
    "apple",
    "banana",
    "grape",
    "grapefruit",
    "kiwi",
    "peach",
    "pear",
    "pepper",
    "carrot",
    "watermelon"
};



// This configuration option defines the timer interrupt handler.
#pragma interrupt TimerInterruptHandler ipl1 vector 0

// Define some constants to use in the UART example program
// Peripheral bus clock rate, UART baud rate, and which UART
// to use.
#define PB_CLOCK 10000000
#define UART_BAUD_RATE 9600 
#define MY_UART UART1

// Number of milliseconds per UART send
#define NUM_MILLISECS_PER_SEND 200

// Timer compare setting
// The period of Timer 2 is (16 * (624+1))/(10 MHz) = 1 ms.
#define TIMER_PERIOD_1_MSEC 624

// Intrumentation for logic analyzer or oscilloscope
#define MASK_DBG1  0x1;
#define MASK_DBG2  0x2;
#define MASK_DBG3  0x4;
#define DBG_ON(a)  LATESET = a
#define DBG_OFF(a) LATECLR = a
#define DBG_INIT()  TRISECLR = 0x7

unsigned char Button1History = 0x00;
bool Button1Pressed = false;
bool StateUpdated = false;

void TimerInterruptHandler(void)
{
if(INTGetFlag(INT_T2)) {
        Button1History <<= 1;
        // Check button history.
        if(PORTG & 0x40) {
            Button1History |= 0x01;
        }
         // Signal to update state
         if(Button1History == 0xFF) {
            Button1Pressed = true;
         }
         /* Restart so we update state on next press */
          if(Button1History == 0x00) {
             if(Button1Pressed) {
                StateUpdated = false;
             }
             Button1Pressed = false;
          }
        INTClearFlag(INT_T2);
    }
   return;
}


enum state {
       stop,
       start,
};

int main(void)
{
    // Initialize the delay timer and OLED.
    DelayInit();
    OledInit();

    // Set up Timer2 to roll over every ms
   OpenTimer2(T2_ON         |
             T2_IDLE_CON    |
             T2_SOURCE_INT  |
             T2_PS_1_16     |
             T2_GATE_OFF,
             TIMER_PERIOD_1_MSEC);  // freq = 10MHz/16/625 = 1 kHz

   // Set up Timer3 to roll over every second
   OpenTimer3(T3_ON         |
             T3_IDLE_CON    |
             T3_SOURCE_INT  |
             T3_PS_1_256     |
             T3_GATE_OFF,
             39063);  // freq = 10MHz/256/39064 = 1 Hz
   
    // Configure the CPU to respond to Timer 2's interrupt requests.
    INTConfigureSystem(INT_SYSTEM_CONFIG_SINGLE_VECTOR);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_1);
    INTClearFlag(INT_T2);
    INTEnable(INT_T2, INT_ENABLED);
    INTEnableInterrupts();

    // Configure the UART the way we want to use it...
    // See the Plib include file (uart.h) and notes from
    // class to understand the settings.
    UARTConfigure(MY_UART, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetDataRate(MY_UART, PB_CLOCK, UART_BAUD_RATE);
    UARTSetLineControl(MY_UART,
            UART_DATA_SIZE_8_BITS|UART_PARITY_NONE|UART_STOP_BITS_1);
    UARTEnable(MY_UART, UART_ENABLE|UART_PERIPHERAL|UART_RX|UART_TX);


   // Initialize GPIO for BTN1 and LED1
   TRISGSET = 0xc0;     // For BTN1: configure PortG bit for input
   TRISGCLR = 0xf000;   // For LED1: configure PortG pin for output

   // Initialize intial time to 00:00
   unsigned int seconds = 0;
   unsigned int minutes = 0;
   char buf[17];        // Temp string for OLED display


   // Messages to send to the terminal display.
   char *start_message = "ECE 2534 Hangman!\nLet'sPlay!";
   char *game_word = NULL;
   char hidden_word[MAXWORDLENGTH];
   char *message1 = "Secret word:";
   char *message2 = "Remaining trials:";
   char *message3 = "Enter Your Selection:";
   char *message4 = "The secret word was:";
   char *message5 = "GAME OVER - THE COMPUTER WINS!";
   char *message6 = "To start a new game, press PB1";
   char *message7 = "Secret word";
   char *message8 = "CONGRATUALATIONS - YOU WIN!";
   char character_holder[2];
   character_holder[0] = "";
   character_holder[1] = '\0';

   // Holds the output messages sent to terminal.
   char message1_buf[MAXCHAR];
   char message2_buf[MAXCHAR];
   char message3_buf[MAXCHAR];

   int num_trials = 10;

   // Send an initial welcome message to the OLED display.
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
   enum state press_state = stop;
   bool updated = false;
   bool values_updated = false;

   while(1){

       // This block is used to update the state of the state machine
       // whenever button 1 is pressed.
       if(Button1Pressed & !StateUpdated) {
          if(press_state == stop) {
             press_state = start;
          } else if(press_state == start) {
              game_word = NULL;
              num_trials = 10;
          }
          StateUpdated = true;
      }

       if(press_state == start) {

           // This block runs whenever a new game is started. It gets the new
           // gameword and prompts the user for input.
           if(game_word == NULL) {
              myputs(start_message);
              srand(TMR3);
              int random = rand()%10;
              game_word = &words[random][0];

              // Generate string with same number of * as characters in word.
              int length = strlen(game_word);
              int i = 0;
              while(i < length)
              {
                  hidden_word[i] = '*';
                  i++;
              }
              hidden_word[i] = '\0';

              // Output message
              sprintf(message1_buf, "%s %s", message1, hidden_word);
              sprintf(message2_buf, "%s %d", message2, num_trials);
              myputs(message1_buf);
              myputs(message2_buf);
              myputs(message3);
           }
           // This block runs when a game is in session.
           // It tries to get a character from the terminal and then
           // checks that terminal agains the game word.
           else {
               int guess = mygetchar();
                   guess = tolower(guess);
               // Verify that we have a valid game character
               if(guess > 0 && guess != '#') {
                   // Echo user input
                   character_holder[0] = guess;
                   myputs(character_holder);

                  // Check word for letter match.
                  bool correct_guess = false;
                  int length = strlen(game_word);
                  int i = 0;
                  while(i < length)
                  {
                      if(guess == game_word[i])
                      {
                          hidden_word[i] = guess;
                          correct_guess = true;
                      }
                      i++;
                  }

                  // Decement number of trials on incorrect guess.
                  if(!correct_guess) {
                      num_trials--;
                  }

                  // Output game over message if game lost.
                  if(num_trials == 0) {
                      sprintf(message3_buf, "%s %s\n %s\n %s", message4,
                                game_word, message5, message6);
                      myputs(message3_buf);
                      game_word = NULL;
                      num_trials = 10;
                      press_state = stop;
                  } else {

                      // Check hidden word to see if game won.
                      bool word_found = true;
                      int length = strlen(game_word);
                      int i = 0;
                      while(i < length)
                      {
                          if(hidden_word[i] == '*') {
                              word_found = false;
                          }
                          i++;
                      }                      

                      // Output error message and go to stop state if game
                      // won.
                      if(word_found) {
                          sprintf(message3_buf, "%s %s\n %s\n %s", message4,
                                    game_word, message8, message6);
                          myputs(message3_buf);
                          game_word = NULL;
                          num_trials = 10;
                          press_state = stop;
                      // Output current game status and prompt user for input.
                      } else {
                          sprintf(message1_buf, "%s %s", message1, hidden_word);
                          sprintf(message2_buf, "%s %d", message2, num_trials);
                          myputs(message1_buf);
                          myputs(message2_buf);
                          myputs(message3);
                      }
                  }
               } else if(guess == '#') { // Output character and start new game.
                   character_holder[0] = guess;
                   myputs(character_holder);
                   num_trials = 10;
                   game_word = NULL;
               }
            }
        }

      /*Time keeping section of the game*/
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
    
    return 0;
}

/////////////////////////////////////////////////////////
// Description: Send a string to UART1,
// and append a newline character ('\n')
// Input: str ? pointer to the string to be transmitted
// Return value: If successful, return the length of the string,
// not including the newline character;
// else return -1 to indicate an error
int myputs ( const char * str )
{
    unsigned char char_to_send;

    int i = 0;
    //Send all characters to UART
    while(i < strlen(str)) {
        char_to_send = str[i];
        // Spin while UART is not ready for send
        while (!UARTTransmitterIsReady(MY_UART)) {
        }
        UARTSendDataByte(MY_UART, char_to_send);
        i++;
    }
    // Append Newline character
    char_to_send = '\n';
    while (!UARTTransmitterIsReady(MY_UART)) {
    }
    UARTSendDataByte(MY_UART, char_to_send);
    return strlen(str);
}
/////////////////////////////////////////////////////////
// Description: Attempt to read 1 character from UART1
// Return value: If successful, return the character with a
// type-cast to type (int);
// otherwise return -1 to indicate an error
int mygetchar(void)
{
    unsigned char char_received;
    /*Get character if one is avaliable from the UART*/
    if(UARTReceivedDataIsAvailable(MY_UART)) {
        char_received = UARTGetDataByte(MY_UART);
    } else {
        return -1;
    }
    return (int) char_received;
}
/*In the puts function you might need to check the return of SendDataByte to
  make sure that it returns correctly*/
