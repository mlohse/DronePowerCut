/*******************************************************************************
 * Controller for DronePowerCut                                                *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-11                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#include "ctrl.h"
#include "led.h"
#include "timer.h"
#include "config.h"
#include "decoder.h"
#include <stdint.h>


static uint32_t lastchange;
static state_t state;

static state_t ctrl_update_state(void)
{
	uint16_t val = decoder_value();
	if (!val)
	{
		return STATE_NO_SIGNAL;
	}
	if (val < CTRL_DECODER_VAL_MIN || val > CTRL_DECODER_VAL_MAX)
	{
		return STATE_INVALID_SIGNAL;
	}
	return (val > CTRL_DECODER_VAL_TRIG ?
	            (CTRL_DECODER_INVERT ? STATE_PWR_ON : STATE_PWR_OFF) :
	            (CTRL_DECODER_INVERT ? STATE_PWR_OFF : STATE_PWR_ON));
}

void ctrl_init(void)
{
	state = STATE_NO_SIGNAL;
	lastchange = timer_uptime();
}

void ctrl_run(void)
{
	state_t tmp = ctrl_update_state();
	uint32_t uptime = timer_uptime();

	if (state != tmp)
	{
		state = tmp;
		lastchange = uptime;
	}

	switch (state)
	{
		case STATE_NO_SIGNAL:
			/* no signal from receiver -> turn off act led */
			led_off(LED_ACT);
			break;
		case STATE_INVALID_SIGNAL:
			/* invalid signal -> flash act led 5Hz */
			led_set(LED_ACT, (uptime % CTRL_INTVAL_INVALID_SIG) < (CTRL_INTVAL_INVALID_SIG / 2));
			break;
		case STATE_PWR_OFF:
			led_on(LED_ACT); /* valid signal from receiver */
			if ((uptime - lastchange) > CTRL_DELAY_PWR_OFF)
			{
				led_on(LED_OPT);
				led_on(LED_OFF);
			}
			break;
		case STATE_PWR_ON:
			led_on(LED_ACT); /* valid signal from receiver */
			if ((uptime - lastchange) > CTRL_DELAY_PWR_ON)
			{
				led_off(LED_OPT);
				led_off(LED_OFF);
			}
			break;
	}
}

state_t ctrl_state(void)
{
	return state;
}
