//lcd.hvoid setup();
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
// #include "lcd.h"
#include "i2c.h"

void pre_setup(void);
void setup(void);
// void i2c_init(uint8_t);
// uint8_t i2c_io(uint8_t, uint8_t *, uint16_t,
//                uint8_t *, uint16_t, uint8_t *, uint16_t);
uint8_t Display_On(void);
uint8_t Display_Clear(void);
uint8_t Set_Cursor_Line_1(void);
uint8_t Set_Cursor_Line_2(void);
uint8_t Set_Cursor_Line_3(void);
uint8_t Set_Cursor_Line_4(void);
uint8_t Cursor_BACKSPACE(void);
uint8_t Cursor_Home(void);
uint8_t Cursor_Right(void);
uint8_t Cursor_Left(void);
uint8_t Cursor_POS(unsigned char pos);
uint8_t Print_a_character(uint8_t);
uint8_t Print_multiple_character(char* input, int length);