/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.h
 *
 * Description: Header file for Button Module.
 *
 * Author: Yasmin Mohamed 
 ******************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include "Std_Types.h"

/* Button State according to its configuration PULL UP/Down */
#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH



/* Description: Read the Button state Pressed/Released */
uint8 BUTTON_getState(void);

/* 
 * Description: This function is called every 20ms by Os Task and it responsible for Updating 
 *              the BUTTON State. it should be in a PRESSED State if the button is pressed for 60ms.
 *		and it should be in a RELEASED State if the button is released for 60ms.
 */   
void BUTTON_refreshState(void);

#endif /* BUTTON_H */
