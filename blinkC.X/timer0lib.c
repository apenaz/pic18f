/*
 * File:   timer0lib.c
 * Author: Aluno
 *
 * Created on 3 de Setembro de 2019, 20:16
 */


#include <xc.h>
#include "timer0lib.h"

void configTimer0(unsigned char prescalerValue)
{
    T0CS = 0;//FONTE DE CLOCK : CLOCK DE INSTRUÇÃO INTERNO
    PSA = 0;//PRESCALER ASSOCIADO AO TIMER 0
    T0CON = T0CON&0b11111000;//ZERANDO OS 3 ULTIMOS VALORES BITS
    T0CON = T0CON|prescalerValue;//SETANDO VALOR DO PRESCALER
    TMR0ON = 1; //LIGAR TIMER0
}

void setTimer0Value(unsigned char value)
{
    TMR0 = value;
}

unsigned char getTimer0Value(void)
{
    return(TMR0);
}

void resetTimer0(void)
{
    TMR0 = 0x00;
}

void enableTimer0ISR(void)
{
    T0IE = 1;
    TMR0IF = 0;
}
