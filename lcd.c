// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdio.h>
// #include <string.h>
#include "lcd.h"
// #include "i2c.h"

# define FOSC 7372800 // Clock frequency = Oscillator freq .
# define BDIV ( FOSC / 100000 - 16) / 2 + 1

// void pre_setup(void);
// void i2c_init(uint8_t);
// uint8_t i2c_io(uint8_t, uint8_t *, uint16_t,
//                uint8_t *, uint16_t, uint8_t *, uint16_t);
// void Display_On(void);
// void Display_Clear(void);
// void Set_Cursor_Line_1(void);
// void Set_Cursor_Line_2(void);
// void Cursor_Home(void);
// void Cursor_Right(void);
// void Print_a_character(uint8_t);


#define I2C_ADDRESS        0x50  //LCD I2C address  0x28??? It should be 0x50 
#define DISPLAY_ON         0x41  //DISPLAY ON
#define DISPLAY_OFF        0x42  //DISPLAY OFF
#define SET_CURSOR         0x45  //SET CURSOR
#define CURSOR_HOME        0x46  //CURSOR HOME
#define MOVE_CURSOR_LEFT   0x49  //MOVE CURSOR LEFT
#define MOVE_CURSOR_RIGHT  0x4A  //MOVE CURSOR RIGHT
#define BLINK_CURSOR_ON    0x4B  //BLINK CURSOR ON
#define BLINK_CURSOR_OFF   0x4C  //BLINK CURSOR OFF
#define BACKSPACE          0x4E  //BACKSPACE
#define CLEAR_SCREEN       0x51  //CLEAR SCREEN
#define SET_CONTRAST       0x52  //SET CONTRAST
#define SET_BACKLIGHT      0x53  //SET BACKLIGHT
#define MOVE_DISP_LEFT     0x55  //MOVE DISPLAY LEFT
#define MOVE_DISP_RIGHT    0x56  //MOVE DISPLAY RIGHT
#define DISP_I2C_ADDR      0x72  //DISPLAY I2C ADDRESS

#define LCD_PRE            0xFE


char displayCapLetter[] = 
{
  0x41, 0x42, 0x43, 0x44, 0x45,
  0x46, 0x47, 0x48, 0x49, 0x4A,
  0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
  0x50, 0x51, 0x52, 0x53, 0x54,
  0x55, 0x56, 0x57, 0x58, 0x59,
  0x5A
};

char displaySmlLetter[] = 
{
  0x61, 0x62, 0x63, 0x64, 0x65,
  0x66, 0x67, 0x68, 0x69, 0x6A,
  0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74,
  0x75, 0x76, 0x77, 0x78, 0x79,
  0x7A
};

void pre_setup(void){
  PORTC |= (1 << PC1);        // Enable pull-up for switch on PORTC bit 1
  setup();
}

void setup() 
{
  i2c_init(BDIV*2);

  // Wire.setClock(100000);  //sets I2C speed to 100kHz
  // Wire.begin();
  // Serial.begin(9600);
  _delay_ms(200);
  Display_On();
  // _delay_ms(200);
  Display_Clear();
  // _delay_ms(200);
  Cursor_Home();
  // _delay_ms(200);
  
  Set_Cursor_Line_1();
  _delay_ms(200);
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write("0123456789");  //Display Text
  // Wire.endTransmission();
  unsigned char blink_cursor[2] = {LCD_PRE, BLINK_CURSOR_ON};
  i2c_io (I2C_ADDRESS, NULL, 0, blink_cursor, 2, NULL, 0);
  _delay_ms(200);

  unsigned char brightness[3] = {LCD_PRE, 0x53, 3};
  i2c_io (I2C_ADDRESS, NULL, 0, brightness, 3, NULL, 0);
  _delay_ms(200);

  // unsigned char buf[11] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x7F, 0x57, 0x6F, 0x72, 0x6C, 0x64};
  // unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, &buf, 11, NULL, 0);
  // _delay_ms(200);

  // unsigned char buf[1] = {0x48};
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x65;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x6C;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x6C;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x6F;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x7F;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x57;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x6F;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x72;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x6C;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // // _delay_ms(1);

  // buf[0] = 0x64;
  // i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  // _delay_ms(1);

  // Set_Cursor_Line_2();
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write("ABCDEFGHIJKLMNOPQRST");  //Display Text
  // Wire.endTransmission();
  
  // _delay_ms(1000);                //wait for a second
}


uint8_t Print_a_character(uint8_t input){
  unsigned char buf;
  buf = input;
  if(input == ' '){
    buf = 0x20;
  }else if(input >= 'A' && input <= 'Z'){
    buf = displayCapLetter[input-'A'];
  }else if(input >= 'a' && input <= 'z'){
    buf = displaySmlLetter[input-'a'];
  }
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Print_multiple_character(char* input, int length){
  for(; *input!='\0';input++){
    unsigned char buf = 0x20;;
      if(*input == ' '){
        buf = 0x20;
      }else if(*input >= 'A' && *input <= 'Z'){
        buf = displayCapLetter[*input-'A'];
      }else if(*input >= 'a' && *input <= 'z'){
        buf = displaySmlLetter[*input-'a'];
      }
      Print_a_character(buf);
      // _delay_ms(10);
  }
  return 0;
}


uint8_t Display_On(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(DISPLAY_ON);     //Display On
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, DISPLAY_ON};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
  return status;
}

uint8_t Cursor_BACKSPACE(void){
    unsigned char buf[2] = {LCD_PRE, BACKSPACE};
    uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
    _delay_ms(20);
    return status;
}

uint8_t Display_Clear(void)
{


  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(CLEAR_SCREEN);   //Clear Display
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, CLEAR_SCREEN};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
  return status;
}

uint8_t Set_Cursor_Line_1(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x00);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x00};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Set_Cursor_Line_2(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x40);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x40};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Set_Cursor_Line_3(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x40);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x14};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Set_Cursor_Line_4(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x40);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x54};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Cursor_Home(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(CURSOR_HOME);     //Cursor Home
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, CURSOR_HOME};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(10);
  return status;
}

uint8_t Cursor_Right(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(MOVE_CURSOR_RIGHT);     //Cursor Home
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, MOVE_CURSOR_RIGHT};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(5);
  return status;
}

uint8_t Cursor_Left(void)
{
  unsigned char buf[2] = {LCD_PRE, MOVE_CURSOR_LEFT};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(5);
  return status;
}

uint8_t Cursor_POS(unsigned char pos)
{
  unsigned char buf[3] = {LCD_PRE, 0x45, pos};
  uint8_t status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 3, NULL, 0);
  _delay_ms(20);
  return status;
}