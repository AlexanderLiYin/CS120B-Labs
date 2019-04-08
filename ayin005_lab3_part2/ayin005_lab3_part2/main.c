/*
 * ayin005_lab3_part2.c
 *
 * Created: 4/8/2019 10:08:04 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	// initialize to 0s
	unsigned char button0 = 0x00;
	unsigned char button1 = 0x00;
	unsigned char button2 = 0x00;
	unsigned char button3 = 0x00;
	unsigned char button4 = 0x00;
	unsigned char button5 = 0x00;
	unsigned char button6 = 0x00;
	
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
		
		int fuel = 0;
		int light = 0;
		
		// 2) Perform Computation
		if (button0 == 0x01) { // True if PA0 is 1
			fuel = fuel + 1;
		}
		if (button1 == 0x02) { // True if PA1 is 1
			fuel = fuel + 2;
		}
		if (button2 == 0x04) { // True if PA2 is 1
			fuel = fuel + 4;
		}
		if (button3 == 0x08) { // True if PA3 is 1
			fuel = fuel + 8;
		}
		
		if ((button4 == 0x10) && (button5 == 0x20) && (button6 != 0x40)) { // True if PA3 is 1
			light = light + 128;
		}
		// 3) write results to port
		if (fuel <= 0)
		{
			light = light + 64;
		}
		if ((fuel > 0) && (fuel <= 2))
		{
			light = light + 96;
		}
		if ((fuel >= 3) && (fuel <= 4))
		{
			light = light + 112;
		}
		if ((fuel >= 5) && (fuel <= 6))
		{
			light = light + 56;
		}
		if ((fuel >= 7) && (fuel <= 9))
		{
			light = light + 60;
		}
		if ((fuel >= 10) && (fuel <= 12))
		{
			light = light + 62;
		}
		if ((fuel >= 13) && (fuel <= 15))
		{
			light = light + 63;
		}
		PORTC = light;
	}
}