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
	PORTC = 0x07; //Port C is initialized to 7.
	enum state {base, increment, decrement};
	enum state machine;
	int value=7;
	int button0;
	int button1;
	int check=0;
	while(1)
	{
		int button0 = PINA & 0x01;
		int button1 = PINA & 0x02;
		switch(machine)
		{
			case base:
			PORTC = value;
			
			if((button0 == 0x01) && (button1 == 0x02))
			{
				value = 0;
				PORTC = value;
				break;
			}
			if ((button0 == 0x01) && (value != 9))
			{
				machine = increment;
				check = 1;
			};
			if ((button1 == 0x02) && (value != 0))
			{
				machine = decrement;
				check = 1;
			}
			break;
		
			case increment:
			if (check == 1)
			{
				value = value + 1;
				check=0;
			}
			
			PORTC = value;
			if (button0 != 0x01)
			{
				machine = base;
			}
			break;
			
			case decrement:
			if (check == 1)
			{
				value = value - 1;
				check=0;
			}
			PORTC = value;
			if (button1 != 0x02)
			{
				machine = base;
			}
			break;
		}
	}
}