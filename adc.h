//adc.h
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

void adc_init(void);
int readAdc(char chan);