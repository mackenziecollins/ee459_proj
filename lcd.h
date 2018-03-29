//lcd.hvoid setup();
void pre_setup(void);
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