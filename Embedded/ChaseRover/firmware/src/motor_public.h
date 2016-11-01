#ifndef _MOTOR_PUBLIC_H 
#define _MOTOR_PUBLIC_H
       

typedef struct _motor_receive_message {
    char command;
    int source;
    int val;    
} motor_receive_message;

void send_to_motor(motor_receive_message *motor_msg);

#endif
