

#ifndef _SENSOR_PUBLIC_H    /* Guard against multiple inclusion */
#define _SENSOR_PUBLIC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

#define SRC_MESSAGE 0x30


typedef struct _sensor_recieve_message {
    int msg_count;
    int source;
    int val;
} sensor_recieve_message;


void send_to_sensor_isr(sensor_recieve_message *sensor_message, BaseType_t *pxHigherPriorityTaskWoken);
void send_to_sensor(sensor_recieve_message *sensor_message);



#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
