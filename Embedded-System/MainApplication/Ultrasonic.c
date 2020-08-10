#include"ultrasonic.h"
#include "Includes.h"
#include "GPIO.h"
#include "Timer0.h"
U32 duration1 = 0;
U32 distance1 = 0;
U32 duration2 = 0;
U32 distance2 = 0;


/* Function Name: Ultrasonic_1
 * Inputs:        Nothing
 * Returns:       U32 distance1
 * Pins :         Pins used for ultrasonic sensor1 using timer3 as counter PA3 (Trigger) - PB2 (Echo)
 * Description:   It used to measure distance using HC SR04 Ultrasonic sensor module
 * */
U32 ultrasonic_1 (void){
    DigitalWrite(PORTA, PIN2, LOW);         //Trigger LOW
    delayMicro(10);
    DigitalWrite(PORTA, PIN2, HIGH);         //Trigger LOW
    delayMicro(10);                    //10 micro-seconds delay
    DigitalWrite(PORTA, PIN2, LOW);         //Trigger-Low
    // Clearing Trigger finished

    duration1 = Timer2_Count_Ret();         //Return counts of trigger detected by timer3
    distance1 = (((float)duration1*(float)0.00340000))/2;   //calculate the distance with the constant speed of sound

    return  distance1;
}



/* Function Name: Ultrasonic_2
 * Inputs:        Nothing
 * Returns:       U32 distance2
 * Pins :         Pins used for ultrasonic sensor1 using timer2 as counter PA2 (Trigger)  -   PB0  (Echo)
 * Description:   It used to measure distance using HC SR04 Ultrasonic sensor module
 * */
U32 ultrasonic_2 (void){
    DigitalWrite(PORTA, PIN2, LOW);         //Trigger LOW
    delayMicro(10);
    DigitalWrite(PORTA, PIN2, HIGH);         //Trigger LOW
    delayMicro(10);                    //10 micro-seconds delay
    DigitalWrite(PORTA, PIN2, LOW);         //Trigger-Low
    // Clearing Trigger finished

    duration2 = Timer3_Count_Ret();                          //Return counts of trigger detected by timer2
    distance2 = (((float)duration2*(float)0.00340000))/2;   //calculate the distance with the constant speed of sound

    return  distance2;
}
