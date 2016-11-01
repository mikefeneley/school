#include "motor.h"
#include "motor_public.h"
#include "queue.h"

extern QueueHandle_t motor_queue1;

void send_to_motor(motor_receive_message *motor_msg)
{
    xQueueSend(motor_queue1, (void *)motor_msg, portMAX_DELAY);
}

