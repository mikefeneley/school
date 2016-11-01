/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "queue.h"
/*
 * WiFly
 * Orange Point = Access Point
 * Green Wire = Client
 */

/* Message sources*/
#define MONITOR 0x0
#define MESSAGE 0x1
#define SENSOR 0x2
#define COORDINATOR 0x3
#define MOTOR 0x4

#define ZERO 48
#define ONE 49

#define START_CMD 0

#define COMMAND 48
#define IR_SENSOR1 49
#define IR_SENSOR2 50
#define IR_SENSOR3 51
#define ULTRASONIC 52
#define MSG_LENGTH 11

#define LEFT 76
#define RIGHT 82
#define STOP 83
#define FORWARD 70

#define START 'S'
#define DONE 'D'


#define IR_SENSOR1_SEND 0x9
#define SENSOR_REC 0x10
#define SENSOR_SEND 0x11
#define COORD_REC 0x12
#define COORD_SEND 0x13
#define MOTOR_REC 0x14
#define MONITOR_REC 0x15
#define MONITOR_SEND 0x16
#define MESSAGE_REC 0x17

void WRITE_MSG(uint16_t message);

void xQueueReceive_D(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);


#endif /* _DEBUG_H */

/* *****************************************************************************
 End of File
 */
