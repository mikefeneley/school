


#include "coordinator_public.h"
#include "queue.h"

/* The queue used by the task and timer. */
extern QueueHandle_t coordinator_queue1;

void send_to_coordinator(coordinator_receive_message *message)
{
    xQueueSend(coordinator_queue1, (void *)message, portMAX_DELAY);
}

