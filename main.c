//main.c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "adc.h"
#include "lcd.h"
#include "PCF8563.h"
#include "sci.h"

# define FOSC 9830400 // Clock frequency = Oscillator freq .
# define BDIV ( FOSC / 100000 - 16) / 2 + 1

#define MYSTRING_LEN(s) strlen(s)
#define MENU_LV1_1 "Menu Item A"
#define MENU_LV1_2 "Menu Item B"
#define MENU_LV1_3 "Menu Item C"
#define MENU_LV1_4 "Menu Item D"

// define state number for state machine

enum STATE_BUTTON {STATE_BUTTON_UP_LEFT, STATE_BUTTON_BOTTOM_LEFT, 
				   STATE_BUTTON_UP_RIGHT, STATE_BUTTON_BOTTOM_RIGHT,
				   STATE_B_UL_PRESSED, STATE_B_BL_PRESSED,
				   STATE_B_UR_PRESSED, STATE_B_BR_PRESSED,
				   STATE_B_INIT};

enum STATE_MENU {
				MENU_1, MENU_2, MENU_3, MENU_4
				};


// # define STATE_BUTTON_UP_LEFT      1
// # define STATE_BUTTON_BOTTOM_LEFT  3
// # define STATE_BUTTON_UP_RIGHT     5
// # define STATE_BUTTON_BOTTOM_RIGHT 7

// # define STATE_B_UL_PRESSED 2
// # define STATE_B_BL_PRESSED 4
// # define STATE_B_UR_PRESSED 6
// # define STATE_B_BR_PRESSED 8

// # define STATE_B_INIT 0

unsigned char old_sec = NULL;
unsigned char old_minute = NULL;
unsigned char old_hour = NULL;

unsigned char old_day = NULL;
// unsigned char old_weekday = NULL;
unsigned char old_month = NULL;
unsigned char old_year = NULL;

extern bool Received_ISR_end;
extern Array* storage_buffer;

// char letter_to_lcd_hex(char input){
// 	if(input == ' '){
// 		return 0x20;
// 	}else if(input >= 'A' && input <= 'Z'){
// 		return displayCapLetter[input-'A'];
// 	}else if(input >= 'a' && input <= 'z'){
// 		return displaySmlLetter[input-'a'];
// 	}
// 	return 0x20;
// }

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

char rtc_subroutine_time(){
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

		uint8_t status = Cursor_POS(0x40);
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

		uint8_t status = Cursor_POS(0x42);
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

		uint8_t status = Cursor_POS(0x44);
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

char rtc_subroutine_date(){
	unsigned char current_day = getDay();
	unsigned char current_weekday = getWeekday();
	unsigned char current_month = getMonth();
	unsigned char current_year = getYear();
	_delay_ms(10);
	bool update_day = 0;
	bool update_month = 0;
	bool update_year = 0;
	if(old_day != current_day){
		update_day = 1;
	}
	if(old_month != current_month){
		update_month = 1;
	}
	if(old_year != current_year){
		update_year = 1;
	}

	if(update_year){
		unsigned char temp;
		unsigned char tens = current_year / 10;
		temp = current_year % 10;
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

				old_year = current_year;
			}
		}
	}

	// Print_a_character(0x3C);

	if(update_month){
		unsigned char temp;
		unsigned char tens = current_month / 10;
		temp = current_month % 10;
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

				old_month = current_month;
			}
		}
	}

	// Print_a_character(0x3C);

	if(update_day){
		unsigned char temp;
		unsigned char tens = current_day / 10;
		temp = current_day % 10;
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

				old_day = current_day;
			}
		}

		//Then print which weekday
		unsigned char out = 0x30;
		out += current_weekday;
		status = Print_a_character(out);
	}

	return 1;
}

void display_number(int input){
	int temp = 0;
	int tens = input / 10;
	temp = input % 10;
	unsigned char out = 0x30;
	out += tens;
	Print_a_character(out);
	_delay_ms(10);
	out = 0x30;
	out += temp;
	Print_a_character(out);
	_delay_ms(10);
}

char checkInput(char bit)
{
    if ((PIND & (1 << bit)) != 0)
        return(1);
    else
        return(0);
}

