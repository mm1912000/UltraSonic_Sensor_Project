/*
 * hc-sr04_ultrasonic.h
 *
 *  Created on: Feb 26, 2024
 *      Author: Marwan Medhat
 */

#ifndef HC_SR04_ULTRASONIC_H_
#define HC_SR04_ULTRASONIC_H_

#include "icu.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ICU_CLOCK 							F_CPU_8  /* This value should be equal one of the ICU_ClockType enum */
#define ICU_EDGE  							RAISING  /* This value should be equal to one of the ICU_EdgeType enum */
#define ULTRASONIC_TR_PORT_ID 				PORTB_ID
#define ULTRASONIC_TR_PIN_ID 				PIN5_ID
#define US_MEASURMENT_CYCLE					38       /* milliseconds */
#define US_CPU_FREQ							8000000
#define US_PRESCALER						8
#define US_SPEED_OF_SOUND					34000    /* cm/s */
#define US_TOLERANCE						1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ULTRASONIC driver
 * 	1. Initialize the ICU registers
 * 	2. Set the callback function
 * 	3. set the ultrasonic trigger pin as output
 */
void ULTRASONIC_init(void);
/*
 * Description : Function to trigger the ultrasonic wave
 * 	1. Set the trigger pin to high
 * 	2. wait 10 micro sec
 * 	3. set the trigger pin to low
 */
void ULTRASONIC_trigger(void);
/*
 * Description : CallBack function
 * 	1. first interrupt will occur when the echo pin is high which means the sesnor was triggered.
 * 	2. increment the edgecount and clear the timer value and set the edge to falling
 * 	3. when another interrupt occurs this means the wave is reflected back to the sensor and edgecount will be incremented
 * 	4. reach the ICR1 value and assign it to the echotime variable.
 */
void ULTRASONIC_edgeProcessing(void);
/*
 * Description : Function to read distance
 * 	1. call the trigger function
 * 	2. wait until the ultrasonic wave is reflected back to the sensor
 * 	3. calculate the distance according to the time taken for the wave to be received by the sensor
 */
uint16 ULTRASONIC_readDistance(void);


#endif /* HC_SR04_ULTRASONIC_H_ */
