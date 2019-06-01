/*
 * ayin005_project.c
 *
 * Created: 5/21/2019 9:40:37 AM
 * Author : shado
 */ 

#include <avr/io.h>
#include "timer.h" //used for timer
#include "io.h" //used for LCD
#include "stack.h" //stack functions
//#include "seven_seg.h" //code for seven segment display
#include "queue.h" //code for a queue
#include "bit.h" //code for set and get bit
#include "keypad.h" //code for the keypad
#include <avr/eeprom.h>

unsigned char temp=0;
enum TL_States {TL_SMStart, TL_Seq0, TL_Seq1, TL_Seq2} TL_State;
enum BL_States {BL_SMStart, BL_LEDOff, BL_LEDOn} BL_State;
enum SP_States {SP_SMStart, SP_Off, SP_On} SP_State;
void BlinkLED_Tick()
{
	switch (BL_State)
	{
		case BL_SMStart:
		BL_State=BL_LEDOn;
		break;
		
		case BL_LEDOn:
		temp=SetBit(temp, 3, 1);
		PORTB=temp;
		BL_State=BL_LEDOff;
		break;
		
		case BL_LEDOff:
		temp=SetBit(temp, 3, 0);
		PORTB=temp;
		BL_State=BL_LEDOn;
		break;
	}
}

void Speaker_Tick()
{
	switch (SP_State)
	{
		case SP_SMStart:
		SP_State=SP_On;
		break;
		
		case SP_On:
		temp=SetBit(temp, 4, 1);
		PORTB=temp;
		SP_State=SP_Off;
		break;
		
		case SP_Off:
		temp=SetBit(temp, 4, 0);
		PORTB=temp;
		SP_State=SP_On;
		break;
	}
}

void ThreeLED_Tick()
{
	switch(TL_State)
	{
		case TL_SMStart:
		TL_State=TL_Seq0;
		break;
		
		case TL_Seq0:
		temp=SetBit(temp,2,0);
		temp=SetBit(temp,0,1);
		PORTB=temp;
		TL_State=TL_Seq1;
		break;
		
		case TL_Seq1:
		temp=SetBit(temp,0,0);
		temp=SetBit(temp,1,1);
		PORTB=temp;
		TL_State=TL_Seq2;
		break;
		
		case TL_Seq2:
		temp=SetBit(temp,1,0);
		temp=SetBit(temp,2,1);
		PORTB=temp;
		TL_State=TL_Seq0;
		break;
	}
}

void main()
{
	DDRA = 0x00; // Set port B to output
	PORTA = 0xFF; // Init port B to 0s
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	unsigned long SP_elapsedTime = 0;
	unsigned char tmpA1;
	
	const unsigned long timerPeriod = 2;
	TimerSet(timerPeriod);
	TimerOn();
	
	BL_State=BL_SMStart;
	TL_State=TL_SMStart;
	SP_State=SP_SMStart;
	while(1) {
		if (TL_elapsedTime>=300)
		{
			ThreeLED_Tick();
			TL_elapsedTime=0;
		}
		if (BL_elapsedTime >= 1000)
		{
			BlinkLED_Tick();
			BL_elapsedTime=0;
		}
		tmpA1 = PINA & 0x02;
		if ((tmpA1 != 0x02) && (SP_elapsedTime >= 2))
		{
			Speaker_Tick();
			SP_elapsedTime=0;
		}
		while(!TimerFlag);
		TimerFlag=0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		SP_elapsedTime += timerPeriod;
	}
}