int main(void){
	// PORTC = 0x00;
	DDRC = 0xFF;

	PORTD = 0x00;
	DDRD &= 0b11000011; // 5, 4, 3, 2 is input

	enum STATE_BUTTON test_button = STATE_B_INIT;
	enum STATE_MENU test_menu = MENU_1;
	char buttonUL = 0;
	char buttonUR = 0;
	char buttonBL = 0;
	char buttonBR = 0;
	char button_check = 0;

	adc_init();
	pre_setup();
	i2c_init(BDIV*2);
	_delay_ms(200);

	initClock();
	setTime(23,59,00);
	setDate(30, 4, 9, 0, 18);


	Display_Clear();
	_delay_ms(50);
	Set_Cursor_Line_1();
	_delay_ms(50);

	/* ----------------------- Segment for menu testing
	Set_Cursor_Line_1();
	_delay_ms(50);
	Print_multiple_character(MENU_LV1_1, MYSTRING_LEN(MENU_LV1_1));
	Set_Cursor_Line_2();
	_delay_ms(50);
	Print_multiple_character(MENU_LV1_2, MYSTRING_LEN(MENU_LV1_2));
	Set_Cursor_Line_3();
	_delay_ms(50);
	Print_multiple_character(MENU_LV1_3, MYSTRING_LEN(MENU_LV1_3));
	Set_Cursor_Line_4();
	_delay_ms(50);
	Print_multiple_character(MENU_LV1_4, MYSTRING_LEN(MENU_LV1_4));
	Cursor_Home();
	*/
	while(1){
		// _delay_ms(200);	
		// adc_subroutine();
		// rtc_subroutine_time();
		// char flag = rtc_subroutine_date();

		// if(flag){
			// Cursor_Home();
			// Display_Clear();
		// }
		// _delay_ms(100);
		// char flag = checkInput(4);
		// if(!flag){
		// 	button_state = 0;
		// 	// PORTC = 0b11111111;
		// 	Print_a_character(0x30+flag);
		// }else{
		// 	button_state = 1;
		// 	// PORTC = 0b00000000;
		// 	Print_a_character(0x30+flag);
		// }
		// Cursor_Home();


		/* ----------------------------------------------------------*/
		/*  
		        Code section that check if any button is pressed

		        Current implementation only allow one button to be pressed at a time
		*/
		
		char button_state = 0;
		switch(test_button){
			case STATE_B_INIT:
				button_state = 0;
				buttonUL = checkInput(3);
				buttonUR = checkInput(2);
				buttonBL = checkInput(4);
				buttonBR = checkInput(5);

				if(!buttonUL){
					test_button = STATE_BUTTON_UP_LEFT;
				}else if(!buttonUR){
					test_button = STATE_BUTTON_UP_RIGHT;
				}else if(!buttonBL){
					test_button = STATE_BUTTON_BOTTOM_LEFT;
				}else if(!buttonBR){
					test_button = STATE_BUTTON_BOTTOM_RIGHT;
				}
				break;
			case STATE_BUTTON_UP_LEFT:
				button_state = 1;
				test_button = STATE_B_UL_PRESSED;
				break;
			case STATE_BUTTON_UP_RIGHT:
				button_state = 3;
				test_button = STATE_B_UR_PRESSED;
				break;
			case STATE_BUTTON_BOTTOM_LEFT:
				button_state = 5;
				test_button = STATE_B_BL_PRESSED;
				break;
			case STATE_BUTTON_BOTTOM_RIGHT:
				button_state = 7;
				test_button = STATE_B_BR_PRESSED;
				break;

			case STATE_B_UL_PRESSED:
				button_state = 2;
				button_check = checkInput(3);
				if(button_check){
					test_button = STATE_B_INIT;
				}
				break;
			case STATE_B_UR_PRESSED:
				button_state = 4;
				button_check = checkInput(2);
				if(button_check){
					test_button = STATE_B_INIT;
				}
				break;
			case STATE_B_BL_PRESSED:
				button_state = 6;
				button_check = checkInput(4);
				if(button_check){
					test_button = STATE_B_INIT;
				}
				break;
			case STATE_B_BR_PRESSED:
				button_state = 8;
				button_check = checkInput(5);
				if(button_check){
					test_button = STATE_B_INIT;
				}
				break;			
		}
		// Cursor_Home();

		// char to_print = 0x30 + button_state;
		// Print_a_character(to_print);
		// _delay_ms(10);

		/*----------------------- Segment for basic menu navigation
		switch(test_menu){
			case MENU_1:
				Set_Cursor_Line_1();
				Print_multiple_character(MENU_LV1_1, MYSTRING_LEN(MENU_LV1_1));
				Print_a_character(0x3c);
				if(test_button==STATE_B_UL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_4;
				}else if(test_button==STATE_B_BL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_2;
				}
				break;
			case MENU_2:
				Set_Cursor_Line_2();
				Print_multiple_character(MENU_LV1_2, MYSTRING_LEN(MENU_LV1_2));
				Print_a_character(0x3c);
				if(test_button==STATE_B_UL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_1;
				}else if(test_button==STATE_B_BL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_3;
				}
				break;
			case MENU_3:
				Set_Cursor_Line_3();
				Print_multiple_character(MENU_LV1_3, MYSTRING_LEN(MENU_LV1_3));
				Print_a_character(0x3c);
				if(test_button==STATE_B_UL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_2;
				}else if(test_button==STATE_B_BL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_4;
				}
				break;
			case MENU_4:
				Set_Cursor_Line_4();
				Print_multiple_character(MENU_LV1_4, MYSTRING_LEN(MENU_LV1_4));
				Print_a_character(0x3c);
				if(test_button==STATE_B_UL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_3;
				}else if(test_button==STATE_B_BL_PRESSED){
					Cursor_BACKSPACE();
					// Cursor_BACKSPACE();
					Print_multiple_character("         ", 9);
					test_menu = MENU_1;
				}
				break;
		}
		_delay_ms(200);
		*/
	}
	return 0;
}