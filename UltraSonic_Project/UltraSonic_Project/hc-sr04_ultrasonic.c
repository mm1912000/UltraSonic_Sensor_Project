/*
 * hc-sr04_ultrasonic.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Marwan Medhat
 */
#include "hc-sr04_ultrasonic.h"
#include "gpio.h"
#include <util/delay.h>
#include "avr/io.h"
#include "common_macros.h"

/*******************************************************************************
 *                           Configurations                                    *
 *******************************************************************************/

ICU_ConfigType s_config = { ICU_CLOCK, ICU_EDGE }; /* This variable will set the Clock and Edge */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the edge count and echo time in both the ISR and ultrasonic functions  */

static volatile uint8 g_edgecount = 0;
static volatile uint16 g_echotime = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : Function to initialize the ULTRASONIC driver
 * 	1. Initialize the ICU registers
 * 	2. Set the callback function
 * 	3. set the ultrasonic trigger pin as output
 */
void ULTRASONIC_init(void)
{
	ICU_init(&s_config); /* initialize the ICU module */
	ICU_setCallBack(ULTRASONIC_edgeProcessing); /* set the ULTRASONIC_edgeProcessing function as the callback function */
	GPIO_setupPinDirection(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, PIN_OUTPUT); /* set trigger pin as output pin */
}
/*
 * Description : CallBack function
 * 	1. first interrupt will occur when the echo pin is high which means the sesnor was triggered.
 * 	2. increment the edgecount and clear the timer value and set the edge to falling
 * 	3. when another interrupt occurs this means the wave is reflected back to the sensor and edgecount will be incremented
 * 	4. reach the ICR1 value and assign it to the echotime variable.
 */
void ULTRASONIC_edgeProcessing(void)
{
	g_edgecount++; /* increment the variable every interrupt */
	if( g_edgecount == 1 ) /* the echo pin is high now so we will clear the timer value */
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING); /* set the edge detection to falling */
	}
	else if ( g_edgecount == 2 ) /* the code will execute this condition when another interrupt occurs */
	{
		g_echotime = ICU_getInputCaptureValue(); /* now the wave is reflected back to the sensor and assign the echotime variable the ICR1 value */
		ICU_setEdgeDetectionType(RAISING); /* set the edge detection back to high (default) */
	}
}
/*
 * Description : Function to trigger the ultrasonic wave
 * 	1. Set the trigger pin to high
 * 	2. wait 10 micro sec
 * 	3. set the trigger pin to low
 */
void ULTRASONIC_trigger(void)
{
	GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_HIGH); /* Set the trigger pin to high */
	_delay_ms(1); /* pulse of 10µsec or more is given to the Trigger pin */
	GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_LOW); /* set the trigger pin to low after the 10µsec */
}
/*
 * Description : Function to read distance
 * 	1. call the trigger function
 * 	2. wait until the ultrasonic wave is reflected back to the sensor
 * 	3. calculate the distance according to the time taken for the wave to be received by the sensor
 */
uint16 ULTRASONIC_readDistance(void)
{
	uint16 us_distance; /* variable to hold the distance value */

	ULTRASONIC_trigger(); /* function to send the ultrasonic wave */

	_delay_ms(US_MEASURMENT_CYCLE); /* this is the maximum time a wave can take to be reflected back to the sensor */

	if ( g_edgecount == 2 )
	{
		g_edgecount = 0; /* after the wave is received set the edgecount back to 0 to read a new wave if the function is called again */
		/* this equation will convert the ICR1 value to distance */
		us_distance = ( uint16 )(  (  (g_echotime) / (float) ( ( 2 * US_CPU_FREQ ) / (US_PRESCALER * US_SPEED_OF_SOUND) ) ) ) ;
		/* due to the float cast the value will be either rounded up or down so US_TOLERANCE will be set accordingly to try
		 * and achieve the distance as accurate as possible
		 */
		us_distance += US_TOLERANCE;
	}

	return us_distance;

}

