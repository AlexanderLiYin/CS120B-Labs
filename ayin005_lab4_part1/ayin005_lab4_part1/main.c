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
	int state = 0;
	int counter = 0;
	int temp = 0;
	while(1)
	{
		state = PINA & 0x01;
		switch(state)
		{
		case 0:
			if (temp != 1)
			{
				PORTB = 0x01;
				counter = 0;
			}
			else
			{
				counter = 1;
			}
			break;
		case 1:

				PORTB = 0x02;
				if (counter != 1)
				{
					temp = 1;
				}
				else 
				{
					temp = 0;
					PORTB =0x01;
				}
		break;
		}
	}
}
