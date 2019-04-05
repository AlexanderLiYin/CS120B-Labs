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
	
	int tmpA0 = 0x00; // Temporary variable to hold the value of A0
	int tmpA1 = 0x00; // Temporary variable to hold the value of A1
	int tmpA2 = 0x00; // Temporary variable to hold the value of A2
	int tmpA3 = 0x00; // Temporary variable to hold the value of A3
	int tmpA4 = 0x00; // Temporary variable to hold the value of A4
	int tmpA5 = 0x00; // Temporary variable to hold the value of A5
	int tmpA6 = 0x00; // Temporary variable to hold the value of A6
	int tmpA7 = 0x00; // Temporary variable to hold the value of A7
	
	int tmpB0 = 0x00; // Temporary variable to hold the value of B0
	int tmpB1 = 0x00; // Temporary variable to hold the value of B1
	int tmpB2 = 0x00; // Temporary variable to hold the value of B2
	int tmpB3 = 0x00; // Temporary variable to hold the value of B3
	int tmpB4 = 0x00; // Temporary variable to hold the value of B4
	int tmpB5 = 0x00; // Temporary variable to hold the value of B5
	int tmpB6 = 0x00; // Temporary variable to hold the value of B6
	int tmpB7 = 0x00; // Temporary variable to hold the value of B7
	
	int tmpC0 = 0x00; // Temporary variable to hold the value of C0
	int tmpC1 = 0x00; // Temporary variable to hold the value of C1
	int tmpC2 = 0x00; // Temporary variable to hold the value of C2
	int tmpC3 = 0x00; // Temporary variable to hold the value of C3
	int tmpC4 = 0x00; // Temporary variable to hold the value of C4
	int tmpC5 = 0x00; // Temporary variable to hold the value of C5
	int tmpC6 = 0x00; // Temporary variable to hold the value of C6
	int tmpC7 = 0x00; // Temporary variable to hold the value of C7
	
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
		if (totalWeight > 0xFF) {
			PORTD = 0x01;
		}
		if ((weightDifference > 0x50) || (weightDifference < -0x50)) { // True if PA0 is 1 and PA1 is 0
			PORTD = 0x02;
		}
		if ((totalWeight > 0xFF) && ((weightDifference > 0x50) || (weightDifference < -0x50))) {
			PORTD = 0x03;
		}
	}
}