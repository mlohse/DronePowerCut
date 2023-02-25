/*******************************************************************************
 * Config file for Drone Power Cut board rev. A                                *
 * author:  Markus Lohse <mlohse@gmx.net>                                      *
 * date:    2023-02-05                                                         *
 * license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt              *
 ******************************************************************************/
#ifndef CONFIG_H_
#define CONFIG_H_

#define BOARD_REV_A

/***********************************
 * IO Ports                        *
 ***********************************/
//#define IO_DDRA               0xFF    // -> not available on AtMega48!
#define IO_DDRB                 0xC7    // PortB [0..4] unused out, 3 mosi input, 4 miso input, 5 sck input
#define IO_DDRC                 0xFF    // PortC [0..6] unused out, 7 switch out
#define IO_DDRD                 0xFB    // PortD [0,1,3] unused out, 2 servo in, 4 opto-coupler out, [5..7] LED1-3 out

/* led definition for led.h */
#define PORT_LED0               PORTD
#define PORT_LED1               PORTD
#define PORT_LED2               PORTD
#define PORT_LED3               PORTD

#define PIN_LED0                4       // opto-coupler out (LED_PWR)
#define PIN_LED1                5       // red
#define PIN_LED2                6       // green
#define PIN_LED3                7       // blue

#define LED_NUM                 4

/* led names to be used with led_on, led_off,... */
#define LED_OPT                 0
#define LED_PWR                 3
#define LED_ACT                 2
#define LED_OFF                 1


/***********************************
 * Initialization                  *
 ***********************************/
//#define INIT_PORTA              0x00  // -> not available on AtMega48!
#define INIT_PORTB              0x38    // pull unused pins to GND, enable pullups for mosi/miso/sck
#define INIT_PORTC              0x00    // pull unused pins to GND
#define INIT_PORTD              0x00    // pull unused pins to GND, switch off leds, disable pullups


/***********************************
 * Servo decoder                   *
 ***********************************/
#define DECODER_INPUT_PORT      PIND    // Port for servo signal to be decoded
#define DECODER_INPUT_PIN       2       // Pin for servo signal
#define DECODER_TIMEOUT_NOSIG   25000   // timeout (us) for reporting "no signal" -> min 40Hz


/***********************************
 * Controller                      *
 ***********************************/
#define CTRL_DECODER_VAL_MIN    750     // min signal length (usec) before signal is being markes as invalid
#define CTRL_DECODER_VAL_MAX    2250    // max signal length (usec) before signal is being markes as invalid
#define CTRL_DECODER_VAL_TRIG   1500    // signal length (usec) triggering power on/off
#define CTRL_DECODER_INVERT     0       // if set '1' on/off states will be inverted
#define CTRL_DELAY_PWR_ON       1500    // 1.5 sec delay before power is restored (should be long enough to ensure that MosFETs do not overheat!)
#define CTRL_DELAY_PWR_OFF      200     // 0.2sec delay before power is cut (~10 pulses)
#define CTRL_INTVAL_INVALID_SIG 200     // interval in msec -> flash act led 5Hz when receiver signal is invalid


/***********************************
 * MAIN                            *
 ***********************************/
#define MAIN_INTVAL_PWR         1000    // interval in msec -> flash pwr led 1Hz

#endif /* CONFIG_H_ */
