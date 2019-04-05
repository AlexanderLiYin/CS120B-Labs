/*
 * ayin005_lab2_part1.c
 *
 * Created: 4/5/2019 9:47:43 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
					// Initialize output on PORTB to 0x00
	unsigned char temp_input = 0x00;
	while(1)
	{
		temp_input = PINA;
		PORTB = temp_input;	// Writes port B's 8 pins with the values
					// on port A's 8 pins
	}
}
