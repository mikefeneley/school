#ifndef _MONITOR_H
#define _MONITOR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"


void MONITOR_Initialize ( void );
void MONITOR_Tasks( void );
void check_coordinator_msg_count(int coordinator_count, int msg_count);
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

