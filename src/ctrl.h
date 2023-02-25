/*******************************************************************************
 * Controller for DronePowerCut                                                *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-11                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#ifndef CTRL_H_
#define CTRL_H_

#include <stdint.h>


typedef enum
{
	STATE_NO_SIGNAL,
	STATE_INVALID_SIGNAL,
	STATE_PWR_OFF,
	STATE_PWR_ON
} state_t;

/**
 * @brief ctrl_init initialises controller
 */
void ctrl_init(void);

/**
 * @brief ctrl_run runs main application...
 */
void ctrl_run(void);

/**
 * @brief ctrl_state
 * @return returns current state
 */
state_t ctrl_state(void);

#endif /* CTRL_H_ */
