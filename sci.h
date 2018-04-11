//sci.h
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "dynamic_array.h"  // growing array as buffer

void sci_init(void);
void sci_out(char ch);
void sci_outs(char *s);
ISR(USART_RX_vect);