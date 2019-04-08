/*
 * ayin005_lab3_part1.c
 *
 * Created: 4/8/2019 9:26:00 AM
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
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	// initialize to 0s
	unsigned char button0 = 0x00;
	unsigned char button1 = 0x00;
	unsigned char button2 = 0x00;
	unsigned char button3 = 0x00;
	unsigned char button4 = 0x00;
	unsigned char button5 = 0x00;
	unsigned char button6 = 0x00;
	unsigned char button7 = 0x00;
	
	unsigned char button8 = 0x00;
	unsigned char button9 = 0x00;
	unsigned char buttonA = 0x00;
	unsigned char buttonB = 0x00;
	unsigned char buttonC = 0x00;
	unsigned char buttonD = 0x00;
	unsigned char buttonE = 0x00;
	unsigned char buttonF = 0x00;
	
	
	while(1)
	{
		// 1) Read Inputs and assign to variables
		button0 = PINA & 0x01; // Mask PINA to only get the bit you are interested in
		button1 = PINA & 0x02; // Mask PINA to only get the bit you are interested in
		button2 = PINA & 0x04; // Mask PINA to only get the bit you are interested in
		button3 = PINA & 0x08; // Mask PINA to only get the bit you are interested in
		button4 = PINA & 0x10; // Mask PINA to only get the bit you are interested in
		button5 = PINA & 0x20; // Mask PINA to only get the bit you are interested in
		button6 = PINA & 0x40; // Mask PINA to only get the bit you are interested in
		button7 = PINA & 0x80; // Mask PINA to only get the bit you are interested in
		
		button8 = PINB & 0x01; // Mask PINA to only get the bit you are interested in
		button9 = PINB & 0x02; // Mask PINA to only get the bit you are interested in
		buttonA = PINB & 0x04; // Mask PINA to only get the bit you are interested in
		buttonB = PINB & 0x08; // Mask PINA to only get the bit you are interested in
		buttonC = PINB & 0x10; // Mask PINA to only get the bit you are interested in
		buttonD = PINB & 0x20; // Mask PINA to only get the bit you are interested in
		buttonE = PINB & 0x40; // Mask PINA to only get the bit you are interested in
		buttonF = PINB & 0x80; // Mask PINA to only get the bit you are interested in
		
		int count = 0;
		// 2) Perform Computation
		if (button0 == 0x01) { // True if PA0 is 1
			count = count + 1; 
		}
		if (button1 == 0x02) { // True if PA1 is 1
			count = count + 1; 
		}
		if (button2 == 0x04) { // True if PA2 is 1
			count =count + 1; 
		}
		if (button3 == 0x08) { // True if PA3 is 1
			count =count + 1; 
		}
		if (button4 == 0x10) { // True if PA4 is 1
			count =count + 1; 
		}
		if (button5 == 0x20) { // True if PA5 is 1
			count =count + 1; 
		}
		if (button6 == 0x40) { // True if PA6 is 1
			count =count + 1; 
		}
		if (button7 == 0x80) { // True if PA7 is 1
			count = count + 1; 
		}
		
		if (button8 == 0x01) { // True if PB0 is 1
			count =count + 1; 
		}
		if (button9 == 0x02) { // True if PB1 is 1
			count =count + 1; 
		}
		if (buttonA == 0x04) { // True if PB2 is 1
			count =count + 1; 
		}
		if (buttonB == 0x08) { // True if PB3 is 1
			count =count + 1; 
		}
		if (buttonC == 0x10) { // True if PB4 is 1
			count =count + 1; 
		}
		if (buttonD == 0x20) { // True if PB5 is 1
			count =count + 1; 
		}
		if (buttonE == 0x40) { // True if PB6 is 1
			count =count + 1; 
		}
		if (buttonF == 0x80) { // True if PB7 is 1
			count = count + 1; 
		}
		// 3) write results to port
		PORTC = count;
	}
}
