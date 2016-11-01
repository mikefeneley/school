#ifndef _COORDINATOR_PUBLIC_H    /* Guard against multiple inclusion */
#define _COORDINATOR_PUBLIC_H


#include "coordinator.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
 


typedef struct _coordinator_receive_msg {
    int source;
    int val;
} coordinator_receive_message;

  
void send_to_coordinator(coordinator_receive_message *message);

#endif 