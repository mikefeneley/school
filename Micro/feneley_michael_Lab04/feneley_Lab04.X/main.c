////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        Lab 4
//
// File name:       main.c
//
// Description:     Allows the player to play a gamw with the objective of
//                  avoiding a zombie block.
//
// How to use:      Initially a splash screen will be displayed for 2 seconds.
//                  After this a menu screen is displayed. Here the user can
//                  press button 1 up to 4 times to add tree obstances. After
//                  setting the number of trees, hit button 3 to start.
//
//                  In the game, the tilt of the acl determines how fast the
//                  player moves. At any point, button 3 can be pressed to
//                  teleport to a random position on the board. Button 1 and
//                  button 2 can be used to speed up or slow down the zombie
//                  respectively. The trees look like boxes and neither the
//                  player nor the zombie can enter a tree space. Works with
//                  either JE or JF connector.
//
//  Notes:          The zombie program works correctly. Its movement is
//                  propotional to the tilt of the ACL. It does not respond to
//                  a single tap.
//
// Written by:      Michael Feneley
// Last modified:   12 October 2015


#define _PLIB_DISABLE_LEGACY
#include <plib.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"
#include <time.h>
#include <stdbool.h>

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



/* SPI commands */
#define ADXL345_SPI_READ        (1 << 7)
#define ADXL345_SPI_WRITE       (0 << 7)
#define ADXL345_SPI_MB          (1 << 6)
#define ADXL345_DATAX0          0x32 // R   X-Axis Data 0.
#define ADXL345_DATAX1          0x33 // R   X-Axis Data 1.
#define ADXL345_DATAY0          0x34 // R   Y-Axis Data 0.
#define ADXL345_DATAY1          0x35 // R   Y-Axis Data 1.
#define ADXL345_DATAZ0          0x36 // R   Z-Axis Data 0.
#define ADXL345_DATAZ1          0x37 // R   Z-Axis Data 1.
#define ADXL345_ID              0xE5
#define	ADXL345_DEVID           0x00 // R   Device ID.
#define ADXL345_POWER_CTL       0x2D // R/W Power saving features control.
#define ADXL345_PCTL_MEASURE    (1 << 3)
#define ADXL345_THRESH_FF       0x28 // R/W Free-fall threshold.
#define ADXL345_TIME_FF         0x29 // R/W Free-fall time.
#define ADXL345_TAP_AXES        0x2A // R/W Axis control for tap/double tap.
#define ADXL345_ACT_TAP_STATUS  0x2B // R   Source of tap/double tap.
#define ADXL345_INT_ENABLE      0x2E // R/W Interrupt enable control.
#define ADXL345_DUR             0x21 // R/W Tap duration.
#define ADXL345_THRESH_TAP      0x1D // R/W Tap threshold.
#define ADXL345_INT_MAP         0x2F // R/W Interrupt mapping control.
#define ADXL345_SINGLE_TAP      (1 << 6)
#define ADXL345_TAP_Z_EN        (1 << 0)
#define WIDTH 15
#define HEIGHT 4
#define X_LEFT -50
#define X_RIGHT 50
#define Y_UP 50
#define Y_DOWN -50
#define MAX_TREES 4


// Forward declaration of ADXL and SPI functions.
int ADXL_INIT();
int ADXL_GETXyz(short *x, short *y, short *z);
int SPI_INIT(int channel);
int SPIMaster(int numWrite, int numRead, unsigned char byte[]);
int SetPowerMode();

// Forward declaration of gameplay functions.
int PlayGame();
int PlayerXMove(int *player_x, int player_y);
int PlayerYMove(int player_x, int *player_y);
int ZombieMove(int player_x, int player_y, int *zombie_x, int *zombie_y);
void SetupTrees();

void DisplaySplash();
void DisplaySetupScreen();
void DisplayEndGame(unsigned int player_score);
void SetupChar();
void SetGamePieces();
void ClearPress();
bool TreeCollision(int x, int y);
bool CheckMove(int x, int y);
void Teleport(int *x, int *y, int zombie_x, int zombie_y);

