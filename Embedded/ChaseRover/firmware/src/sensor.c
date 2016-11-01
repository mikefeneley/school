
#include "sensor.h"
#include "timers.h"
#include "queue.h"
#include "coordinator_public.h"
#include "debug.h"
#include "sensor_public.h"
#include "sensor_timer.h"

QueueHandle_t sensor_queue1 = NULL;
TimerHandle_t sensor_timer1 = NULL;

static int coordinator_message_count = 0;


void SENSOR_Initialize ( void )
{
   sensor_timer1 = xTimerCreate("Timer1",50, pdTRUE, 0 , sensor_timer1_callback);
   sensor_queue1 = xQueueCreate(100, sizeof(sensor_recieve_message));
   xTimerStart(sensor_timer1, 0);
   DRV_ADC_Open();    
}

int latest = -1;


/******************************************************************************
  Function:
    void SENSOR_Tasks ( void )

  Remarks:
    See prototype in sensor.h.
 */


int holder1[10];
int holder2[10];
int i = 0;
int j = 0;

void SENSOR_Tasks ( void )
{
    for(;;){

        sensor_recieve_message sensor_message;

       
        
		if(xQueueReceive(sensor_queue1, &sensor_message, portMAX_DELAY )){
            
            int val = sensor_message.val;
            int source = sensor_message.source;
            
            if(source == ULTRASONIC) {
                holder1[i] = val;
                i++;
                
                if(i == 9) {
                    int counter = 0;
                    int sum = 0;
                    for(counter = 0; counter < 10; counter++)
                    {
                        sum += holder1[counter];
                    }
                    int average = sum / 9;
                    char message[11];
                    sprintf(message, "BOT%9dM", average);
                    send_debug_message(message);
                    i = 0;
                    
                                                           
                    coordinator_receive_message msg; 
                    msg.source = ULTRASONIC;
                    
                    if(average < 0) {
                        msg.val = ONE;
                    } else {
                        msg.val = ZERO; 
                    }
                    
                    
                    send_to_coordinator(&msg);
                    
                }              
            } else if(source == IR_SENSOR1) {
                holder2[j] = val;
                j++;
                
                if(j == 9) {
                    int counter = 0;
                    int sum = 0;
                    for(counter = 0; counter < 10; counter++)
                    {
                        sum += holder2[counter];
                    }
                    int average = sum / 9;
                    char message[11];
                    sprintf(message, "TOP%9dP", average);
                    send_debug_message(message);
                    j = 0;
                    
                    coordinator_receive_message msg; 
                    msg.source = IR_SENSOR1;
                    msg.val = ZERO;
                    send_to_coordinator(&msg);
                }                
            }           
        }
    }
}
 
/*******************************************************************************
 End of File
 
 
             
            latest = sensor_message.val;

            holder[i] = latest;
            i++;
            if(i == 9) {
                
                int j;
                
                j = 0;
                int sum = 0;
                for(j = 0; j < 10; j++)
                {
                    sum += holder[j];
                }
                int average = sum / 9;
                coordinator_receive_message msg;
                msg.source = ULTRASONIC;
                if(average < 800 && latest != -1) {                    
                    char message[11] = "<OneOnenOn>";
                    send_debug_message(message);
                    sprintf(message, "Z%9dM", average);
                    send_debug_message(message);
                    msg.val = ONE;
                } else {
                    
                    char message[11] = "<ZeroZero0>";
                    send_debug_message(message);
                    sprintf(message, "Q%9dR", average);
                    send_debug_message(message);                   
                    msg.val = ZERO;
                }
     
                send_to_coordinator(&msg);
                i = 0;
             
            }
 
 
 
 
 
 
 
 
 
 */
