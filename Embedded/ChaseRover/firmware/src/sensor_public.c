#include "sensor_public.h"
#include "queue.h"

extern QueueHandle_t sensor_queue1;


void send_to_sensor_isr(sensor_recieve_message *sensor_message, BaseType_t *pxHigherPriorityTaskWoken)
{
    xQueueSendFromISR(sensor_queue1, (void*)sensor_message, pxHigherPriorityTaskWoken);
}

void send_to_sensor(sensor_recieve_message *sensor_message)
{
    xQueueSend(sensor_queue1, (void *)sensor_message, portMAX_DELAY);
}