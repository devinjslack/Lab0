// ******************************************************************************************* //
//
// File:         lab0.c
// Date:         
// Authors:      
//
// Description:  Lab 0 assignment for ECE 372 Spring 2015.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )



typedef enum stateTypeEnum{
    //TODO: Define states by name
D4, D5, D6, D7

} stateType;

stateType currState = D4;

volatile int TCount = 0;

int main(void)
{

    //TODO: Finish these functions in the provided c files
    initLEDs();
    initTimer1();
    initSW1();
    initChange();



    while(1)
    {
        //Use a switch statement to define the behavior based on the state
       switch(currState){
           case D4:
                LATBbits.LATB15 = ON;
                LATBbits.LATB14 = OFF;
                LATBbits.LATB13 = OFF;
                LATBbits.LATB12 = OFF;
           break;

           case D5:
                LATBbits.LATB15 = OFF;
                LATBbits.LATB14 = ON;
                LATBbits.LATB13 = OFF;
                LATBbits.LATB12 = OFF;
           break;

           case D6:
                LATBbits.LATB15 = OFF;
                LATBbits.LATB14 = OFF;
                LATBbits.LATB13 = ON;
                LATBbits.LATB12 = OFF;
           break;

           case D7:
                LATBbits.LATB15 = OFF;
                LATBbits.LATB14 = OFF;
                LATBbits.LATB13 = OFF;
                LATBbits.LATB12 = ON;
           break;

               }
    }
    return 0;
}

void _ISR _T1Interrupt(void){
    //TODO: Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;

    TCount++;//a period of 25ms has elapsed. count increases

    //TODO: Change states if necessary.
    //Make sure if you use any variables that they are declared volatile!
}

void _ISR _CNInterrupt(void){

    IFS1bits.CNIF = 0;//flag goes down
    if(PORTBbits.RB5 == 0)//if the switch isn't pressed, the timer isn't counting
    {
    TCount = 0;
    }
    
    if(PORTBbits.RB5 == 1 && TCount<80)//if the switch is released and it's < 2s
    {
        currState=(currState+1)%4;//count up a state
        TCount = 0;//reset time counter
    }

    else if(PORTBbits.RB5 == 1 && TCount >= 80)//if switch is released and it's >2s
    {
        if(currState==D4)//if it's LED1, go back to LED4
        {
            currState=D7;
            TCount=0;//reset time counter
        }
        else//if it's any state beside D4
        {
            currState=(currState-1)%4;//count backwards
            TCount = 0;
        }
    }
}