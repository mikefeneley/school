#include "sensor_timer.h"
#include "debug.h"
#include "sensor_public.h"

static int sample = 0;
extern int latest;

int counter1 = 0;

void sensor_timer1_callback(TimerHandle_t xTimer){
    char message[11];
    sprintf(message, "F%10d", counter1);
    counter1++;
//    send_debug_message(message);

}   

