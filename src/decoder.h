/*******************************************************************************
 * Servo decoder using Timer1 (16Bit)                                          *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-05                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#ifndef DECODER_H_
#define DECODER_H_

#include <stdint.h>

/**
 * @brief decoder_init initializes timer1
 */
void decoder_init(void);

/**
 * @brief decoder_value
 * @returns the current signal length in usec or '0' if there is no signal
 */
uint16_t decoder_value(void);

#endif /* DECODER_H_ */
