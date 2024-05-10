/*
 * Application.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Marwan Medhat
 */
#include "hc-sr04_ultrasonic.h"
#include <util/delay.h>
#include "lcd.h"
#include"avr/io.h"
#include "button.h"

int main()
{
	uint16 distance ; /* variable to store the distance reading from the UltraSonic sensor */
	uint8 buttonState = 0; /* True if button is pressed and False if not pressed */
	uint8 buttonFlag = 0; /* this variable will be used for toggling purpose */
	uint8 startReading = 0; /* also this variable will be used to either start the reading or not */
	SREG |= (1<<7); /* enable i-bit */
	LCD_init(); /* initialize lcd */
	ULTRASONIC_init(); /* initialize UltraSonic sensor */
	Button_init();
	LCD_displayString("Distance="); /* will display the string on the LCD */
	LCD_displayStringRowColumn(2,0,"cm");

	while(1)
	{
		buttonState = Button_isPressed(); /* check if button is pressed */
		if ( buttonState == TRUE ) /* check if button is pressed */
		{
			_delay_ms(30); /* delay to solve the bouncing issue of the push button */
			if ( buttonState == TRUE && buttonFlag == FALSE) /* check again if the button is pressed and check for the flag*/
			{
				startReading = !startReading; /* set the start reading to true in the first press and everytime the button is pressed this variable will be opposite to the previous value either 1 or 0 */
				buttonFlag = TRUE; /* this variable will be set to True to only execute the startReading equation only once for every press */
			}
		}
		else
		{
			buttonFlag = FALSE; /* if button is not pressed we will return this variable to False to be able to toggle the startReading variable in the next press */
		}

		if ( startReading == TRUE )
			distance = ULTRASONIC_readDistance(); /* read the distance from the UltraSonic sensor */
			if ( distance > 100 )
			{
				LCD_moveCursor(1,0); /* move LCD cursor to the location where the distance value will be displayed */
				LCD_intgerToString(distance); /* display the distance value on the LCD */
			}
			else
			{
				LCD_moveCursor(1,0); /* move LCD cursor to the location where the distance value will be displayed */
				LCD_intgerToString(distance); /* display the distance value on the LCD */
				LCD_displayCharacter(' '); /* if distance value is less than 100 we will display a space character to delete the 3rd digit. */
			}
	}
}
