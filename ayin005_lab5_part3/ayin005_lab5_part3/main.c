/*
 * ayin005_lab5_part3.c
 *
 * Created: 4/22/2019 9:42:28 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	// initialize to 0s
	unsigned char button0 = 0x00;
	
	char light = 0;
	char count;
	while(1)
	{
		// 1) Read Inputs and assign to variables
		button0 = PINA & 0x01; // Mask PINA to only get the bit you are interested in
		
		
		if (button0 && (count== 0))
		{
			light=light + 1;
			count = 1;
		}
		else if (!button0)
		{
			count = 0;
		}
		
		PORTC = light;
	}
}