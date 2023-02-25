/*******************************************************************************
 * main.c                                                                      *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-05                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#include <avr/io.h>
#include "timer.h"
#include "led.h"
#include "config.h"
#include "decoder.h"
#include "ctrl.h"


static void init(void)
{
	/* configure & initialize io ports */
/*	DDRA = IO_DDRA; -> not available on AtMega48 */
	DDRB = IO_DDRB;
	DDRC = IO_DDRC;
	DDRD = IO_DDRD;
	
/*	PORTA = INIT_PORTA; -> not available on AtMega48 */
	PORTB = INIT_PORTB;
	PORTC = INIT_PORTC;
	PORTD = INIT_PORTD;

	timer_init();
/*	led_flash();*/
	decoder_init();
	ctrl_init();
}

int main(void)
{
	init();

	while(1)
	{
		/* insert main code here */
		led_set(LED_PWR, (timer_uptime() % MAIN_INTVAL_PWR) < (MAIN_INTVAL_PWR / 2));
		ctrl_run();
	}
}
