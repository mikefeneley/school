/* 
 * File:   Timer1.c
 * Author: berth
 *
 * Created on February 3, 2016, 10:45 PM
 */
#include "coordinator_timer1.h"
#include "debug.h"


static int minutes = 0;
static int counter = 0;

void coordinator_timer1_callback(TimerHandle_t xTimer){

    counter++;
    if(counter == 12) {
        minutes++;
        counter = 0;
    }    
}