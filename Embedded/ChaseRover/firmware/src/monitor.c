#include "monitor.h"
#include "queue.h"
#include "monitor_public.h"
#include "debug.h"

 QueueHandle_t monitor_queue1;

 static int coordinator_msg_count = 0;
 
/* Monitor file is used to send/recieve traffic from the usart */
void MONITOR_Initialize ( void )
{
    monitor_queue1 = xQueueCreate( 10, sizeof(wifly_message));
}

void MONITOR_Tasks ( void )
{
    while(1) {
    
    wifly_message wifly_msg;    
    /* Output whatver is there to the debug screen */
    if(xQueueReceive( monitor_queue1, &wifly_msg, portMAX_DELAY )) {
        
        
        int i = 0;
        for (i = 0; i < MSG_LENGTH; i++)
        {
            DRV_USART0_WriteByte(wifly_msg.message[i]);
        }
    }     
    }}



/*******************************************************************************
 End of File
 */
