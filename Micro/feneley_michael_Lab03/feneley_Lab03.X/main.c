////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        Lab 3
//
// File name:       main.c
//
// Description:     Allows the player to play a game of snake using a joystick
//
// How to use:      Connections:   Use JA-1
//                                 Red = L/R+
//                                 Black = Ground
//                                 Yellow = U/D+
//                                 Green = U/D
//                                 Brown = L/R
//
//                  The welcome screen displays for 5 seconds. After that use
//                  button1 and button2 to set the desired number of pumpkins
//                  Then press button 3 to start the game. At any point, button1
//                  can be pressed to return to the welcome screen. Button2 and
//                  button3 can be used to control the speed of the snake.
//
//  Notes:          This program meets all requirements.
//
// Written by:      Michael Feneley
// Last modified:   31 October 2015


#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include <time.h>
#include "delay.h"
#include <stdbool.h>

#define WIDTH 10
#define HEIGHT 4
#define MAXSNAKELENGTH 16
#define WELCOMEDURATION 5000
#define UP 700
#define DOWN 300
#define LEFT 300
#define RIGHT 700

// Definitions for the ADC averaging. How many samples (should be a power
// of 2, and the log2 of this number to be able to shift right instead of
// divide to get the average.
#define NUM_ADC_SAMPLES 32
#define LOG2_NUM_ADC_SAMPLES 5

// Enum defines current progress in single game
enum progress {
    win,
    lose,
    restart,
    point,
    play,
};
// Enum defines current screen state
enum game_state {
    welcome,
    setup,
    game,
    end,
};
// Enum defines type of character located at each cell in game board.
enum cell {
    snake_cell,
    pumpkin_cell,
    blank_cell,
};

// Enum defines the current direction the snake should be moving.
enum direction {
    none,
    left,
    right,
    up,
    down,
};

// Enum defines current positon of snake.
struct snake {
  int x;
  int y;
};
// Enum holds a position on the game board.
struct coordinate {
    int x;
    int y;
};



// Forward declaration of functions
void OledDrawGlyph(char ch);
void SetWelcomeScreen();
void SetSetupScreen();
void SetGameScreen(int game_result);
void SetEndGameScreen();
void InitGameBoard(int game_board[WIDTH][HEIGHT],
                            struct snake snakes[MAXSNAKELENGTH]);
void NewPumpkin(int game_board[WIDTH][HEIGHT]);
int NextSnakeIndex(struct snake snakes[MAXSNAKELENGTH]);
void ChangeGoal(int goal);
void UpdateScore();
void DisplayWelcome();
int PlayGame(int pumpkin_goal);
void DisplayEndGame(int game_result);
int GetPumpkinGoal();
void MoveSnake(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH],
                        struct coordinate *prev_pos);
void NewSnake(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH],
                        struct coordinate *prev_pos);
bool CheckWin(int pumpkin_goal);
int SnakeDown(int game_board[WIDTH][HEIGHT],
        struct snake snakes[MAXSNAKELENGTH]);
int SnakeUp(int game_board[WIDTH][HEIGHT],
        struct snake snakes[MAXSNAKELENGTH]);
int SnakeLeft(int game_board[WIDTH][HEIGHT],
        struct snake snakes[MAXSNAKELENGTH]);
int SnakeRight(int game_board[WIDTH][HEIGHT],
        struct snake snakes[MAXSNAKELENGTH]);




// Configure the microcontroller
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_8         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Clock Monitor
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



// Global variable to count number of times in timer2 ISR
unsigned int timer2_ms_value = 0;
// Global variable to keep track of player score
unsigned int score = 0;

// Global definitions of our user-defined characters
BYTE blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char blank_char = 0x01;
BYTE head[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
char head_char = 0x00;
BYTE tail[8] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55};
char tail_char = 0x02;
BYTE pumpkin[8] = {0x00, 0xe6, 0x84, 0x90, 0x90, 0x86, 0xe4, 0x00};
char pumpkin_char = 0x03;

// Variables used to control state and debounce button.
unsigned char Button1History = 0x00;
unsigned char Button2History = 0x00;
unsigned char Button3History = 0x00;
bool Button1Pressed = false;
bool Button2Pressed = false;
bool Button3Pressed = false;
bool StateUpdated = false;

