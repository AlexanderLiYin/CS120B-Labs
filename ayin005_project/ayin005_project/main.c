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

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

//Selects input on PORTA for A2D conversion
//default is A0
void Set_A2D_Pin(unsigned char pinNum) {
	ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;
	// Allow channel to stabilize
	static unsigned char i = 0;
	for ( i=0; i<15; i++ ) { asm("nop"); }
}


unsigned char temp=0;
enum TL_States {TL_SMStart, TL_Seq0, TL_Seq1, TL_Seq2} TL_State;
enum BL_States {BL_SMStart, BL_LEDOff, BL_LEDOn} BL_State;
enum SP_States {SP_SMStart, SP_Off, SP_On} SP_State;
	
enum DS_States {DS_Start, DS_S1, DS_2} DS_State;
	
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

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

void DispaySong()
{
	switch(DS_State)
	{
		case DS_Start:
		TL_State=TL_Seq0;
		break;
		
		case DS_S1:
		TL_State=DS_Start;
		break;
		
		case DS_2:
		TL_State=DS_Start;
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

#define ADC_PRECISION 10
#define TS_PRECISION  6     //thumb stick bit precisio

//returns ADC value of thumb stick at pinNum
unsigned char getThumbStickVal(unsigned char pinNum){
	Set_A2D_Pin(pinNum);
	unsigned char tsTruncate = ADC_PRECISION - TS_PRECISION;
	static unsigned char i;
	for(i = 0; i < 24; i++) asm("nop");
	unsigned char thumbStickVal = ADC >> tsTruncate;
	return thumbStickVal;
}

unsigned char rightH, rightV, leftH, leftV;

#define RIGHTH  0
#define RIGHTV  1
#define LEFTH   2
#define LEFTV   3

void main()
{
	DDRA = 0x00; // Set port A to input
	PORTA = 0xFF;
	
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	
	DDRC = 0xF0; // Set port C to output
	PORTC = 0x0F; // Init port C to 0s
	
	DDRD = 0xFF;  
	PORTD = 0x00; 
	
	//ADC_init();
	PWM_on();
	
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	unsigned long SP_elapsedTime = 0;
	
	unsigned short tmpA0;
	unsigned short tmpA1;
	unsigned short tmpA2;
	
	const unsigned long timerPeriod = 2;
	TimerSet(timerPeriod);
	TimerOn();
	
	BL_State=BL_SMStart;
	TL_State=TL_SMStart;
	SP_State=SP_SMStart;
	while(1) {
		/*
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
		*/
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		
		/*
		rightH = getThumbStickVal(RIGHTH);
		rightV = getThumbStickVal(RIGHTV);
		leftH  = getThumbStickVal(LEFTH);
		leftV  = getThumbStickVal(LEFTV);
		*/
		
		if ((tmpA0==0) /*&& (SP_elapsedTime >= 1)*/)
		{
			PORTB=1;
			//Speaker_Tick();
			//SP_elapsedTime=0;
		}
		else if (tmpA1==0)
		{
			PORTB=0;
		}
		
		/*
		if ((tmpA1 < 50) && (SP_elapsedTime >= 300))
		{
			PORTB=1;
			//Speaker_Tick();
			//SP_elapsedTime=0;
		}
		*/
		while(!TimerFlag);
		TimerFlag=0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		SP_elapsedTime += timerPeriod;
	}
}