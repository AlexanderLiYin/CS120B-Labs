/*
 * Lab3Challenge.c
 *
 * Created: 4/8/2019 1:34:58 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port C's 8 pins as outputs,
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
	
	unsigned char output0 = 0x00;
	unsigned char output1 = 0x00;
	unsigned char output2 = 0x00;
	unsigned char output3 = 0x00;
	unsigned char output4 = 0x00;
	unsigned char output5 = 0x00;
	unsigned char output6 = 0x00;
	unsigned char output7 = 0x00;
	
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
		
		output0 = PINB & 0x08; // Mask PINA to only get the bit you are interested in
		output1 = PINB & 0x04; // Mask PINA to only get the bit you are interested in
		output2 = PINB & 0x02; // Mask PINA to only get the bit you are interested in
		output3 = PINB & 0x01; // Mask PINA to only get the bit you are interested in
		output4 = PINC & 0x10; // Mask PINA to only get the bit you are interested in
		output5 = PINC & 0x20; // Mask PINA to only get the bit you are interested in
		output6 = PINC & 0x40; // Mask PINA to only get the bit you are interested in
		output7 = PINC & 0x80; // Mask PINA to only get the bit you are interested in
		
		int Bnum = 0;
		int Cnum = 0;
		
		// 2) Perform Computation
		if (button0 == 0x01) { // True if PA0 is 1
			output4 = 0x10;
			Cnum = Cnum + 16;
		}
		if (button1 == 0x02) { // True if PA1 is 1
			output5 ==0x20;
			Cnum = Cnum + 32;
		}
		if (button2 == 0x04) { // True if PA2 is 1
			output6 == 0x40;
			Cnum = Cnum + 64;
		}
		if (button3 == 0x08) { // True if PA3 is 1
			output7 = 0x80;
			Cnum = 0x124;
		}
		if (button4 == 0x10) { // True if PA0 is 1
			output3 = 0x01;
			Bnum = Bnum + 1;
		}
		if (button5 == 0x20) { // True if PA1 is 1
			output2 ==0x02;
			Bnum = Bnum + 2;
		}
		if (button6 == 0x40) { // True if PA2 is 1
			output1 == 0x04;
			Bnum = Bnum + 4;
		}
		if (button7 == 0x80) { // True if PA3 is 1
			output0 = 0x08;
			Bnum = Bnum + 8;
		}
		
		PORTB = Bnum;
		PORTC = Cnum;
	}
}