// Variable used to control the direction of the snake.
enum direction input = none;


// The interrupt handler for the ADC
// IPL7 highest interrupt priority
// Takes the average to eliminate noise.
// Sets signals that tell the snake which direction to move.
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
        int x = x_total >> LOG2_NUM_ADC_SAMPLES;
        int y = y_total >> LOG2_NUM_ADC_SAMPLES;

        // Set direction for snake to move
        if(x > RIGHT) {
            input = right;
        } else if (x < LEFT) {
            input = left;
        } else if(y < DOWN) {
            input = down;
        } else if(y > UP) {
            input = up;
        }
    }
    INTClearFlag(INT_AD1);
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
// Timmer 3 is used to begin conversion
// ADC auto sampling (sampling begins immediately following conversion)
#define AD_CONFIG1 ADC_FORMAT_INTG | ADC_CLK_TMR | ADC_AUTO_SAMPLING_ON

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

// The interrupt handler for timer2
// Debounces buttons and signals state changes
// IPL4 medium interrupt priority
// SOFT|AUTO|SRS refers to the shadow register use
void __ISR(_TIMER_2_VECTOR, IPL4AUTO) _Timer2Handler(void) {
    timer2_ms_value++; // Increment the millisecond counter.

    Button1History <<= 1;
    Button2History <<= 1;
    Button3History <<= 1;

    // Check button history.
    if(PORTG & 0x40) {
        Button1History |= 0x01;
    } else if(PORTG & 0x80) {
        Button2History |= 0x01;
    } else if(PORTA & 0x1) {
        Button3History |= 0x1;
    }

    // Signal to update state
    if(Button1History == 0xFF) {
        Button1Pressed = true;
    } else if(Button2History == 0xFF) {
        Button2Pressed = true;
    } else if(Button3History == 0xFF) {
        Button3Pressed = true;
    }

    /* Restart so we update state on next press */
    if(Button1History == 0x00) {
        if(Button1Pressed && StateUpdated) {
            StateUpdated = false;
            Button1Pressed = false;
        }
    }
    if(Button2History == 0x00) {
        if(Button2Pressed && StateUpdated) {
            StateUpdated = false;
            Button2Pressed = false;
        }
    }
    if(Button3History == 0x00) {
        if(Button3Pressed && StateUpdated) {
            StateUpdated = false;
            Button3Pressed = false;
        }
    }
    INTClearFlag(INT_T2); // Acknowledge the interrupt source by clearing flag.
}

// Timer 3 is only used to trigger ADC conversion, so we only need to clear flag
void __ISR(_TIMER_3_VECTOR, IPL5AUTO) _Timer3Handler(void) {
    INTClearFlag(INT_T3);
}

// Initialize timer2 and set up the interrupts
void initTimer2() {
    // Configure Timer 2 to request a real-time interrupt once per millisecond.
    // The period of Timer 2 is (16 * 625)/(10 MHz) = 1 s.
    OpenTimer2(T2_ON | T2_IDLE_CON | T2_SOURCE_INT | T2_PS_1_16 | T2_GATE_OFF,
                    624);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTClearFlag(INT_T2);
    INTEnable(INT_T2, INT_ENABLED);
}

// Initialize timer3 and set up the interrupts
void initTimer3()
{
    // Configure Timer 3 to request a real-time interrupt once per millisecond.
    // The period of Timer 3 is (16 * 625)/(10 MHz) = 1 s.
    OpenTimer3(T3_ON | T3_IDLE_CON | T3_SOURCE_INT | T3_PS_1_16 | T3_GATE_OFF,
                    624);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, INT_PRIORITY_LEVEL_5);
    INTClearFlag(INT_T3);
    INTEnable(INT_T3, INT_ENABLED);
}

