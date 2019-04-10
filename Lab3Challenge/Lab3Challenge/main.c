/*
 * Lab3Challenge.c
 *
 * Created: 4/8/2019 1:34:58 PM
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
	DDRD = 0x00; PORTD = 0xFF; // Configure port D's 8 pins as inputs
	DDRB = 0xFE; PORTB = 0x01; // Configure port D's 8 pins as inputs
	// initialize to 0
	
	unsigned char input = 0x00;
	while(1)
	{
		input = PIND; 
		input = input << 1;
		SetBit(input, 0, PINB & 1);
		
		if (input >= 70)
		{
			PORTB = 0x02; 
		}
		else if ((input < 70) && (input > 5))
		{
			PORTB = 0x04;
		}
	}
}