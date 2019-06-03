/*
 * ayin005_lab8.c
 *
 * Created: 6/2/2019 6:04:00 PM
 * Author : shado
 */ 

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void)
{
	DDRC = 0x00;
	PORTC = 0xFF;
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		unsigned short temp =ADC;
		PORTB =temp;
    }
}

