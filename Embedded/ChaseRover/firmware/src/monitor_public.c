#include "monitor_public.h"
#include "queue.h"
#include "debug.h"

extern  QueueHandle_t monitor_queue1;





void send_debug_message(char message[11])
{
 
    if(monitor_queue1 != NULL) {
        wifly_message wifly_msg;

        int i = 0;    
        for(i = 0; i < MSG_LENGTH; i++)
        {
            wifly_msg.message[i] = message[i];
        }

        xQueueSend(monitor_queue1, (void *)&wifly_msg, portMAX_DELAY); 
    }

}