int main()
{
      // Set U/D+ pin to high.
    PORTSetPinsDigitalOut(IOPORT_B, BIT_6);
    PORTSetBits(IOPORT_B, BIT_6);

    // Initialize GPIO for LEDs
    TRISGCLR = 0xf000; // For LEDs: configure PortG pins for output
    ODCGCLR = 0xf000; // For LEDs: configure as normal output (not open drain)
    LATGCLR = 0xf000; // Initialize LEDs to 0000
    PORTSetPinsDigitalIn(IOPORT_A, BIT_0);
    DDPCONbits.JTAGEN = 0;

    // Initialize Timer1 and OLED for display
    DelayInit();
    OledInit();

    // Set up our user-defined characters for the OLED
    OledDefUserChar(blank_char, blank);
    OledDefUserChar(head_char, head);
    OledDefUserChar(tail_char, tail);
    OledDefUserChar(pumpkin_char, pumpkin);

    // Initialize interrupts
    initTimer2();
    initTimer3();
    initADC();

    // Configure the system for vectored interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Enable the interrupt controller
    INTEnableInterrupts();

    // Start game at the welcome screen.
    enum game_state game_s = welcome;
    enum progress game_result;
    int pumpkin_goal = 1;
    
    while(1) {
        switch(game_s) {
            case(welcome): // Display welcome message for 5 seconds
                DisplayWelcome();
                game_s = setup;
                break;
            case(setup) : // Prompt user to set pumpkin goal using btn1 | btn2
                pumpkin_goal = GetPumpkinGoal();
                game_s = game;                   
                break;
            case(game) : // Allower user to play the game Snake.
                game_result = PlayGame(pumpkin_goal);
                if(game_result == restart) {
                    game_s = welcome;
                } else {
                    game_s = end;
                }
                break;
            case(end) : // Display win or lose game screen
                DisplayEndGame(game_result);
                game_s = welcome;
                break;
        }
    }
    return (EXIT_SUCCESS);
}

/**
 *  Displays the message at the begining of a game
 *
 *   Pre: Oled has been initialized. Timer2 has been initialized
 *   Post: Open message is displayed.
 *   Input: 
 *   Output
 */
void DisplayWelcome()
{
    unsigned int welcome_screen_ms = timer2_ms_value;
    SetWelcomeScreen();
    while(1){
        // Get rid of any accidental button pressed by user.
        if(Button1Pressed || Button2Pressed || Button3Pressed) {
            StateUpdated = true;
        }
        // Delay for 5 seconds.
        if(timer2_ms_value - welcome_screen_ms >= WELCOMEDURATION) {
            return;
        }
    }
}
/**
 *  Displays the message at the end of a game
 *
 *   Pre: Oled has been initialized. Timer2 has been initialized
 *   Post: End message is displayed.
 *   Input: @game_result Result used to set proper end message.
 *   Output
 */
void DisplayEndGame(int game_result)
{
    SetEndGameScreen(game_result);
    while(1) {
        if(Button1Pressed && !StateUpdated) { // Return to welcome screen
            StateUpdated = true;
            return;
        }
    }
}

/**
 *  Implements the logic for the snake game. Intializes game variables and then
 *  responds to user input from the joystick. This function also implements the
 *  added player funcitonality of increasing or decreasing the snake speed by
 *  pressing button2 or button3 respectively.
 *
 *   Pre: Timmer2 and ADC have been initialized.
 *   Post: 
 *   Input: The number of pumpkins that need to be collected to win.
 *   Output Returns if the game has been won, lost, or reset.
 */
