
#ifndef _MONITOR_PUBLIC_H    /* Guard against multiple inclusion */
#define _MONITOR_PUBLIC_H

#include "coordinator.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"


typedef struct _wifly_message {
    char message[250];
} wifly_message;


void send_debug_message(char message[11]);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
