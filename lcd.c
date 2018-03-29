// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdio.h>
// #include <string.h>
#include "lcd.h"
// #include "i2c.h"

# define FOSC 9830400 // Clock frequency = Oscillator freq .
# define BDIV ( FOSC / 100000 - 16) / 2 + 1

void pre_setup(void);
void setup();
void i2c_init(uint8_t);
uint8_t i2c_io(uint8_t, uint8_t *, uint16_t,
               uint8_t *, uint16_t, uint8_t *, uint16_t);
void Display_On(void);
void Display_Clear(void);
void Set_Cursor_Line_1(void);
void Set_Cursor_Line_2(void);
void Cursor_Home(void);
void Cursor_Right(void);
void Print_a_character(uint8_t);


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


void Print_a_character(uint8_t input){
  unsigned char buf[1];
  buf[0] = input;
  i2c_io (I2C_ADDRESS, NULL, 0, &buf, 1, NULL, 0);
}


void Display_On(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(DISPLAY_ON);     //Display On
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, DISPLAY_ON};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
}

void Display_Clear(void)
{


  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(CLEAR_SCREEN);   //Clear Display
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, CLEAR_SCREEN};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
}

void Set_Cursor_Line_1(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x00);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x00};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(300);
}

void Set_Cursor_Line_2(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);         //Prefix 
  // Wire.write(0x45);         //Set Cursor
  // Wire.write(0x40);         //
  // Wire.endTransmission();
  // delay(2);               //wait for a 1/4 second

  unsigned char send_buf[3] = {LCD_PRE, 0x45, 0x40};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, send_buf, 3, NULL, 0);
  _delay_ms(300);
}

void Cursor_Home(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(CURSOR_HOME);     //Cursor Home
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, CURSOR_HOME};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
}

void Cursor_Right(void)
{
  // Wire.beginTransmission(I2C_ADDRESS);  
  // Wire.write(0xFE);           //Prefix 
  // Wire.write(MOVE_CURSOR_RIGHT);     //Cursor Home
  // Wire.endTransmission();
  // delay(2);                 //wait for a 1/4 second

  unsigned char buf[2] = {LCD_PRE, MOVE_CURSOR_RIGHT};
  unsigned char status = i2c_io (I2C_ADDRESS, NULL, 0, buf, 2, NULL, 0);
  _delay_ms(300);
}