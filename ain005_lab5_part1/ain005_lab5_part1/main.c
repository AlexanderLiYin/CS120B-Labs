/*
 * ain005_lab5_part1.c
 *
 * Created: 4/17/2019 9:11:48 AM
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
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs
	// initialize to 0s
	PORTC = 0x00; //Port C is initialized to 7.
	enum state {base, lock, lock2, unlock};
	enum state machine;
	int value = 1;
	int buttonX;
	int buttonY;
	int buttonHash;
	int buttonIn;
	
	while(1)
	{
		buttonX = PINA & 0x01;
		buttonY = PINA & 0x02;
		buttonHash = PINA & 0x04;
		buttonIn = PINA & 0x80;
		switch(machine)
		{
			case base:
			PORTC = value;
			
			if ((buttonHash == 0x04) && ((buttonY != 0x02) || (buttonX != 0x01)))
			{
				machine = lock;
			};
			
			break;
			
			case lock:
			if ((buttonX != 0x01) && ((buttonY!=0x02) || (buttonHash != 0x04)))
			{
				machine = lock2;
			}
			else if((buttonY==0x02) || (buttonHash == 0x04))
			{
				machine = base;
			}
			break;
			
			case lock2:
			if (buttonY == 0x02 && ((buttonX != 0x01) || (buttonHash != 0x04)))
			{
				PORTB = value;
				machine = unlock;
			}
			else if ((buttonX == 0x01) || (buttonHash == 0x04))
			{
				machine = base;
			}
			
			break;
			
			case unlock:
			if (buttonIn==0x80)
			{
				PORTB = 0;
				machine = base;
			}
			break;
		}
	}
}