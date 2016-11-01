#ifndef _MESSAGE_PUBLIC_H    /* Guard against multiple inclusion */
#define _MESSAGE_PUBLIC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"

#define SENSOR_DEST 's'
#define COORD_DEST 'c'
#define MOTOR_DEST 'm'


typedef struct _uart_message {
    char message[250];
} uart_message;

void send_to_message(uart_message *new_message, BaseType_t *pxHigherPriorityTaskWoken);


#endif