// Global variable to count number of times in timer2 ISR
unsigned int timer2_ms_value = 0;
unsigned int sample_counter = 0;
short x = 0;
short y = 0;
short z = 0;
short *xp = &x;
short *yp = &y;
short *zp = &z;


struct tree {
    int x;
    int y;
};

int trees;
// Trees are given fixed positions.
struct tree tree_holder[MAX_TREES];


// Variables used to control state and debounce button.
unsigned char Button1History = 0x00;
unsigned char Button2History = 0x00;
unsigned char Button3History = 0x00;
bool Button1Pressed = false;
bool Button2Pressed = false;
bool Button3Pressed = false;
bool Button1StateUpdated = false;
bool Button2StateUpdated = false;
bool Button3StateUpdated = false;


enum direction {
    left,
    right,
    up,
    down,
    none
};

enum direction next = none;

// Controls how fast the player moves depending on tilt.
int x_update_freq = 600;
int y_update_freq = 600;

// The interrupt handler for timer2
// Debounces buttons and signals state changes
// IPL4 medium interrupt priority
// SOFT|AUTO|SRS refers to the shadow register use
void __ISR(_TIMER_2_VECTOR, IPL4AUTO) _Timer2Handler(void) {

    timer2_ms_value++; // Increment the millisecond counter.
    sample_counter++;

    // Get ADXL reading
    if(sample_counter == 10) {
        sample_counter = 0;
        ADXL_GETXyz(xp, yp, zp);
        x_update_freq = (-120 / 41) * abs(x) + 34700 / 41;
        y_update_freq = (-120 / 41) * abs(y) + 34700 / 41;
    }

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
        if(Button1Pressed && Button1StateUpdated) {
            Button1StateUpdated = false;
            Button1Pressed = false;
        }
    }
    if(Button2History == 0x00) {
        if(Button2Pressed && Button2StateUpdated) {
            Button2StateUpdated = false;
            Button2Pressed = false;
        }
    }
    if(Button3History == 0x00) {
        if(Button3Pressed && Button3StateUpdated) {
            Button3StateUpdated = false;
            Button3Pressed = false;
        }
    }

    INTClearFlag(INT_T2); // Acknowledge the interrupt source by clearing flag
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


