/*
 * ayin005_lab4_part1.c
 *
 * Created: 4/10/2019 8:32:56 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) { //x is the button. K is 0 or 1
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as inputs
	// initialize to 0s
	unsigned char button0 = 0x00;
	
	while(1)
	{
		// 1) Read Inputs and assign to variables
		button0 = PINA & 0x01; // Mask PINA to only get the bit you are interested in
		
		button0 == 0x01;
		int count = 0;
		// 2) Perform Computation
		if (button0 == 0x01) { // True if PA0 is 1
			count = count + 1;
		}
		// 3) write results to port
		PORTC = count;
	}
}
