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
	
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A0

	unsigned char cntavail = 0x00; //Temp variable used to store number available
	
	
	while(1)
	{
		// 1) Read input
		tmpA = PINA;
		// 2) Perform computation
		// if PA0 is 1, set PB1PB0 = 01, else = 10
		if (tmpA == 0x00) { 
			cntavail = (cntavail & 0xFC) | 0x04; // Sets tmpB to bbbbbb01
		}
		
		else if (tmpA == 0x01) {
			cntavail = (cntavail & 0xFC) | 0x03;
		}
		
		else if (tmpA == 0x02) {
			cntavail = (cntavail & 0xFC) | 0x02;
		}
		
		else if (tmpA == 0x01) {
			cntavail = (cntavail & 0xFC) | 0x03;
		}
		
		else if (tmpA == 0x00) {
			cntavail = (cntavail & 0xFC) | 0x04;
		}
		
		// 3) Write output
		PORTC = cntavail; //Assign Port C a number to show how much available 
	}
	return 0;
}