int PlayGame(int pumpkin_goal)
{
    // Put starting pieces on the game board.
    int game_board[WIDTH][HEIGHT];
    struct snake snakes[MAXSNAKELENGTH];
    SetGameScreen(pumpkin_goal);
    InitGameBoard(game_board, snakes);

    // Set input to none so snake is not moving when the game starts.
    input = none;
    // Timer variables used to determine when to update oled.
    unsigned int last_oled_update = 0;
    unsigned int ms_since_last_oled_update;
    enum progress move_result = play;
    int game_speed = 500;

    // Loop until the game is finished or the user restarts.
    while(1) {
        ms_since_last_oled_update = timer2_ms_value - last_oled_update;
        if(ms_since_last_oled_update >= game_speed) {
            switch(input) {
                case(none) :
                    break;
                case(up) :
                    move_result = SnakeUp(game_board, snakes);
                    break;
                case(down):
                    move_result = SnakeDown(game_board, snakes);
                    break;
                case(left) :
                    move_result = SnakeLeft(game_board, snakes);
                    break;
                case(right) :
                    move_result = SnakeRight(game_board, snakes);
                    break;
                default :
                    break;
            }
            last_oled_update = timer2_ms_value;
        }
        // Button2 increases movement speed.
        if(Button2Pressed && !StateUpdated) {
            StateUpdated = true;
            if(game_speed >= 200) {
                game_speed = game_speed - 100;
            }
        }
        // Button3 decreases movement speed.
        if(Button3Pressed && !StateUpdated) {
            StateUpdated = true;
            game_speed = game_speed + 100;
        }

       // Give users the option to go to welcome screen by pressing button 1
       if(Button1Pressed && !StateUpdated) {
            StateUpdated = true;
            move_result = restart;
            return move_result;
       }
        if(CheckWin(pumpkin_goal)) {
            move_result = win;
        }
        // Return if something causes the game to end.
        if(move_result != play) {
            return move_result;
        }
    }
}

/**
 *  Displays the setup screen and waits for the user to set the pumpkin goal
 *  using button1 and button2.
 *
 *   Pre: Timmer2 has been initialized.
 *   Post: Snake has been added at position (0,0). One spot contains a pumpkin.
 *         All other spots are blank.
 *   Input: 
 *   Output The  number of pumpkins that need to be collected to win.
 */
int GetPumpkinGoal()
{
    SetSetupScreen();
    int pumpkin_goal = 1;

    while(1) {
        DelayMs(2);
        if(Button1Pressed && !StateUpdated) {
            if(pumpkin_goal < MAXSNAKELENGTH - 1) {
                pumpkin_goal++;
                ChangeGoal(pumpkin_goal);
            }

            StateUpdated = true;
        } else if(Button2Pressed && !StateUpdated) {
            if(pumpkin_goal > 1) {
                pumpkin_goal--;
                ChangeGoal(pumpkin_goal);
            }
            StateUpdated = true;
        } else if(Button3Pressed && !StateUpdated) {
            StateUpdated = true;
            return pumpkin_goal;
        }
    }

    return pumpkin_goal;
}
/**
 *   Set up the board for a new game of snake.
 *
 *   Pre: All variables have been intialized.
 *   Post: Snake has been added at position (0,0). One spot contains a pumpkin.
 *         All other spots are blank.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold snake segments.
 *   Output 
 */
void InitGameBoard(int game_board[WIDTH][HEIGHT],
                        struct snake snakes[MAXSNAKELENGTH])
{
    score = 0;
    // Set all cells to blank initially
    int i = 0;
    while(i < WIDTH) {
        int j = 0;
        while(j < HEIGHT) {
            game_board[i][j] = blank_cell;
            j++;
        }
        i++;
    }

    // Set way to detect new snake position in array.
    int k = 0;
    while(k < MAXSNAKELENGTH - 1) {
        snakes[k].x = -1;
        k++;
    }

    // Add snake and pumpkin to board.
    snakes[0].x = 0;
    snakes[0].y = 0;
    game_board[0][0] = snake_cell;
    OledSetCursor(0, 0);
    OledDrawGlyph(head_char);
    NewPumpkin(game_board);
    OledUpdate();
}
/**
 *   Adds a new pumpkin at a random spot that does not overlap with the snake
 *   somewhere on the game board.
 *
 *   Pre: game_board has been initialized and contains at least 1 snake cell.
 *   Post: The new pumpkin has been drawn on the screen and the game_board has
 *         been changed to reflect the new spot.
 *   Input: @game_board Board where the pumpkin will be added to.
 *          @snakes 
 *   Output
 */
void NewPumpkin(int game_board[WIDTH][HEIGHT])
{
    int pumpkin_x = rand() % WIDTH;
    int pumpkin_y = rand() % HEIGHT;

    while(game_board[pumpkin_x][pumpkin_y] == snake_cell) {
        pumpkin_x = rand() % WIDTH;
        pumpkin_y = rand() % HEIGHT;
    }
    game_board[pumpkin_x][pumpkin_y] = pumpkin_cell;
    OledSetCursor(pumpkin_x, pumpkin_y);
    OledDrawGlyph(pumpkin_char);
}

