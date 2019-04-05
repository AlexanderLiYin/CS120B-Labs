/*
 * ayin005_lab2_part1.c
 *
 * Created: 4/5/2019 9:47:43 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; // Configure port B's 8 pins as outputs
	PORTB = 0x00; // Initialize PORTB output to 0’s
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}
;
