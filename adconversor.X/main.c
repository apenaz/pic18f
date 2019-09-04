/*
 * File:   main.c
 * Author: Aluno
 *
 * Created on 4 de Setembro de 2019, 19:51
 */


#include <xc.h>
#include <pic18f4550.h>
#include "adclib.h"
#include "config_bits.h"
#define _XTAL_FREQ 8000000

void main(void) {
    TRISD = 0x00;
    TRISA0= 1;
    adcConfig(ADC_CLOCK_8,ADC_TAD_6,ADC_CONFIG_0);
    unsigned int valor;
    while(1){
        valor = adcRead(0,RIGHT_JUST);
        LATD = ~valor;
        __delay_ms(50);
    }
    
    return;
}
