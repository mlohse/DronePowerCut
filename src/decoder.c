/*******************************************************************************
 * Servo decoder using Timer1 (16Bit)                                          *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-05                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#include "decoder.h"
#include "config.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint16_t value = 0;

/*******************************************************************************
 * Timer1 @1MHz: no prescaler: 1000000 inc/sec (~1us resolution)               *
 *                                                                             *
 * -> OCR1A (Compare Match A) is used as timeout for servo signal              *
 *    On timeout value will be set to '0' (invalid)                            *
 *                                                                             *
 * -> On raising edge of servo input timer1 is cleared                         *
 *                                                                             *
 * -> On faling edge timer1 is stored in value (~period in us of servo input)  *
 ******************************************************************************/

/**
 * ISR for Compare Match A (timeout)
 */
ISR(TIMER1_COMPA_vect)
{
	/* timeout - no servo signal! */
	value = 0;
}

/**
 * ISR for pin change PCINT[16..23]
 * @todo vector depends on input pin and should be configurable via config!
 */
ISR(PCINT2_vect)
{
	uint8_t rising_edge = DECODER_INPUT_PORT & (1 << DECODER_INPUT_PIN);
	if (rising_edge)
	{
		/* clear/start timer on raising edge */
		TCNT1 = 0;
	}
	else
	{
		/* on falling edge: store period in value (~in usec.) */
		value = TCNT1;
	}
}

void decoder_init(void)
{
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS10); /* CTC-Mode, no prescaler */

	TIMSK1 &= (uint8_t)~(1 << TOIE1); /* TOIE1 = 0 (Timer1 overflow IRQ) */
	TIMSK1 |= (1 << OCIE1A);  /* OCIE1A = 1 (Timer1 Compare Match A IRQ) */

	OCR1A = DECODER_TIMEOUT_NOSIG;  /* irq on timeout */
	
	/** @todo: enabling pin change interrupts depends on input pin and should be configurable via config as well! */
	PCICR |= (1 << PCIE2);    /* enable irq for PCINT[16..23] */
	PCMSK2 |= (1 << PCINT18); /* enable pin change irq for PCINT18 */
}

uint16_t decoder_value(void)
{
	uint16_t tmp;
	cli();
	tmp = value;
	sei();
	return tmp;
}

