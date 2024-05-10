 /******************************************************************************
 *
 * Module: Push Button
 *
 * File Name: button.h
 *
 * Description: Header file for the Push Button driver
 *
 * Author: Marwan Medhat
 *
 *******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PULLUP_RESISTOR					TRUE             /* set to TRUE if push button is configured using the pull up resistor and FALSE if pull down */
#define PUSHBUTTON_PORT_ID				PORTC_ID
#define PUSHBUTTON_PIN_ID				PIN7_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the Push Button:
 * 1. Setup the Push Button pin direction by the use of the GPIO driver.
 */
void Button_init();
/*
 * Description :
 * Returns logic low or high depending on whether the button is pressed or not:
 */
uint8 Button_isPressed();

#endif /* BUTTON_H_ */
