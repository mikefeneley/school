/*******************************************************************************
 System Interrupts File

  File Name:
    system_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <sys/attribs.h>
#include "coordinator.h"
#include "monitor.h"
#include "motor.h"
#include "sensor.h"
#include "system_definitions.h"
#include "coordinator_public.h"
#include "sensor_public.h"
#include "message_public.h"
#include "debug.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

static int coordinator_message_count = 0;
// All distances will be converted to cm
uint32_t frontDistance = 0;
uint32_t leftDistance = 0;
uint32_t rightDistance = 0;

// Temporary values used for calculating distances
uint32_t frontTemp = 0;
uint32_t leftTemp = 0;
uint32_t rightTemp = 0;

// coordinator_receive_message coordinator_msg;
sensor_recieve_message sensor_msg; 

void IntHandlerChangeNotification(void)
{
    
    
    // Front sensor is high
    if(PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1))
    {
        frontTemp = DRV_TMR0_CounterValueGet();
    }
    // Front sensor is low
    else if(!PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1))
    {
        frontDistance = (DRV_TMR0_CounterValueGet() - frontTemp);
        Nop();
        sensor_msg.source = ULTRASONIC;
        sensor_msg.val = frontDistance;
        send_to_sensor_isr(&sensor_msg, pdFALSE);       
    }
    // Left sensor is high
    if(PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2))
    {
        leftTemp = DRV_TMR0_CounterValueGet();
    }
    // Left sensor is low
    else if(!PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2))
    {
        leftDistance = (DRV_TMR0_CounterValueGet() - leftTemp);
        Nop();
        
        sensor_msg.source = IR_SENSOR1;
        sensor_msg.val = frontDistance;
        send_to_sensor_isr(&sensor_msg, pdFALSE);       
    } 
        
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_CHANGE_NOTICE);
}


void IntHandlerDrvTmrInstance0(void)
{

    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);

}

char message[11];
int counter = 0;
int start = 0;
void IntHandlerDrvUsartInstance0(void)
{
    uint8_t val;
    while(!DRV_USART0_ReceiverBufferIsEmpty()) {
        val = DRV_USART0_ReadByte();

        if(!((counter ==0) && val != '<')) {
            message[counter] = val;
            counter++;
        }
    }
    
    if(val == '>') {
        uart_message new_message;
        BaseType_t pxHigherPriorityTaskWoken=pdFALSE;
        
        int i = 0;
        for(i = 0; i < MSG_LENGTH; i++)
        {
            new_message.message[i] = message[i];
        }
        
        
        send_to_message(&new_message, &pxHigherPriorityTaskWoken);
        counter = 0;
        portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);      
    }

    
    /* Clear pending interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);

}
 
 
 

 
 

 

 
 
void IntHandlerDrvOCInstance0(void)

{
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_OUTPUT_COMPARE_3);

}

void IntHandlerDrvOCInstance1(void)

{
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_OUTPUT_COMPARE_4);

}

void IntHandlerDrvOCInstance2(void)

{
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_OUTPUT_COMPARE_5);

}
 
/*******************************************************************************
 End of File
*/

