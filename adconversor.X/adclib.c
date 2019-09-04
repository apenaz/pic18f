#include "adclib.h"
#include <pic18f4550.h>


void adcConfig(unsigned char conversionRate,unsigned char acqTime,unsigned char portConfig){
    //configurar taxa de conversão
    ADCON2 = ADCON2 & 0b11111000;
    ADCON2 = ADCON2 | conversionRate;
    
    // configurar o tempo de aquisição 
    ADCON2 = ADCON2 & 0b11000111;
    ADCON2 = ADCON2  | acqTime;
    
    // configurar pino ad
    ADCON1 = ADCON1 & 0b11110000;
    ADCON1 = ADCON1 | portConfig;
    VCFG1 = 0;
    VCFG0 = 0;
}
unsigned int adcRead(unsigned char channel,unsigned char resultFormat){
    unsigned int returnValue = 0;
    
    ADCON0 = ADCON0 & 0b111000011;
    ADCON0 = ADCON0|(channel<<2);
    
    ADCON2 = ADCON2 & 0b01111111;
    ADCON2 = ADCON2 | resultFormat;
    
    ADON = 1;
    GO_nDONE = 1;
    while(GO_nDONE);
    if(resultFormat == RIGHT_JUST){
        returnValue = (ADRESH<<8)|ADRESL;
    }
    if (resultFormat == LEFT_JUST) {
        returnValue = (ADRESH<<2)|(ADRESL>>6);
    }

}
