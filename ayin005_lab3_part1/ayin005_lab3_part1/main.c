/*
 * ayin005_lab3_part1.c
 *
 * Created: 4/8/2019 9:26:00 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs,
	// initialize to 0s
	unsigned char tmpB = 0x00; // intermediate variable used for port updates
	unsigned char button = 0x00;
	while(1)
	{
		// 1) Read Inputs and assign to variables
		button = PINA & 0x01; // Mask PINA to only get the bit you are interested in
		// 2) Perform Computation
		// if PA0 is 1, set PB1PB0=01, else =10
		if (GetBit(button, 0)) { // True if PA0 is 1
			tmpB = SetBit(tmpB, 1, 0); // Set bit 1 to 0
			tmpB = SetBit(tmpB, 0, 1); // Set bit 0 to 1
		}
		else {
			tmpB = SetBit(tmpB, 1, 1); // Set bit 1 to 1
			tmpB = SetBit(tmpB, 0, 0); // Set bit 0 to 0
		}
		// 3) write results to port
		PORTB = tmpB;
	}
}
