/*
 * ayin005_lab10_part2.c
 *
 * Created: 5/6/2019 12:10:53 PM
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

	enum TL_States {TL_SMStart, TL_Seq0, TL_Seq1, TL_Seq2} TL_State;
	enum BL_States {BL_SMStart, BL_LEDOff, BL_LEDOn} BL_State;
	void BlinkLED_Tick();
	void ThreeLED_Tick();
void main()
{
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
	const unsigned long timerPeriod = 500;
	TimerSet(timerPeriod);
	TimerOn();
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	
	BL_State=BL_SMStart;
	TL_State=TL_SMStart;
	while(1) {
		if (TL_elapsedTime>=1000)
		{
			ThreeLED_Tick();
			TL_elapsedTime=0;
		}
		if (BL_elapsedTime >= 1500)
		{
			BlinkLED_Tick();
			BL_elapsedTime=0;
		}
		while(!TimerFlag);
		TimerFlag=0;
		BL_elapsedTime += 500;
		TL_elapsedTime += 500;
	}
}