/**
 *   Moves the head of the snake one position down and updates the
 *   position of all other segments to the positon of the previous segments.
 *
 *   Pre: All variables have been intialized.
 *   Post: Every snake piece has been drawn in the position of the previous
 *         segment. The game board has been updated to reflect new snake
 *         positions. Coordinates of all snake segments have been updated.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold snake segments.
 *   Output Returns play if the game continues. Returns lose if the snake runs
 *          into a snake tail or the wall.
 */
int SnakeDown(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH])
{
    enum progress move_result = play;
    struct coordinate prev_pos;
    prev_pos.x = snakes[0].x;
    prev_pos.y = snakes[0].y;
    bool new_snake = false;

    snakes[0].y++;
    // Check lose conditions
    if(snakes[0].y > HEIGHT - 1 ||
            game_board[snakes[0].x][snakes[0].y] == snake_cell) {
        move_result = lose;
        return move_result;
    } else {
        // Check if the snake collected a pumpkin
        if(game_board[snakes[0].x][snakes[0].y] == pumpkin_cell) {
            new_snake = true;
        }

        // Move every snake to the next position in the chain.
        MoveSnake(game_board, snakes, &prev_pos);

        // Updates last spot with either a new snake or a blank cell.
        OledSetCursor(prev_pos.x, prev_pos.y);
        if(new_snake) {
            NewSnake(game_board, snakes, &prev_pos);
        } else {
            game_board[prev_pos.x][prev_pos.y] = blank_cell;
            OledDrawGlyph(blank_char);
        }
        OledUpdate();
    }
    return move_result;
}
/**
 *   Moves the head of the snake one position up and updates the
 *   position of all other segments to the positon of the previous segments.
 *
 *   Pre: All variables have been intialized.
 *   Post: Every snake piece has been drawn in the position of the previous
 *         segment. The game board has been updated to reflect new snake
 *         positions. Coordinates of all snake segments have been updated.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold snake segments.
 *   Output Returns play if the game continues. Returns lose if the snake runs
 *          into a snake tail or the wall.
 */
int SnakeUp(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH])
{
    enum progress move_result = play;
    struct coordinate prev_pos;
    prev_pos.x = snakes[0].x;
    prev_pos.y = snakes[0].y;
    bool new_snake = false;

    snakes[0].y--;
    if(snakes[0].y < 0 ||
            game_board[snakes[0].x][snakes[0].y] == snake_cell) {
            move_result = lose;
            return move_result;
    } else {
        // Check if the snake collected a pumpkin
        if(game_board[snakes[0].x][snakes[0].y] == pumpkin_cell) {
            new_snake = true;
        }

        // Move every snake to the next position in the chain.
        MoveSnake(game_board, snakes, &prev_pos);
        // Updates last spot with either a new snake or a blank cell.
        OledSetCursor(prev_pos.x, prev_pos.y);
        if(new_snake) {
            NewSnake(game_board, snakes, &prev_pos);
        } else {
            game_board[prev_pos.x][prev_pos.y] = blank_cell;
            OledDrawGlyph(blank_char);
        }
        OledUpdate();
    }
    return move_result;
}
/**
 *   Moves the head of the snake one position to the right and updates the
 *   position of all other segments to the positon of the previous segments.
 *
 *   Pre: All variables have been intialized.
 *   Post: Every snake piece has been drawn in the position of the previous
 *         segment. The game board has been updated to reflect new snake
 *         positions. Coordinates of all snake segments have been updated.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold snake segments.
 *   Output Returns play if the game continues. Returns lose if the snake runs
 *          into a snake tail or the wall.
 */
