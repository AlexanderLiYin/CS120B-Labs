/*
 * ayin005_lab10_part5.c
 *
 * Created: 5/8/2019 1:14:45 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) { //x is the button. K is 0 or 1
	return ((x & (0x01 << k)) != 0);
}

unsigned char temp=0;
int timer=1000;
enum TL_States {TL_SMStart, TL_Seq0, TL_Seq1, TL_Seq2} TL_State;
enum BL_States {BL_SMStart, BL_LEDOff, BL_LEDOn} BL_State;
enum SP_States {SP_SMStart, SP_Off, SP_On} SP_State;
enum TM_States {TM_SMStart, TM_Up, TM_Down} TM_State;

unsigned char i1=0;
unsigned char i2=0;

void BlinkLED_Tick(unsigned char tmp)
{	
	/*
	if ((i1>2) || (i2>2))
	{
		timer=400;
	}
	else
	{
		timer=1000;
	}
	*/ 
	if ((tmp==1) && (temp <9))
	{
		i2=0;
		temp=temp+1;
		PORTB=temp;
		i1=i1+1;
	}
	
	/*
	else if ((tmp==2) && (temp > 0))
	{
		i1=0;
		temp=temp-1;
		PORTB=temp;
		i2=i2+1;
	}
	
	else if (tmp==3)
	{
		temp=0;
		PORTB=temp;
	}
	*/
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

void Timer_Tick(unsigned char tmp)
{
	if (tmp==1)
	{
		timer++;
	}
	if((tmp==2) && (timer!=1))
	{
		timer--;
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
	
	unsigned char tmpA0;
	unsigned char tmpA1;
	unsigned char tmpA2;
	
	const unsigned long timerPeriod = 200;
	TimerSet(timerPeriod);
	TimerOn();
	
	BL_State=BL_SMStart;
	TL_State=TL_SMStart;
	SP_State=SP_SMStart;
	while(1) {
		tmpA0 = PINA & 0x01;
		tmpA1 = PINA & 0x02;
		tmpA2 = PINA & 0x04;
		/*
		if (TL_elapsedTime>=300)
		{
			ThreeLED_Tick();
			TL_elapsedTime=0;
		}
		*/
		if (BL_elapsedTime >= timer)
		{
			if ((tmpA0!=0x01) && (tmpA2!=0x02))
			{
				BlinkLED_Tick(3);
			}
			else if (tmpA0!=0x01)
			{
				BlinkLED_Tick(1);
			}
			else if (tmpA2!=0x02)
			{
				BlinkLED_Tick(2);
			}
			BL_elapsedTime=0;
		}
		
		/*
		if (tmpA0 != 0x01)
		{
			Timer_Tick(1);
		}
		if (tmpA1 != 0x02)
		{
			Timer_Tick(2);
		}
		if ((tmpA2 != 0x04) && (SP_elapsedTime >= timer))
		{
			Speaker_Tick();
			SP_elapsedTime=0;
		}
		*/
		while(!TimerFlag);
		TimerFlag=0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
		SP_elapsedTime += timerPeriod;
	}
}