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
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA0 = 0x00; // Temporary variable to hold the value of A0
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A1
	unsigned char tmpA2 = 0x00; // Temporary variable to hold the value of A2
	unsigned char tmpA3 = 0x00; // Temporary variable to hold the value of A3
	unsigned char cntavail = 0x04; //Temp variable used to store number available
	
	
	while(1)
	{
		// 1) Read input
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x03;
		tmpA3 = PINA & 0x04;
		// 2) Perform computation
		// if PA0 is 1, set PB1PB0 = 01, else = 10
		if (tmpA0 == 0x01) { 
			cntavail++;
		}

		if (tmpA1 == 0x01) {
			cntavail++;
		}
		
		if (tmpA2 == 0x01) {
			cntavail++;
		}
		
		if (tmpA3 == 0x01) {
			cntavail++;
		}
		// 3) Write output
		PORTB = tmpB;
		PORTC = cntavail; //Assign Port C a number to show how much available 
	}
	return 0;
}
