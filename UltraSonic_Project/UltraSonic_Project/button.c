 /******************************************************************************
 *
 * Module: Push Button
 *
 * File Name: button.c
 *
 * Description: Source file for the Push Button driver
 *
 * Author: Marwan Medhat
 *
 *******************************************************************************/
#include "button.h"
#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Initialize the Push Button:
 * 1. Setup the Push Button pin direction by the use of the GPIO driver.
 */
void Button_init(void)
{
	GPIO_setupPinDirection(PUSHBUTTON_PORT_ID, PUSHBUTTON_PIN_ID, PIN_INPUT); /* set push button as input pin */
}
/*
 * Description :
 * Returns logic low or high depending on whether the button is pressed or not:
 */
uint8 Button_isPressed(void)
{
	uint8 pin_value; /* local variable to store the return value of the GPIO function */
	pin_value = GPIO_readPin(PUSHBUTTON_PORT_ID, PUSHBUTTON_PIN_ID); /* read the state of the push button and store it in the variable */
#if (PULLUP_RESISTOR == FALSE)
	return pin_value; /* will return the value of the variable in pull down resistor configuration*/
#else
	return !pin_value; /* will return the opposite value of the variable in pull up resistor configuration */
#endif
}
