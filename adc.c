//adc.c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

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

int main(void){
	PORTC = 0x00;
	DDRC = 0x00;
	adc_init();
	pre_setup();
	while(1){
		//Start ADC on channel 1 = PC1
		int result1 = readAdc(1);
		int thousands = result1 / 1000;
		int temp = result1 %1000;

		int hundreds = temp / 100;
		temp = temp%100;

		int tens = temp/10;
		temp = temp%10;

		int ones = temp;

		char out = 0x30;
		out += thousands;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += hundreds;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += tens;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += ones;
		Print_a_character(out);
		_delay_ms(100);

		Set_Cursor_Line_2();
		_delay_ms(100);

		//Start ADC on channel 2 = PC2
		int result2 = readAdc(2);
		thousands = result2 / 1000;
		temp = result2 %1000;

		hundreds = temp / 100;
		temp = temp%100;

		tens = temp/10;
		temp = temp%10;

		ones = temp;

		out = 0x30;
		out += thousands;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += hundreds;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += tens;
		Print_a_character(out);
		_delay_ms(50);

		out = 0x30;
		out += ones;
		Print_a_character(out);
		_delay_ms(100);

		Cursor_Home();
		_delay_ms(100);

		Display_Clear();

	}
	return 0;
}