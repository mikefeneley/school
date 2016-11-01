#include "message_public.h"



extern QueueHandle_t message_queue1;

void send_to_message(uart_message *new_message, BaseType_t *pxHigherPriorityTaskWoken)
{
    xQueueSendFromISR(message_queue1, (void*)new_message, pxHigherPriorityTaskWoken);
}
