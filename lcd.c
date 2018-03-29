#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

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

/* ----------------------------------------------------------------------- */

/*
  i2c_io - write and read bytes to a slave I2C device

  This funtions write "an" bytes from array "ap" and then "wn" bytes from array
  "wp" to I2C device at address "device_addr".  It then reads "rn" bytes from
  the same device to array "rp".

  Return values (might not be a complete list):
        0    - Success
        0x20 - NAK received after sending device address for writing
        0x30 - NAK received after sending data
        0x38 - Arbitration lost with address or data
        0x48 - NAK received after sending device address for reading

  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

This "i2c_io" I2C routine is an attempt to provide an I/O function for both
reading and writing, rather than have separate functions.

I2C writes consist of sending a stream of bytes to the slave device.  In some
cases the first few bytes may be the internal address in the device, and then
the data to be stored follows.  For example, EEPROMs like the 24LC256 require a
two-byte address to precede the data.  The DS1307 RTC requires a one-byte
address.

I2C reads often consist of first writing one or two bytes of internal address
data to the device and then reading back a stream of bytes starting from that
address.  Some devices appear to claim that that reads can be done without
first doing the address writes, but so far I haven't been able to get any to
work that way.

This function does writing and reading by using pointers to three arrays "ap",
"wp", and "rp".  The function performs the following actions in this order:
    If "an" is greater than zero, then "an" bytes are written from array "ap"
    If "wn" is greater then zero, then "wn" bytes are written from array "wp"
    If "rn" is greater then zero, then "rn" byte are read into array "rp"
Any of the "an", "wn", or "rn" can be zero.

The reason for separate "ap" and "wp" arrays is that the address data can be
taken from one array (ap), and then the write data from another (wp) without
requiring that the contents be merged into one array before calling the
function.  This means the following three calls all do exactly the same thing.

    i2c_io(0xA0, buf, 100, NULL, 0, NULL, 0);
    i2c_io(0xA0, NULL, 0, buf, 100, NULL, 0);
    12c_io(0xA0, buf, 2, buf+2, 98, NULL, 0);

In all cases 100 bytes from array "buf" will be written to the I2C device at
bus address 0xA0.

A typical write with a 2-byte address is done with

    i2c_io(0xA0, abuf, 2, wbuf, 50, NULL, 0);

A typical read with a 1-byte address is done with

    i2c_io(0xD0, abuf, 1, NULL, 0, rbuf, 20);
*/

uint8_t i2c_io(uint8_t device_addr, uint8_t *ap, uint16_t an, 
               uint8_t *wp, uint16_t wn, uint8_t *rp, uint16_t rn)
{
    uint8_t status, send_stop, wrote, start_stat;

    status = 0;
    wrote = 0;
    send_stop = 0;

    if (an > 0 || wn > 0) {
        wrote = 1;
        send_stop = 1;

        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);  // Send start condition
        while (!(TWCR & (1 << TWINT)));     // Wait for TWINT to be set
        status = TWSR & 0xf8;
        if (status != 0x08)                 // Check that START was sent OK
            return(status);

        TWDR = device_addr & 0xfe;          // Load device address and R/W = 0;
        TWCR = (1 << TWINT) | (1 << TWEN);  // Start transmission
        while (!(TWCR & (1 << TWINT)));     // Wait for TWINT to be set
        status = TWSR & 0xf8;
        if (status != 0x18) {               // Check that SLA+W was sent OK
            if (status == 0x20)             // Check for NAK
                goto nakstop;               // Send STOP condition
            return(status);                 // Otherwise just return the status
        }

        // Write "an" data bytes to the slave device
        while (an-- > 0) {
            TWDR = *ap++;                   // Put next data byte in TWDR
            TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
            while (!(TWCR & (1 << TWINT))); // Wait for TWINT to be set
            status = TWSR & 0xf8;
            if (status != 0x28) {           // Check that data was sent OK
                if (status == 0x30)         // Check for NAK
                    goto nakstop;           // Send STOP condition
                return(status);             // Otherwise just return the status
            }
        }

        // Write "wn" data bytes to the slave device
        while (wn-- > 0) {
            TWDR = *wp++;                   // Put next data byte in TWDR
            TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
            while (!(TWCR & (1 << TWINT))); // Wait for TWINT to be set
            status = TWSR & 0xf8;
            if (status != 0x28) {           // Check that data was sent OK
                if (status == 0x30)         // Check for NAK
                    goto nakstop;           // Send STOP condition
                return(status);             // Otherwise just return the status
            }
        }

        status = 0;                         // Set status value to successful
    }

    if (rn > 0) {
        send_stop = 1;

        // Set the status value to check for depending on whether this is a
        // START or repeated START
        start_stat = (wrote) ? 0x10 : 0x08;

        // Put TWI into Master Receive mode by sending a START, which could
        // be a repeated START condition if we just finished writing.
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
                                            // Send start (or repeated start) condition
        while (!(TWCR & (1 << TWINT)));     // Wait for TWINT to be set
        status = TWSR & 0xf8;
        if (status != start_stat)           // Check that START or repeated START sent OK
            return(status);

        TWDR = device_addr  | 0x01;         // Load device address and R/W = 1;
        TWCR = (1 << TWINT) | (1 << TWEN);  // Send address+r
        while (!(TWCR & (1 << TWINT)));     // Wait for TWINT to be set
        status = TWSR & 0xf8;
        if (status != 0x40) {               // Check that SLA+R was sent OK
            if (status == 0x48)             // Check for NAK
                goto nakstop;
            return(status);
        }

        // Read all but the last of n bytes from the slave device in this loop
        rn--;
        while (rn-- > 0) {
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Read byte and send ACK
            while (!(TWCR & (1 << TWINT))); // Wait for TWINT to be set
            status = TWSR & 0xf8;
            if (status != 0x50)             // Check that data received OK
                return(status);
            *rp++ = TWDR;                   // Read the data
        }

        // Read the last byte
        TWCR = (1 << TWINT) | (1 << TWEN);  // Read last byte with NOT ACK sent
        while (!(TWCR & (1 << TWINT)));     // Wait for TWINT to be set
        status = TWSR & 0xf8;
        if (status != 0x58)                 // Check that data received OK
            return(status);
        *rp++ = TWDR;                       // Read the data

        status = 0;                         // Set status value to successful
    }
    
nakstop:                                    // Come here to send STOP after a NAK
    if (send_stop)
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);  // Send STOP condition

    return(status);
}


/*
  i2c_init - Initialize the I2C port
*/
void i2c_init(uint8_t bdiv)
{
    TWSR = 0;                           // Set prescalar for 1
    TWBR = bdiv;                        // Set bit rate register
}