#include "motion.h"

void forward(U16 x){
    PWMWrite(PWM1, GEN2,x);
    DigitalWrite(PORTB, PIN5,HIGH);

}

void backward(U16 x){
    PWMWrite(PWM1, GEN2,x);
    DigitalWrite(PORTB, PIN5,LOW);

}
void stop(){

    PWMWrite(PWM1, GEN2,0);
    PWMWrite(PWM1, GEN3,0);

}
void left(void){
    PWMWrite(PWM1, GEN3,15999);
    DigitalWrite(PORTB, PIN7,LOW);
}
void right(void){
    PWMWrite(PWM1, GEN3,15999);
    DigitalWrite(PORTB, PIN7,HIGH);
}

void forward_right(U16 x){
    forward(x);
    right();
}

void forward_left(U16 x){
    forward(x);
    left();
}

void backward_right(U16 x){
    backward(x);
    right();
}

void backward_left(U16 x){
    backward(x);
    left();
}
