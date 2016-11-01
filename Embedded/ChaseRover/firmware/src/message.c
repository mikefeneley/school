#include "message.h"
#include "queue.h"
#include "message_public.h"
#include "monitor_public.h"
#include "sensor_public.h"
#include "motor_public.h"
#include "coordinator_public.h"
#include "debug.h"

QueueHandle_t message_queue1 = NULL;

void MESSAGE_Initialize ( void )
{
    message_queue1 = xQueueCreate(50, sizeof(uart_message));
}





void MESSAGE_Tasks ( void )
{
    uart_message new_message;
    
    for(;;)
    {
        if(xQueueReceive(message_queue1, &new_message, portMAX_DELAY )) {

            char source = new_message.message[5];            
            coordinator_receive_message msg;
            msg.source = source;
            msg.val = new_message.message[9];
            send_to_coordinator(&msg);
                
        }
    }
}
