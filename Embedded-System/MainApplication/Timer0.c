/*
 * Timer0.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Ahmed Magdy
 */
#include"stdtypes.h"
#include"util.h"
#include"GPIO.h"
#include"Timer0.h"
U32 N=0;
void Timer0_Delay(U32 ttime)
{
    SET_BIT(RCGCTIMER,0);    //Enable clock for timer0

    CLR_BIT(GPTMCTL,0);      //Disable timer0 during configuration


    GPTMCFG=0x04;

    GPTMTAMR = 0x02;     //Select one shot timer& Down count selection

    GPTMTAILR = 16-1;  //Set clock to 16MHZ
    SET_BIT(GPTMICR,0);       //Clear flag

    SET_BIT(GPTMCTL,0);        //Enable timer0
    for(N=0;N<(ttime/2);N++)
    {
        while((GET_BIT(GPTMRIS,0))==0); //wait for TimerA timeout flag to set*/
        SET_BIT(GPTMICR,0);       //Clear flag
    }
}

void Timer3_Count_Init(void){


    SET_BIT(RCGCTIMER,3);    //Enable clock for timer3
    SET_BIT(RCGCGPIO,1);        //enable GPIO clock

    CLR_BIT(GETREG(BaseGBIOAdress,GPIODIR,PORTB),2);
    SET_BIT(GETREG(BaseGBIOAdress,GPIODEN,PORTB),2);
    SET_BIT(GETREG(BaseGBIOAdress,GPIOAFSEL,PORTB),2);
    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) &=~0x00000F00;
    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) |=0x00000700;

    CLR_BIT(GPTMCTL3,0);      //Disable timer0 during configuration


    GPTMCFG3=0x04;

    GPTMTAMR3 = 0x17;     //Select one shot timer& Down count selection
    SET_BIT(GPTMCTL3, 2);
    SET_BIT(GPTMCTL3, 3);
    SET_BIT(GPTMCTL3,0);        //Enable timer3 to start counting
}

U32 Timer3_Count_Ret(void){

    SET_BIT(GPTMICR3,2);
    while(GET_BIT(GPTMRIS3, 2)==0){}
    U32 duration1 =  GPTMTAR3;


    SET_BIT(GPTMICR3,2);
    while(GET_BIT(GPTMRIS3, 2)==0){}
    U32 duration2 =   GPTMTAR3;


    return (duration2 - duration1) &0x00FFFFFF;

}




void Timer2_Count_Init(void){

    SET_BIT(RCGCTIMER,2);    //Enable clock for timer2
    SET_BIT(RCGCGPIO,1);        //enable GPIO clock
    SET_BIT(RCGCGPIO,5);        //enable GPIO clock
    CLR_BIT(GETREG(BaseGBIOAdress,GPIODIR,PORTB),0);
    CLR_BIT(GETREG(BaseGBIOAdress,GPIODIR,PORTF),4);
    SET_BIT(GETREG(BaseGBIOAdress,GPIODEN,PORTB),0);
    SET_BIT(GETREG(BaseGBIOAdress,GPIODEN,PORTF),4);
    SET_BIT(GETREG(BaseGBIOAdress,GPIOAFSEL,PORTB),0);
    SET_BIT(GETREG(BaseGBIOAdress,GPIOAFSEL,PORTF),4);

    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) &=~0x0000000F;
    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) |=0x00000007;

    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) &=~0x000F0000;
    GETREG(BaseGBIOAdress,GPIOPCTL,PORTB) |=0x00070000;

    CLR_BIT(GPTMCTL2,0);      //Disable timer0 during configuration


    GPTMCFG2=0x04;

    GPTMTAMR2 = 0x17;     //Select one shot timer& Down count selection

    SET_BIT(GPTMCTL2, 2);
    SET_BIT(GPTMCTL2, 3);

    SET_BIT(GPTMCTL2,0);        //Enable timer3 to start counting
}

U32 Timer2_Count_Ret(void){

    SET_BIT(GPTMICR2,2);
    while(GET_BIT(GPTMRIS2, 2)==0){}
    U32 duration1 =  GPTMTAR2;


    SET_BIT(GPTMICR2,2);
    while(GET_BIT(GPTMRIS2, 2)==0){}
    U32 duration2 =   GPTMTAR2;


    return (duration2 - duration1) &0x00FFFFFF;

}
