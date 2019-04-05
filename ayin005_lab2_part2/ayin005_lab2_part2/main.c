/*
 * ayin005_lab2_part2.c
 *
 * Created: 4/5/2019 10:02:03 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpA0 = 0x00; // Temporary variable to hold the value of A0
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A1
	unsigned char tmpA2 = 0x00; // Temporary variable to hold the value of A0
	unsigned char tmpA3 = 0x00; // Temporary variable to hold the value of A1
while(1)
	{
		// 1) Read input
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		tmpA3 = PINA & 0x08;
		int cntavail = 0;
		// 2) Perform computation
		// if PA0 is 1, set PB1PB0 = 01, else = 10
		if (tmpA0 == 0x01) { // True if PA0 is 1 and PA1 is 0
			cntavail = cntavail + 1;
		}
		
		if (tmpA1 == 0x02) { // True if PA0 is 1 and PA1 is 0
			cntavail = cntavail + 1;
		}
		
		if (tmpA2 == 0x04) { // True if PA0 is 1 and PA1 is 0
			cntavail = cntavail + 1;
		}
		
		if (tmpA3 == 0x08) { // True if PA0 is 1 and PA1 is 0
			cntavail = cntavail + 1;
		}

		// 3) Write output
		PORTC = 4 - cntavail;	
	}
}
