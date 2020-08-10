#include "Includes.h"


U32 distance_1 = 0;
U32 distance_2 = 0;

U8 flag = 0;
U8 hema;
int i = 0;
int x = 15999;
void delayMs(int n);
volatile U32 adcresult = 1234;
volatile U16 adcresult2 = 0;
#define OutInHZ 10000
#define DUTYCYCLE 0
#define PWMNum PWM1
#define baudrate 9600

U16 pwm = 5000;
U16 Spwm = 15999;
U8* recive_data;
void main(void)
{
    UARTBEGIN(UART0, PORTA, 9600);
    UARTBEGIN(UART3, PORTC, 9600);

//    delayMs(7000);
    PinMode(PORTF, PIN3, OUTPUT); //Dir-1
    PinMode(PORTF, PIN1, OUTPUT); //Dir-2

    PinMode(PORTB, PIN5, OUTPUT); //PWM-1
    PinMode(PORTB, PIN7, OUTPUT); //PWM-2

    PWMInt(PWM1, GEN3, PWMPIN7,DOWNMODE, 1000, 50);
    PWMInt(PWM1, GEN2, PWMPIN5,DOWNMODE, 1000, 50);
    stop();



    while (1)
    {

        recive_data = UARTReciveString(UART3);
        /*
        UARTSendString(recive_data,UART0);
        UARTSendString("\n",UART0);
         */
        if (recive_data[0] == 'F'){
            forward(pwm);

        }else if (recive_data[0] == 'B') {
            backward(pwm);
        }else if (recive_data[0] == 'L')
        {
            left();
        }else if (recive_data[0] == 'R') {
            right();
        }else if (recive_data[0] == 'G') {
            forward_left(pwm);
        }else if (recive_data[0] == 'I') {
            forward_right(pwm);
        }else if (recive_data[0] == 'H') {
            backward_left(pwm);
        }else if (recive_data[0] == 'J') {
            backward_right(pwm);
        }else {
            stop();
        }


    }
}



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

void adc0(void)
{
    flag = 1;
    ClearAdcInterruptFlag(ADC0, SS3);
}
void adc1(void)
{
    //    SetBit(GETREG(BaseADCAdress,ADCISC,ADC1), SS3); //CLEAR FLAG

    flag = 1;
    adcresult2 = GETREG(BaseADCAdress, ADCSSFIFO3, ADC1);
    ClearAdcInterruptFlag(ADC1, SS3);
}
void delayMs(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++)
        {
        } /* do nothing for 1 ms */
}

void delayMicro(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++)
        {
        } /* do nothing for 1 micros */
}


void I2CC2(void)
{
    DigitalTogle(LEDPORT, RED);

    //    hema = GETREG(BaseI2CAdress, I2CSDR, I2C2);
    //    SetBit(GETREG(BaseI2CAdress,I2CSICR,I2C2), 0);
    SetBit(GETREG(BaseI2CAdress,I2CMICR,I2C2), 0);


}

void I2CC1(void)
{

    DigitalTogle(LEDPORT, GREEN);
    hema = GETREG(BaseI2CAdress, I2CSDR, I2C1);
    //    SetBit(GETREG(BaseI2CAdress,I2CMICR,I2C1), 0);
    SetBit(GETREG(BaseI2CAdress,I2CSICR,I2C1), 0);

}
void I2CC0(void)
{

    DigitalTogle(LEDPORT, RED);

    hema = GETREG(BaseI2CAdress, I2CSDR, I2C0);
    SetBit(GETREG(BaseI2CAdress,I2CSICR,I2C0), 0);
    //    SetBit(GETREG(BaseI2CAdress,I2CMICR,I2C0), 0);

}

void I2CC3(void)
{

    DigitalTogle(LEDPORT, GREEN);

    hema = GETREG(BaseI2CAdress, I2CSDR, I2C3);

    //    SetBit(GETREG(BaseI2CAdress,I2CMICR,I2C3), 0);
    SetBit(GETREG(BaseI2CAdress,I2CSICR,I2C3), 0);


}

int I2C_wait_till_done(void)
{
    while (GETREG(BaseI2CAdress, I2CMCS, I2C0) & 1)
        ; /* wait until I2C master is not busy */
    return (GETREG(BaseI2CAdress, I2CMCS, I2C0) & 0xE); /* return I2C error code */
}




