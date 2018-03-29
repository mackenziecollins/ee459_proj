//adc.c
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdio.h>
// #include <string.h>
#include "adc.h"

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define VREF 5
#define POT 10000

void adc_init(void)
{
    ADMUX = (1<<REFS0);     //select AVCC as reference
    ADCSRA = (1<<ADEN) | 7;  //enable and prescale = 128 (16MHz/128 = 125kHz)
}

int readAdc(char chan)
{
    ADMUX = (1<<REFS0) | (chan & 0x0f);  //select input and ref
    ADCSRA |= (1<<ADSC);                 //start the conversion
    while (ADCSRA & (1<<ADSC));          //wait for end of conversion
    return ADCW;
}