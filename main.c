//main.c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "adc.h"
#include "lcd.h"
#include "PCF8563.h"

# define FOSC 9830400 // Clock frequency = Oscillator freq .
# define BDIV ( FOSC / 100000 - 16) / 2 + 1

unsigned char old_sec = NULL;
unsigned char old_minute = NULL;
unsigned char old_hour = NULL;

void adc_subroutine(){
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
}

char rtc_subroutine(){
	unsigned char current_sec = getSecond();
	unsigned char current_minute = getMinute();
	unsigned char current_hour = getHour();
	_delay_ms(10);
	bool update_sec = 0;
	bool update_minute = 0;
	bool update_hour = 0;
	if(old_sec != current_sec){
		update_sec = 1;
	}
	if(old_minute != current_minute){
		update_minute = 1;
	}
	if(old_hour != current_hour){
		update_hour = 1;
	}

	if(update_hour){
		unsigned char temp;
		unsigned char tens = current_hour / 10;
		temp = current_hour % 10;
		unsigned char ones = temp;

		uint8_t status = Cursor_POS(0x00);
		_delay_ms(10);
		if(status==0){

			unsigned char out = 0x30;
			out += tens;
			status = Print_a_character(out);
			_delay_ms(10);
			if(status==0){

				out = 0x30;
				out += ones;
				status = Print_a_character(out);
				_delay_ms(10);

				old_hour = current_hour;
			}
		}
	}

	// Print_a_character(0x3C);

	if(update_minute){
		unsigned char temp;
		unsigned char tens = current_minute / 10;
		temp = current_minute % 10;
		unsigned char ones = temp;

		uint8_t status = Cursor_POS(0x02);
		_delay_ms(10);
		if(status==0){

			unsigned char out = 0x30;
			out += tens;
			status = Print_a_character(out);
			_delay_ms(10);
			if(status==0){

				out = 0x30;
				out += ones;
				status = Print_a_character(out);
				_delay_ms(10);

				old_minute = current_minute;
			}
		}
	}

	// Print_a_character(0x3C);

	if(update_sec){
		unsigned char temp;
		unsigned char tens = current_sec / 10;
		temp = current_sec % 10;
		unsigned char ones = temp;

		uint8_t status = Cursor_POS(0x04);
		_delay_ms(10);
		if(status==0){

			unsigned char out = 0x30;
			out += tens;
			status = Print_a_character(out);
			_delay_ms(10);
			if(status==0){

				out = 0x30;
				out += ones;
				status = Print_a_character(out);
				_delay_ms(10);

				old_sec = current_sec;
			}
		}
	}

	return 1;
}

int main(void){
	PORTC = 0x00;
	DDRC = 0x00;
	adc_init();
	pre_setup();
	i2c_init(BDIV*2);
	_delay_ms(200);

	initClock();
	setTime(12,59,20);


	Display_Clear();
	_delay_ms(50);
	while(1){
		// _delay_ms(200);	
		// adc_subroutine();
		char flag = rtc_subroutine();

		if(flag){
			// Cursor_Home();
			// Display_Clear();
		}
		// _delay_ms(100);
	}
	return 0;
}