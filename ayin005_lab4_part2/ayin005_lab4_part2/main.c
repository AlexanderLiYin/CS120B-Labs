/*
 * ayin005_lab4_part2.c
 *
 * Created: 4/14/2019 10:38:51 AM
 * Author : shado
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	// initialize to 0s
	while(1)
	{
		int temp = PORTC;
		if ((PORTA == 0x01) && (PORTA < 10))
		{
			PORTC = temp + 1;
		}
		if ((PORTA == 0x02) && (PORTA > 0))
		{
			PORTC = temp -1;
		}
	}
}
