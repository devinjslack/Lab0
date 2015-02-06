/*
* File:   initLab0.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

void initLEDs(){
    //TODO: Initialize the pin connected to the LEDs as outputs
    //LED4-7 connected to 23-26


    //initilize all LEDs to output (0)
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;

    //TODO: Turn each LED OF
}

void initSW1(){
    //TODO: Initialize the pin connected to the switch as an input.

    TRISBbits.TRISB5 = 1;

    //switch connected to pin 14 RB5
    
}

#define FCY 14745600.0
#define ONE_MILLISECOND 57
#define TIME_DELAY .025

void initTimer1(){
    //TODO: Initialize the timer
    unsigned int prVal = (FCY*TIME_DELAY)/256.0 - 1;
    PR1 = prVal;
    T1CONbits.TCKPS = 0b11; //prescalar 256
    IEC0bits.T1IE = 1; // Enable the interrupt
    IFS0bits.T1IF = 0; // Put the interrupt flag down
    T1CONbits.TON = 1;//Turn the timer 1 on but turn off when switch is released
}

void initChange(){
    IFS1bits.CNIF = 0; //Put the CN flag down
    CNEN2bits.CN27IE = 1; //enable the CN interupt on pin 14
    IEC1bits.CNIE = 1;//enable all CN
}