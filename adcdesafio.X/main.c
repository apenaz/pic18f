#include <xc.h>
#include "adclib.h"
#include "config_bits.h"
#include "configIO.h"
#include "timer0lib.h"
#include "sevenSeg.h"

#define limite 512
unsigned char contador = 0;
//unsigned char contador1 = 0;

void interrupt ISR() {
    if (T0IF) {
        T0IF = 0;
        contador++;
        if (contador == 61) {
            LATC7 = ~LATC7; // RD3 = ~RD3
            contador = 0x00;
        }
        //contador1++;
        /*if (contador1 == 128) {
            LATD2 = ~LATD2; // RD3 = ~RD3
            contador1 = 0x00;
        }*/
    }
}

int main() {
    //config pin c7 output and led off
    setOutputC(PIN_C7);
    output_highC(PIN_C7);
    // portD as output for display controller
    setInputA(PIN_A0);
    setOutputD(PIN_D0|PIN_D1|PIN_D2|PIN_D3|PIN_D4|PIN_D5|PIN_D6|PIN_D7);
    output_highD(PIN_D0|PIN_D1|PIN_D2|PIN_D3|PIN_D4|PIN_D5|PIN_D6|PIN_D7);
    configTimer0(PRESCALER128);
    enableTimer0ISR();
    resetTimer0();
    GIE = 1;
    
    adcConfig(ADC_CLOCK_8, ADC_TAD_6, ADC_CONFIG_0);
    configSevenSeg();
    
    unsigned int valor = 0;
    while (1) {
        
        valor = adcRead(0,RIGHT_JUST);
        //__delay_ms(50);
        printDisplays(valor);
        if(valor > limite){
            enableTimer0ISR();
        }
        else{
            desableTimer0ISR();
            output_highC(PIN_C7);
        }
        
    }
    return;


}