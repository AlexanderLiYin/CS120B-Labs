/*
 * ayin005_lab3_part1.c
 *
 * Created: 4/8/2019 9:26:00 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpB = 0x00; // You are UNABLE to read from output pins. Instead you
	// Should use a temporary variable for all bit manipulation.
	unsigned char button = 0x00;
	while(1)
	{
		// 1) Read input
		button = PINA & 0x01;
		// 2) Perform Computation
		// if PA0 is 1, set PB1PB0 = 01, else = 10
		if (button == 0x01) { // True if PA0 is 1
			tmpB = (tmpB & 0xFC) | 0x01; // Sets tmpB to bbbbbb01
			// (clear rightmost 2 bits, then set to 01)
		}
		else {
			tmpB = (tmpB & 0xFC) | 0x02; // Sets tmpB to bbbbbb10
			// (clear rightmost 2 bits, then set to 10)
		}
		// 3) Write Output
		PORTB = tmpB;	// Sets output on PORTB to value of tmpB
	}
}