int SnakeRight(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH])
{
    enum progress move_result = play;

    struct coordinate prev_pos;
    prev_pos.x = snakes[0].x;
    prev_pos.y = snakes[0].y;
    bool new_snake = false;

    snakes[0].x++;
    if(snakes[0].x > WIDTH - 1 ||
            game_board[snakes[0].x][snakes[0].y] == snake_cell) {
        move_result = lose;
        return move_result;
    } else {

        if(game_board[snakes[0].x][snakes[0].y] == pumpkin_cell) {
            new_snake = true;
        }

        // Move every snake to the next position in the chain.
        MoveSnake(game_board, snakes, &prev_pos);

        OledSetCursor(prev_pos.x, prev_pos.y);
        if(new_snake) {
             NewSnake(game_board, snakes, &prev_pos);
        } else {
            game_board[prev_pos.x][prev_pos.y] = blank_cell;
            OledDrawGlyph(blank_char);
        }
        OledUpdate();
    }
    return move_result;
}
/**
 *   Moves the head of the snake one position to the left and updates the
 *   position of all other segments to the positon of the previous segments.
 *
 *   Pre: All variables have been intialized.
 *   Post: Every snake piece has been drawn in the position of the previous
 *         segment. The game board has been updated to reflect new snake
 *         positions. Coordinates of all snake segments have been updated.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold snake segments.
 *   Output Returns play if the game continues. Returns lose if the snake runs
 *          into a snake tail or the wall.
 */
int SnakeLeft(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH])
{

    enum progress move_result = play;
    struct coordinate prev_pos;
    prev_pos.x = snakes[0].x;
    prev_pos.y = snakes[0].y;
    bool new_snake = false;

    snakes[0].x--;
    if(snakes[0].x < 0 ||
            game_board[snakes[0].x][snakes[0].y] == snake_cell) {
        move_result = lose;
        return move_result;
    } else {
        
        if(game_board[snakes[0].x][snakes[0].y] == pumpkin_cell) {
            new_snake = true;
        }

        // Move every snake to the next position in the chain.
        MoveSnake(game_board, snakes, &prev_pos);

        // Make a new snake if pumpkin eaten, otherwise replace with blank cell
        OledSetCursor(prev_pos.x, prev_pos.y);
        if(new_snake) {
            NewSnake(game_board, snakes, &prev_pos);
        } else {
            game_board[prev_pos.x][prev_pos.y] = blank_cell;
            OledDrawGlyph(blank_char);
        }
        OledUpdate();
    }
    return move_result;
}
/**
 *   Moves every segment of the snake to the position of the previous segment
 *   In the array
 *
 *   Pre: All variables have been intialized.
 *   Post: Every snake piece has been drawn in the position of the previous
 *         segment. The game board has been updated to reflect new snake
 *         positions. Coordinates of all snake segments have been updated.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold new snake segment.
 *          @prev_pos Holds the coordinates where the new snake witll be added.
 *   Output
 */
void MoveSnake(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH],
                        struct coordinate *prev_pos)
{
    OledSetCursor(snakes[0].x, snakes[0].y);
    OledDrawGlyph(head_char);
    game_board[snakes[0].x][snakes[0].y] = snake_cell;

    struct coordinate tmp;
    // Move every snake to the next position in the chain.
    int index = NextSnakeIndex(snakes);
    int k = 1;
    while(k < index) {
        game_board[prev_pos->x][prev_pos->y] = snake_cell;
        tmp.x = snakes[k].x;
        tmp.y = snakes[k].y;
        snakes[k].x = prev_pos->x;
        snakes[k].y = prev_pos->y;
        OledSetCursor(snakes[k].x, snakes[k].y);
        OledDrawGlyph(tail_char);
        prev_pos->x = tmp.x;
        prev_pos->y = tmp.y;
        k++;
    }
}
/**
 *   Adds a new snake segment to the snake.
 *
 *   Pre: All variables have been intialized.
 *   Post: A new snake tail piece has been drawn on the oled at the coordinate
 *         specified by prev_pos. The coordinate is labeld as a snake_cell on
 *         the game_board.
 *   Input: @game_board Used to hold game logic.
 *          @snakes Array that is used to hold new snake segment.
 *          @prev_pos Holds the coordinates where the new snake witll be added.
 *   Output 
 */
void NewSnake(int game_board[WIDTH][HEIGHT],
                    struct snake snakes[MAXSNAKELENGTH],
                        struct coordinate *prev_pos)
{
    game_board[prev_pos->x][prev_pos->y] = snake_cell;
    int index = NextSnakeIndex(snakes);
    snakes[index].x = prev_pos->x;
    snakes[index].y = prev_pos->y;
    OledDrawGlyph(tail_char);
    UpdateScore();
    NewPumpkin(game_board);
}


