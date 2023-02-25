/*******************************************************************************
 * Timer providing simple sleep and uptime functions                           *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-05                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#include "timer.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile uint32_t uptime = 0; /* uptime in ms */

/*******************************************************************************
 * Timer0
 * 1 MHz: pre: 256->3906.25 inc/sec -> OCR0A: 39->100.16irq/sec (~9.98ms resolution)
 ******************************************************************************/
ISR(TIMER0_COMPA_vect)
{
	/* add 10msec on each timer compare match (precision: ~+2%) */
	uptime += 10;
}

void timer_init(void)
{
	uptime = 0;

	TCCR0A = (1 << WGM01); /* CTC-Mode */
	TCCR0B = (1 << CS02); /* clk/256 prescaler (*/

	TIMSK0 &= (uint8_t)~(1 << TOIE0); /* TOIE0 = 0 (Timer0 overflow IRQ) */
	TIMSK0 |= (1 << OCIE0A);  /* OCIE0 = 1 (Timer0 Compare IRQ) */

	OCR0A = 0x27; /* timer compare irq every 9.98ms@1MHz */
}

void timer_msleep(uint32_t ms)
{
	ms += timer_uptime();
	while (timer_uptime() < ms);
}

uint32_t timer_uptime(void)
{
	uint32_t tmp;
	cli();
	tmp = uptime;
	sei();
	return tmp;
}

void timer_clear(void)
{
	cli();
	uptime = 0;
	sei();
}
