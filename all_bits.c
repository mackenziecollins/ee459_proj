// switching bits up and down in a loop

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	DDRB |= 0xFF;          // Set PORTB bit 0 for output
    DDRC |= 0xFF;          // Set PORTC bit 0 for output
    DDRD |= 0xFF;          // Set PORTD bit 0 for output

    while (1) {
		PORTB |= 1 << PB0;      // Set PB0 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB0);   // Set PB0 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB1;      // Set PB1 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB1);   // Set PB1 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB2;      // Set PB2 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB2);   // Set PB2 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB3;      // Set PB3 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB3);   // Set PB3 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB4;      // Set PB4 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB4);   // Set PB4 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB5;      // Set PB5 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB5);   // Set PB5 to a 0
		//_delay_ms(100);

		PORTB |= 1 << PB7;      // Set PD8 to a 1
		//_delay_ms(100);
		PORTB &= ~(1 << PB7);   // Set PD8 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC0;      // Set PC0 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC0);   // Set PC0 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC1;      // Set PC1 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC1);   // Set PC1 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC2;      // Set PC2 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC2);   // Set PC2 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC3;      // Set PC3 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC3);   // Set PC3 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC4;      // Set PC4 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC4);   // Set PC4 to a 0
		//_delay_ms(100);

		PORTC |= 1 << PC5;      // Set PC5 to a 1
		//_delay_ms(100);
		PORTC &= ~(1 << PC5);   // Set PC5 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD0;      // Set PD0 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD0);   // Set PD0 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD1;      // Set PD1 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD1);   // Set PD1 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD2;      // Set PD2 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD2);   // Set PD2 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD3;      // Set PD3 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD3);   // Set PD3 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD4;      // Set PD4 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD4);   // Set PD4 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD5;      // Set PD5 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD5);   // Set PD5 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD6;      // Set PD6 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD6);   // Set PD6 to a 0
		//_delay_ms(100);

		PORTD |= 1 << PD7;      // Set PD7 to a 1
		//_delay_ms(100);
		PORTD &= ~(1 << PD7);   // Set PD7 to a 0
		//_delay_ms(100);

    }

    return 0;   /* never reached */
}