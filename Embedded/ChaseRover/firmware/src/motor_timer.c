#include "motor_timer.h"
#include "motor_public.h"
#include "debug.h"
#include "coordinator_public.h"


int first = 1;


void motor_timer1_callback(TimerHandle_t xTimer){
    
    
    if(first == 0) {
        char message[11] = "<MCALLBACK>";
        send_debug_message(&message);
        PLIB_PORTS_Write( PORTS_ID_0, PORT_CHANNEL_D, 0x0 ); //Disable channel 1 and 2 (bit 0 and 1)
        coordinator_receive_message msg;
        msg.source = DONE;
        send_to_coordinator(&msg); 
    }
    first = 0;

}