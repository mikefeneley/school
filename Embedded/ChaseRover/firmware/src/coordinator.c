#include "FreeRTOSConfig.h"
#include "coordinator.h"
#include "queue.h"
#include "debug.h"
#include "timers.h"
#include "coordinator_timer1.h"
#include "coordinator_public.h"
#include "motor_public.h"
#include "monitor_public.h"
#include <stdlib.h>
/* The queue used by the task and timer. */
QueueHandle_t coordinator_queue1 = NULL;


void COORDINATOR_Initialize ( void )
{  
   srand(NULL);
   coordinator_queue1 = xQueueCreate( 30, sizeof(coordinator_receive_message));
}

typedef enum _state {
    waiting = 1,
    init = 2,
    searching = 3,
    turning = 4,        
} game_state;

typedef enum _move {
    going = 1,
    not_going = 2,
    right = 3,
    left = 4,
} move_state;

move_state move = not_going;

game_state state = waiting;

int ir_1 = -1;
int ultrasonic = -1;

/* Turn 90 degrees left to face victim rover */
void turn_left()
{
    motor_receive_message msg;
    msg.val = 90;
    msg.command = '5';     
    send_to_motor(&msg); 
    char message[11] = "<    C   L>";
    send_debug_message(message);
}

/* Turn a random number of degrees to avoid wall */
void turn_left_random()
{
    int degrees = (rand() % 70) + 20;
    motor_receive_message msg;
    msg.val = degrees;
    msg.command = '5';     
    send_to_motor(&msg); 
    
    char message[11] = "<    C   ?>";
    send_debug_message(message); 
}

/* Turn 90 degrees right to face victim rover */
void turn_right()
{
    /* Send right command to motor */    
    motor_receive_message msg;
    msg.val = 90;
    msg.command = '4';   
    send_to_motor(&msg); 
    
    /* Send right command over wifly for testing */    
    char message[11] = "<    C   R>";
    send_debug_message(message);
}

/* Start moving forward until stop command */
void forward()
{
    /* Send forward command to motor */    
    motor_receive_message msg;
    msg.command = '1';    
    send_to_motor(&msg);    

    /* Send forward command over wifly for testing */    
    char message[11] = "<    C   F>";
    send_debug_message(message);
}

/* Stop rover from moving forward */
void stop()
{
    /* Send stop command to motor */
    motor_receive_message msg;
    msg.command = '3';    
    send_to_motor(&msg);
    
    /* Send stop command over wifly for testing */
    char message[11] = "<    C   S>";
    send_debug_message(message);
}

/* Send game won message over wifly and reset state*/
void game_won()
{   
    /* Send stop command to motor */
    motor_receive_message msg;
    msg.command = '3';    
    send_to_motor(&msg);
    
    /* Send stop command over wifly for testing */
    state = waiting;
    char message[11] = "<    C   W>";
    send_debug_message(message);
}

/* This function sends an ack message to coordinator indicating the game
 * is ready to be played.
 */
void send_start()
{
    char *message = "<A>";
    send_debug_message(message);
}


void COORDINATOR_Tasks (void)
{
    coordinator_receive_message coordinator_message;    
    
    for(;;)
    {
        if(xQueueReceive( coordinator_queue1,(void*)&coordinator_message, portMAX_DELAY )) 
        {            
            char source = coordinator_message.source;
            char val = coordinator_message.val;
         
            /* Update sensor values depending on msg source and val */
            if(source == IR_SENSOR1) {
                ir_1 = val;
            } else if(source == ULTRASONIC) {
                ultrasonic = val;
            } 
            
            /*Special case message starts the game */
            if(source == START) {
                send_start();
                state = init;
                move = not_going;
                ir_1 = -1;
                ultrasonic = -1;
            } else if(source == DONE) { /* Special case message indicates end of turn */
                state = init;
                move = not_going;
                ir_1 = -1;
                ultrasonic = -1;
            }
                        
            if(state == init) { /* Delays decision until new data recieved */             
                if(ir_1  != -1 && ultrasonic != -1){
                    state = searching;
                }
            } else if(state == searching) { /* Analyze and make move decision */
                
                if(ultrasonic == ONE) { /* Turn left if wall in front */
                    turn_left_random();
                    state = turning;
                    move = left;
                } else if(ir_1 == ONE) { /* Game is won if detected in front */
                    game_won();
                } else                    
                    /* Send move command if we aren't already moving */
                    if(move != going) {
                        forward();
                        move = going;
                    }            
            } else if(state == turning) { /* Wait for rover to finish turning before making next move */
                Nop();
            }
        }       
    }
 }