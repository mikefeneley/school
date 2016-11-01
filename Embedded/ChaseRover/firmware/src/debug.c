#include"debug.h"
#include "FreeRTOSConfig.h"
#include "queue.h"


void WRITE_MSG(uint16_t message){
    if(message == 0) {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0xFF);
    } else {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, message);
    }
}


void xQueueReceive_D(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait)
{
    int result = xQueueReceive(xQueue, pvBuffer, xTicksToWait);
    if(result < 0) {
    } else {
        
    }
}
