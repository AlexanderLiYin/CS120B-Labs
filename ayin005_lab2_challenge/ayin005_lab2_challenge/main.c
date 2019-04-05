/*
 * ayin005_lab2_challenge.c
 *
 * Created: 4/5/2019 2:31:36 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port C's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF; // Configure port B's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s
	
	unsigned char tmpA0 = 0x00; // Temporary variable to hold the value of A0
	unsigned char tmpA1 = 0x00; // Temporary variable to hold the value of A1
	unsigned char tmpA2 = 0x00; // Temporary variable to hold the value of A2
	unsigned char tmpA3 = 0x00; // Temporary variable to hold the value of A3
	unsigned char tmpA4 = 0x00; // Temporary variable to hold the value of A4
	unsigned char tmpA5 = 0x00; // Temporary variable to hold the value of A5
	unsigned char tmpA6 = 0x00; // Temporary variable to hold the value of A6
	unsigned char tmpA7 = 0x00; // Temporary variable to hold the value of A7
	
	unsigned char tmpB0 = 0x00; // Temporary variable to hold the value of B0
	unsigned char tmpB1 = 0x00; // Temporary variable to hold the value of B1
	unsigned char tmpB2 = 0x00; // Temporary variable to hold the value of B2
	unsigned char tmpB3 = 0x00; // Temporary variable to hold the value of B3
	unsigned char tmpB4 = 0x00; // Temporary variable to hold the value of B4
	unsigned char tmpB5 = 0x00; // Temporary variable to hold the value of B5
	unsigned char tmpB6 = 0x00; // Temporary variable to hold the value of B6
	unsigned char tmpB7 = 0x00; // Temporary variable to hold the value of B7
	
	unsigned char tmpC0 = 0x00; // Temporary variable to hold the value of C0
	unsigned char tmpC1 = 0x00; // Temporary variable to hold the value of C1
	unsigned char tmpC2 = 0x00; // Temporary variable to hold the value of C2
	unsigned char tmpC3 = 0x00; // Temporary variable to hold the value of C3
	unsigned char tmpC4 = 0x00; // Temporary variable to hold the value of C4
	unsigned char tmpC5 = 0x00; // Temporary variable to hold the value of C5
	unsigned char tmpC6 = 0x00; // Temporary variable to hold the value of C6
	unsigned char tmpC7 = 0x00; // Temporary variable to hold the value of C7
	
	while(1)
	{
		// 1) Read input
		tmpA0 = PINA & 0x01; //1
		tmpA1 = PINA & 0x02; //2
		tmpA2 = PINA & 0x04; //4
		tmpA3 = PINA & 0x08; //8
		tmpA4 = PINA & 0x10; //16
		tmpA5 = PINA & 0x20; //32
		tmpA6 = PINA & 0x40; //64
		tmpA7 = PINA & 0x80; //128
		int WeightA = tmpA0 + tmpA1 + tmpA2 + tmpA3 + tmpA4 + tmpA5 + tmpA6 + tmpA7;
		
		tmpB0 = PINB & 0x01; //1
		tmpB1 = PINB & 0x02; //2
		tmpB2 = PINB & 0x04; //4
		tmpB3 = PINB & 0x08; //8
		tmpB4 = PINB & 0x10; //16
		tmpB5 = PINB & 0x20; //32
		tmpB6 = PINB & 0x40; //64
		tmpB7 = PINB & 0x80; //128
		int WeightB = tmpB0 + tmpB1 + tmpB2 + tmpB3 + tmpB4 + tmpB5 + tmpB6 + tmpB7;
		
		tmpC0 = PINC & 0x01; //1
		tmpC1 = PINC & 0x02; //2
		tmpC2 = PINC & 0x04; //4
		tmpC3 = PINC & 0x08; //8
		tmpC4 = PINC & 0x10; //16
		tmpC5 = PINC & 0x20; //32
		tmpC6 = PINC & 0x40; //64
		tmpC7 = PINC & 0x80; //128
		int WeightC = tmpC0 + tmpC1 + tmpC2 + tmpC3 + tmpC4 + tmpC5 + tmpC6 + tmpC7;
		
		int totalWeight = WeightA + WeightB + WeightC;
		int weightDifference = WeightA - WeightC;
		
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
		if (cntavail == 4)
		{
			PORTC = 128;
		}
		else
		{
			PORTC = 4 - cntavail;
		}
		
	}
}