// Global definitions of our user-defined characters
BYTE blank[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char blank_char = 0x01;
BYTE zombie[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
char zombie_char = 0x00;
BYTE pumpkin[8] = {0x00, 0xe6, 0x84, 0x90, 0x90, 0x86, 0xe4, 0x00};
char pumpkin_char = 0x03;
BYTE tree[8] = {0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff};
char tree_char = 0x2;



/* SPI and ADXL Config and variables */
const unsigned int SPI_SOURCE_CLOCK_DIVIDER = 8;
#define CONFIG  SPI_OPEN_MSTEN | SPI_OPEN_CKP_HIGH |SPI_OPEN_ENHBUF \
                | SPI_OPEN_MODE8  | SPI_OPEN_ON
#define JUNK 0x00
int channel_num = -1;

enum state {
    splash,
    setup,
    game,
    endgame
};



int main() {

    // Set up Oled
    DelayInit();
    OledInit();
    OledClearBuffer();
    OledUpdate();

    // Set up timer and interrupts
    initTimer2();
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
    ADXL_INIT();
    SetupChar();
    SetupTrees();

    // Initialize GPIO
    TRISGCLR = 0xf000;
    ODCGCLR = 0xf000;
    LATGCLR = 0xf000;
    DDPCONbits.JTAGEN = 0;


    unsigned int player_score;
    unsigned int start_time;
    enum state game_state = splash;




    // STATE MACHINE IMPLEMENTAITON OF MAIN GAME STAGES
    while(1) {
        switch(game_state) {
            case(splash): {
                DisplaySplash();
                game_state = setup;
                break;
            } case(setup): {
                DisplaySetupScreen();
                game_state = game;
                break;
            } case(game): {
                start_time = timer2_ms_value;
                PlayGame();
                player_score = timer2_ms_value - start_time;
                game_state = endgame;
                break;
            } case(endgame): {
                DisplayEndGame(player_score);
                game_state = setup;
                break;
            } default: {
                exit(EXIT_FAILURE);
            }
        }
    } 

    return (EXIT_SUCCESS);
}

/*
 * Controls the logic for the zombie game. Places the pieces on the board and
 * then responds to the players input from the  buttons to specify game features
 * and the ACL to specify movement.
 */
int PlayGame()
{
    OledClearBuffer();
    int i = 0;
    for(i = 0; i < trees; i++)
    {
        OledSetCursor(tree_holder[i].x, tree_holder[i].y);
        OledDrawGlyph(tree_char);
    }
    int player_x;
    int player_y;
    // Generate Player Position
    while(1) {
        player_x = rand() % WIDTH;
        player_y = rand() % HEIGHT;

        bool no_collision = true;
        int j = 0;
        for(j = 0; j < trees; j++)
        {
            if(player_x == tree_holder[j].x && player_y == tree_holder[j].y) {
                no_collision= false;
            }
        }
        if(no_collision) {
            break;
        }
    }

    // Generate zombie position
    int zombie_x;
    int zombie_y;
    while(1) {
        zombie_x = rand() % WIDTH;
        zombie_y = rand() % HEIGHT;

        bool no_collision = true;

        if(zombie_x == player_x && zombie_y == player_y) {
            no_collision = false;
        }

        int j = 0;
        for(j = 0; j < trees; j++)
        {
            if(zombie_x == tree_holder[j].x && zombie_y == tree_holder[j].y) {
                no_collision= false;
            }
        }
        if(no_collision) {
            break;
        }
    }

    OledSetCursor(player_x, player_y);
    OledDrawGlyph(pumpkin_char);

    OledSetCursor(zombie_x, zombie_y);
    OledDrawGlyph(zombie_char);
    OledUpdate();

    int zombie_update_freq = 800;
    unsigned int last_x_update = 0;
    unsigned int ms_since_last_x_update;
    unsigned int last_y_update = 0;
    unsigned int ms_since_last_y_update;
    unsigned int last_zombie_update = 0;
    unsigned int ms_since_last_zombie_update;


    while(1) {

        int player_teleport = 0;
        int player_x_move = 0;
        int player_y_move = 0;
        int zombie_move = 0;
        // Update player movement in x direction
        ms_since_last_x_update = timer2_ms_value - last_x_update;
        if(ms_since_last_x_update >= x_update_freq) {
            player_x_move = PlayerXMove(&player_x, player_y);
            last_x_update = timer2_ms_value;
        }

        if(player_x == zombie_x && player_y == zombie_y) {
            return 0;
        }

        // Update player movement in the y direction
        ms_since_last_y_update = timer2_ms_value - last_y_update;
        if(ms_since_last_y_update >= y_update_freq) {
            player_y_move = PlayerYMove(player_x, &player_y);
            last_y_update = timer2_ms_value;
        }

        if(player_x == zombie_x && player_y == zombie_y) {
            return 0;
        }

        // Update Zombie position
        ms_since_last_zombie_update = timer2_ms_value - last_zombie_update;
        if(ms_since_last_zombie_update >= zombie_update_freq) {
            zombie_move = ZombieMove(player_x, player_y, &zombie_x, &zombie_y);
            last_zombie_update = timer2_ms_value;
        }

        if(player_x == zombie_x && player_y == zombie_y) {
            return 0;
        }

        // Respond to user game input.
        if(Button1Pressed && !Button1StateUpdated) {
            if(zombie_update_freq > 200) {
                zombie_update_freq -= 100;
            }
            Button1StateUpdated = true;
        }
        if(Button2Pressed && !Button2StateUpdated) {
            zombie_update_freq += 100;
            Button2StateUpdated = true;
        }
        if(Button3Pressed && !Button3StateUpdated) {
            Teleport(&player_x, &player_y, zombie_x, zombie_y);
            player_teleport = 1;
            Button3StateUpdated = true;
        }

        // Update the Game if any piece has moved.
         if(player_x_move || player_y_move || zombie_move || player_teleport) {
            OledUpdate();
        }
    }
    return 0;
}
/*
 * Move the zombie in the direction of the playre taking in to account distance
 * and game board factors
 */
int ZombieMove(int player_x, int player_y, int *zombie_x, int *zombie_y)
{
    
    OledSetCursor(*zombie_x, *zombie_y);
    OledDrawGlyph(blank_char);

    // Check for direction to navigate around trees
    if(next == up) {
       (*zombie_y)--;
       next = none;
       OledSetCursor(*zombie_x, *zombie_y);
       OledDrawGlyph(zombie_char);
       return 1;
    } else if(next == down) {
        (*zombie_y)++;
        next= none;
        OledSetCursor(*zombie_x, *zombie_y);
        OledDrawGlyph(zombie_char);
        return 1;
    }

    // This section controls the movement of the zombie. It moves zombie
    // around obstacles and towards the player.
    bool zombie_move = false;
    if(*zombie_x > player_x) {
        if(CheckMove(*zombie_x - 1, *zombie_y)) {
            (*zombie_x)--;
            zombie_move = true;
        } else {
            if(*zombie_y > player_y && CheckMove(*zombie_x, *zombie_y -1)) {
                (*zombie_y)--;
                zombie_move = true;
            } else if(*zombie_y < player_x && CheckMove(*zombie_x, *zombie_y +1)) {
                (*zombie_y)++;
                zombie_move = true;
            }
        }
    } else if(*zombie_x < player_x) {
        if(CheckMove(*zombie_x + 1, *zombie_y)) {
            (*zombie_x)++;
            zombie_move = true;
        } else {
            if(*zombie_y > player_y && CheckMove(*zombie_x, *zombie_y -1)) {
                (*zombie_y)--;
                zombie_move = true;
            } else if(*zombie_y < player_x && CheckMove(*zombie_x, *zombie_y +1)) {
                (*zombie_y)++;
                zombie_move = true;
            }
        }
    } else {
        if(*zombie_y > player_y) {
            if(CheckMove(*zombie_x, *zombie_y -1)) {
                (*zombie_y)--;
            } else {
                next = up;
                (*zombie_x)--;
            }
        } else {
            if(CheckMove(*zombie_x, *zombie_y +1)) {
                (*zombie_y)++;
            } else {
                (*zombie_x)--;
                next = down;

            }
        }
    }
    OledSetCursor(*zombie_x, *zombie_y);
    OledDrawGlyph(zombie_char);
    return 1;
}

/*
 * Move the player in the x direciton depending on game board factors and tilt
 * of ACL
 */
int PlayerXMove(int *player_x, int player_y)
{
    if(x <= X_LEFT && (*player_x) < WIDTH &&
            !TreeCollision(*player_x + 1, player_y)) {
        OledSetCursor(*player_x, player_y);
        OledDrawGlyph(blank_char);
        (*player_x)++;
        OledSetCursor(*player_x, player_y);
        OledDrawGlyph(pumpkin_char);
        return 1;
    } else if(x >= X_RIGHT && (*player_x) > 0 &&
                !TreeCollision(*player_x - 1, player_y)) {
        OledSetCursor(*player_x, player_y);
        OledDrawGlyph(blank_char);
        (*player_x)--;
        OledSetCursor(*player_x, player_y);
        OledDrawGlyph(pumpkin_char);
        return 1;
    }
    return 0;
}

/*
 * Move the player in the y direciton depending on game board factors and tilt
 * of ACL
 */
int PlayerYMove(int player_x, int *player_y)
{    
    if(y <= Y_DOWN && (*player_y) > 0 &&
            !TreeCollision(player_x, *player_y - 1)) {
        OledSetCursor(player_x, *player_y);
        OledDrawGlyph(blank_char);
        (*player_y)--;
        OledSetCursor(player_x, *player_y);
        OledDrawGlyph(pumpkin_char);
        return 1;
    } else if (y >= Y_UP && (*player_y) < HEIGHT &&
            !TreeCollision(player_x, *player_y + 1)) {
        OledSetCursor(player_x, *player_y);
        OledDrawGlyph(blank_char);
        (*player_y)++;
        OledSetCursor(player_x, *player_y);
        OledDrawGlyph(pumpkin_char);
        return 1;
    }
    return 0;
}
/*
 * Check if position collides with tree on game board.
 */
bool TreeCollision(int x, int y)
{
    int i = 0;
    for(i = 0; i < trees; i++)
    {
        if(x == tree_holder[i].x && y == tree_holder[i].y) {
            return true;
        }
    }
    return false;
}

/*
 * Display initial game message for 2 seconds.
 */
void DisplaySplash()
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("OLED ZOMBIES!");
    OledSetCursor(0, 1);
    OledPutString("Michael Feneley");
    OledSetCursor(0, 2);
    OledPutString("ECE 2574");
    OledUpdate();
    DelayMs(2000);
}
/*
 * Display setup screen and change game setting based on user input.
 */
void DisplaySetupScreen()
{
    // Default
    trees = 0;
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("Btn1: Add Tree");
    OledSetCursor(0, 2);
    OledPutString("Btn3: Start");
    OledSetCursor(0, 3);
    char buf[17];
    sprintf(buf, "Num Trees: %d", trees);
    OledPutString(buf);
    OledUpdate();

   
    // Loop and change game depdnding on user input.
    while(1) {
        if(Button1Pressed && !Button1StateUpdated) {
            if(trees < MAX_TREES) {
                trees++;
            }
            OledSetCursor(0, 3);
            sprintf(buf, "Num Trees: %d", trees);
            OledPutString(buf);
            OledUpdate();
            Button1StateUpdated = true;
        } else if (Button2Pressed &!Button2StateUpdated) {
            Button2StateUpdated = true;
        } else if(Button3Pressed && !Button3StateUpdated) {
            Button3StateUpdated = true;
            return;
        }
    }
}
/*
 * Display end game message until button 1 is pressed.
 */
void DisplayEndGame(unsigned int player_score)
{
    OledClearBuffer();
    OledSetCursor(0, 0);
    OledPutString("Game Over!       ");
    OledSetCursor(0, 1);
    char buf[17];
    sprintf(buf, "Score: %d sec", player_score / 1000);
    OledPutString(buf);
    OledSetCursor(0, 2);
    OledPutString("To Restart");
    OledSetCursor(0, 3);
    OledPutString("Press Button 1");
    OledUpdate();

    // Restart game on button press.
    while(1) {
        if(Button1Pressed && !Button1StateUpdated) {
            Button1StateUpdated = true;
            return;
        }
    }
}


/*
 * Defines the shapes for the game pieces.
 */
void SetupChar()
{
    OledDefUserChar(blank_char, blank);
    OledDefUserChar(zombie_char, zombie);
    OledDefUserChar(pumpkin_char, pumpkin);
    OledDefUserChar(tree_char, tree);
}

/*
 * Setup the ADXL for input and output. Connect to either JE or JF connector.
 */
int ADXL_INIT(){

    unsigned char byte[2];
    byte[0] = ADXL345_DEVID | ADXL345_SPI_READ;

    SPI_INIT(SPI_CHANNEL3);
    SPIMaster(1, 1, byte);
    if(byte[1] == ADXL345_ID) {
        SetPowerMode();
        return SPI_CHANNEL3;
    }

    SPI_INIT(SPI_CHANNEL4);
    SPIMaster(1, 1, byte);
    if(byte[1] == ADXL345_ID) {
        SetPowerMode();
        return SPI_CHANNEL4;
    }

    return -1;
}

/*
 * Configure SPI for input and output on argument channel.
 */
int SPI_INIT(int channel)
{
    if(channel == SPI_CHANNEL3) {
        mPORTDSetPinsDigitalOut(BIT_14);
        mPORTDSetBits(BIT_14);
        channel_num = SPI_CHANNEL3;
    } else if(channel == SPI_CHANNEL4) {
        mPORTFSetPinsDigitalOut(BIT_12);
        mPORTFSetBits(BIT_12);
        channel_num = SPI_CHANNEL4;
    } else {
        channel_num = -1;
        return -1;
    }
    SpiChnOpen(channel, CONFIG, SPI_SOURCE_CLOCK_DIVIDER);
    return 0;
}

/*
 * Reads the acceleartion data from the ADXL.
 */
int ADXL_GETXyz(short *x, short *y, short *z)
{
    unsigned char byte[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned char firstRegAddress = ADXL345_DATAX0;

    byte[0] = ADXL345_SPI_READ | ADXL345_SPI_MB | firstRegAddress;

    SPIMaster(1, 6, byte);
    *x = ((short)byte[2] << 8) + byte[1];
    *y = ((short)byte[4] << 8) + byte[3];
    *z = ((short)byte[6] << 8) + byte[5];
    return 0;
}

/*
 * SPI Master provides the input/output interface for the SPI.
 */
int SPIMaster(int numWrite, int numRead, unsigned char byte[])
{
    // Deassert the correct bit.
    if(channel_num == SPI_CHANNEL3) {
        mPORTDClearBits(BIT_14);
    } else if(channel_num == SPI_CHANNEL4) {
        mPORTFClearBits(BIT_12);
    } else {
        return -1;
    }

    int j = 0;
    for(j = 0; j < numWrite; j++)
    {
        SpiChnPutC(channel_num, byte[j]);
        SpiChnGetC(channel_num);
    }

    int i = numWrite;
    for(i = numWrite; i < numRead + numWrite; i++)
    {
        SpiChnPutC(channel_num, 0x00);
        unsigned char val = SpiChnGetC(channel_num);
        byte[i] = val;
    }

    // Reassert the correct bit.
    if(channel_num == SPI_CHANNEL3) {
        mPORTDSetBits(BIT_14);
    } else if(channel_num == SPI_CHANNEL4) {
        mPORTFSetBits(BIT_12);
    }

   return 0;
}

/*
 * Sets the mode of the ADXL to measure mode so data can be read.
 */
int SetPowerMode()
{
    int pwrMode = 1;
    unsigned char oldPowerCtl = 0;
    unsigned char newPowerCtl = 0;

    unsigned char powervalue[2] = {0, 0};

    powervalue[0] = ADXL345_SPI_READ | ADXL345_POWER_CTL;
    SPIMaster(1, 1, powervalue);

    oldPowerCtl = powervalue[0];
    newPowerCtl = oldPowerCtl & ~ADXL345_PCTL_MEASURE;
    newPowerCtl = newPowerCtl | (pwrMode * ADXL345_PCTL_MEASURE);

    unsigned char newPowervalue[2] = {0, 0};
    newPowervalue[0] = (BIT_7 & 0) | (BIT_6 & 0) | (ADXL345_POWER_CTL);
    newPowervalue[1] = newPowerCtl;
    SPIMaster(2, 0, newPowervalue);

    return 1;
}

/*
 * Sets the fixed position of the game trees.
 */
void SetupTrees()
{
    tree_holder[0].x = 1;
    tree_holder[0].y = 1;
    tree_holder[1].x = 4;
    tree_holder[1].y = 1;
    tree_holder[2].x = 7;
    tree_holder[2].y = 2;
    tree_holder[3].x = 11;
    tree_holder[3].y = 1;
}

/*
 * Check if the move to position (, y) is valid.
 */
bool CheckMove(int move_x, int move_y)
{
    if(TreeCollision(move_x, move_y)) {
        return false;
    } else if (move_x < 0 || move_x > WIDTH || move_y < 0 || move_y > HEIGHT) {
        return false;
    } else {
        return true;
    }
}

/*
 * Moves the player to a new random position on the game board.
 */
void Teleport(int *x, int *y, int zombie_x, int zombie_y) {

    OledSetCursor(*x, *y);
    OledDrawGlyph(blank_char);

    while(1) {
        *x = rand() % WIDTH;
        *y = rand() % HEIGHT;

        bool no_collision = true;

        if(zombie_x == *x && zombie_y == *y) {
            no_collision = false;
        }

        int j = 0;
        for(j = 0; j < trees; j++)
        {
            if(*x == tree_holder[j].x && *y == tree_holder[j].y) {
                no_collision= false;
            }
        }
        if(no_collision) {
            OledSetCursor(*x, *y);
            OledDrawGlyph(pumpkin_char);
            return;
        }        
    }
}