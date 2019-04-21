/*
 * ayin005_Lab5_part1.c
 *
 * Created: 4/21/2019 10:34:02 AM
 * Author : shado
 */ 

#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}


