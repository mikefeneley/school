
#ifndef _COORDINATOR_H    /* Guard against multiple inclusion */
#define _COORDINATOR_H



#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"


    
void check_sensor_count(int msg_count, int sensor_msg_count);
void check_ir_value(int val);
void send_status(int minutes, int seconds);
void send_rover_x();
void send_rover_y();
void send_rover_speed();
void send_distance();
void send_time(int minutes, int seconds);
void send_sensor_msg();
void send_motor_msg();
void send_latest_ir();



void COORDINATOR_Initialize ( void );
void COORDINATOR_Tasks(void);


#endif

/* *****************************************************************************
 End of File
 */