/**
 *   Finds the next open slot for a snake in the snakes array.
 *
 *   Pre:   snakes has been initialized. All empty slots have an x value of -1.
 *   Post:  
 *   Input: @snakes Array of snakes with at least 1 open slot.
 *   Output Index of open slot.
 */
int NextSnakeIndex(struct snake snakes[MAXSNAKELENGTH])
{
    int i = 0;
    while(i < MAXSNAKELENGTH) {
        if(snakes[i].x == -1) {
            return i;
        }
        i++;
    }
    return MAXSNAKELENGTH -1;
}
/**
 *   Sets the Oled to display welcome messagae.
 *
 *   Pre:   Oled has been initialized
 *   Post:  Oled only displays welcome message.
 *   Input:
 *   Output:
 */
void SetWelcomeScreen()
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("Snake Game ");
    OledSetCursor(0, 1);
    OledPutString("Michael Feneley ");
    OledSetCursor(0, 2);
    OledPutString("October 31, 2015");
    OledUpdate();
}
/**
 *   Sets the Oled to display setup message.
 *
 *   Pre:   Oled has been initialized
 *   Post:  Oled only displays setup message.
 *   Input:
 *   Output:
 */
void SetSetupScreen()
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("Set Goal : 01");
    OledSetCursor(0, 1);
    OledPutString("Btn1 : Goal++");
    OledSetCursor(0, 2);
    OledPutString("Btn2 : Goal--");
    OledSetCursor(0, 3);
    OledPutString("Btn3 : Accept");
    OledUpdate();
}
/**
 *   Sets the Oled to display game message.
 *
 *   Pre:   Oled has been initialized
 *   Post:  Oled only displays setup message.
 *   Input: @goal The number of pumpkins that need to be collected to win.
 *   Output:
 */
void SetGameScreen(int goal)
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("          Score:");
    OledSetCursor(0, 1);
    OledPutString("          00");
    OledSetCursor(0, 2);
    OledPutString("          Goal:");

    char oledstring[17];
    OledSetCursor(0, 3);
    sprintf(oledstring, "          %.2d", goal);
    OledPutString(oledstring);
}
/**
 *   Sets the Oled to display end game messagae.
 *
 *   Pre:   Oled has been initialized
 *   Post:  Oled only displays end game message.
 *   Input: @game_result Used to determine if win or lose message should show.
 *   Output:
 */
void SetEndGameScreen(int game_result)
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    if(game_result == lose) {
        OledPutString("You Lose!");

    } else if(game_result == win) {
        OledPutString("You Win!");
    }
    OledSetCursor(0, 1);
    OledPutString("To play again");
    OledSetCursor(0, 2);
    OledPutString("Press button 1");
}
/**
 *   Changes the value of the goal shown on the LED
 *
 *   Pre:   Oled has been initialized
 *   Post:  The displayed goal has been changed
 *   Input: @goal The new value to display for the goal
 *   Output:
 */
void ChangeGoal(int goal)
{
    char oledstring[17];
    OledSetCursor(0, 0);
    sprintf(oledstring, "Set Goal : %.2d", goal);
    OledPutString(oledstring);
}
/**
 *   Increments the score when the snake head touches a pumpkin
 *
 *   Pre:   Oled has been initialized. Snake has landed on a pumpkin.
 *   Post:  The oled displays the previous score incremented by 1.
 *   Input: 
 *   Output:
 */
void UpdateScore()
{
    score++;
    char oledstring[17];
    OledSetCursor(10, 1);
    sprintf(oledstring, "%.2d", score);
    OledPutString(oledstring);
}
/**
 *   Increments the score when the snake head touches a pumpkin
 *
 *   Pre:   Score and pumpkin goal have been initialized
 *   Post:  
 *   Input: @pumpkin_goal The number of pumpkins required to win.
 *   Output: True if player has collected enough pumpkins. False otherwise.
 */
bool CheckWin(int pumpkin_goal)
{
    if(score >= pumpkin_goal) {
        return true;
    }
    return false;
}

