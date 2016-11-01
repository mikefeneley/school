
#include "motor.h"
#include "timers.h"
#include "FreeRTOSConfig.h"
#include "coordinator.h"
#include "queue.h"
#include "debug.h"
#include "coordinator_public.h"
#include "motor_public.h"
#include "monitor_public.h"
#include "motor_timer.h"

QueueHandle_t motor_queue1 = NULL;
TimerHandle_t motor_timer1 = NULL;
static MOTOR_DATA motor;


static int coordinator_msg_count = 0;
static int monitor_msg_count = 0;
void MOTOR_Initialize ( void )
{
    motor_queue1 = xQueueCreate(50, sizeof(motor_receive_message));
    motor_timer1 = xTimerCreate("MotorTimer1",pdMS_TO_TICKS(2520), pdFALSE, 0 , motor_timer1_callback);
    xTimerStart(motor_timer1,0);
    motor.state = MOTOR_STATE_STOP;
}

void MOTOR_Tasks ( void )
{
    motor_receive_message motor_message;

    for(;;)
    {
        
        switch(motor.state){
            case MOTOR_STATE_STOP:
            {
                char message[11] = "<STOPSTOP>";
                send_debug_message(message);
                PLIB_PORTS_Write( PORTS_ID_0, PORT_CHANNEL_D, 0x0 ); //Disable channel 1 and 2 (bit 0 and 1)
                Nop();
                motor.state = MOTOR_STATE_WAITING;
            }
                break;
            case MOTOR_STATE_FORWARD:
            {
                char message[11] = "<FORWARD>";
                send_debug_message(message);
                PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0x3 ); //Enable channel 1 and 2 (bit 0 and 1)
                PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14); //set channel 1 direction
                PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1); //set channel 2 direction
         
                motor.state = MOTOR_STATE_WAITING;
            }
                break;
            case MOTOR_STATE_LEFT_TURN:
            {
                char message[11] = "<LEFTTURN>";
                send_debug_message(message);
                PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0x3 ); //Enable channel 1 and 2 (bit 0 and 1)
                PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14); //set channel 1 direction
                PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1); //set channel 2 direction
                if(motor.parameter>0){
                    xTimerChangePeriod(motor_timer1,motor.parameter * pdMS_TO_TICKS(14),pdMS_TO_TICKS(50));
                }
                xTimerReset(motor_timer1,pdMS_TO_TICKS(50));
                motor.state = MOTOR_STATE_WAITING;                
            }
                break;       
            case MOTOR_STATE_RIGHT_TURN:
            {   char message[11] = "<RIGHTTURN>";
                send_debug_message(message);
                PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0x3 ); //Enable channel 1 and 2 (bit 0 and 1)
                PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14); //set channel 1 direction
                PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1); //set channel 2 direction
                if(motor.parameter>0){
                    xTimerChangePeriod(motor_timer1,motor.parameter * pdMS_TO_TICKS(14),pdMS_TO_TICKS(50));
                }
                xTimerReset(motor_timer1,pdMS_TO_TICKS(50));
                motor.state = MOTOR_STATE_WAITING;               
            }
                break;
            case MOTOR_STATE_REVERSE:
            {   char message[11] = "<REVERSE>";
                send_debug_message(message);
                PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0x3 ); //Enable channel 1 and 2 (bit 0 and 1)
                PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14); //set channel 1 direction
                PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1); //set channel 2 direction
                
                motor.state = MOTOR_STATE_WAITING;
            }
                break;
            case MOTOR_STATE_ERROR:
            {
            
            }
                break;
            case MOTOR_STATE_WAITING:
            {
                if(xQueueReceive( motor_queue1, (void*)&motor_message, portMAX_DELAY )) {
                    
                    WRITE_MSG(MOTOR_REC);
                    motor.state = (MOTOR_STATE)(motor_message.command - 48);
                    motor.parameter = motor_message.val;         
                }
            }
                break;
            default:
            {
                motor.state = MOTOR_STATE_ERROR;
            }
                break;
        }
    }
}

