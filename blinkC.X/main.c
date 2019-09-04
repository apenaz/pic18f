/*
 * File:   main.c
 * Author: Aluno
 *
 * Created on 3 de Setembro de 2019, 20:15
 */


#include <xc.h>
#include "timer0lib.h"
#include "config_bits.h"

unsigned char cont = 0;

void interrupt IR()
{
    if(T0IF)
    {
        T0IF = 0;
        cont++;
        if(cont >= 61)
        {
            LATD3 = ~LATD3;
            // OU RD3 = ~RD3
            cont = 0x00;
        }
    }
}

void main(void) {
    TRISD = 0x00;//CONFIGURANDO COMO SAÍDA
    //RD3 = 1;//COMEÇA DESLIGADO
    PORTD = 0xFF;
    
    configTimer0(PRESCALER128);
    enableTimer0ISR();
    resetTimer0();
    PEIE = 1;
    GIE = 1;
    
    while(1)
    {
        
    }
    
    return;
}
