 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Yasmin Mohamed 
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

#define PORT_SET_PIN_DIRECTION_API			 (STD_ON)
#define PORT_SET_PIN_MODE_API				 (STD_ON)

/* Number of comfigured pins*/
#define PORT_CONFIGURED_CHANNLES                 (43U)


/* Configured Port ID's  */
#define PORT_A_NUM                           (Port_PortType)0 /* PORTA */
#define PORT_B_NUM                           (Port_PortType)1 /* PORTB */
#define PORT_C_NUM                           (Port_PortType)2 /* PORTC */
#define PORT_D_NUM                           (Port_PortType)3 /* PORTD */
#define PORT_E_NUM                           (Port_PortType)4 /* PORTE */
#define PORT_F_NUM                           (Port_PortType)5 /* PORTF */

/* Configured Channel ID's */
#define PORT_A_PIN_0                        (Port_PinType)0
#define PORT_A_PIN_1                        (Port_PinType)1
#define PORT_A_PIN_2                        (Port_PinType)2
#define PORT_A_PIN_3                        (Port_PinType)3
#define PORT_A_PIN_4                        (Port_PinType)4
#define PORT_A_PIN_5                        (Port_PinType)5
#define PORT_A_PIN_6                        (Port_PinType)6
#define PORT_A_PIN_7                        (Port_PinType)7

#define PORT_B_PIN_0                        (Port_PinType)0
#define PORT_B_PIN_1                        (Port_PinType)1
#define PORT_B_PIN_2                        (Port_PinType)2
#define PORT_B_PIN_3                        (Port_PinType)3
#define PORT_B_PIN_4                        (Port_PinType)4
#define PORT_B_PIN_5                        (Port_PinType)5
#define PORT_B_PIN_6                        (Port_PinType)6
#define PORT_B_PIN_7                        (Port_PinType)7

#define PORT_C_PIN_0                        (Port_PinType)0
#define PORT_C_PIN_1                        (Port_PinType)1
#define PORT_C_PIN_2                        (Port_PinType)2
#define PORT_C_PIN_3                        (Port_PinType)3
#define PORT_C_PIN_4                        (Port_PinType)4
#define PORT_C_PIN_5                        (Port_PinType)5
#define PORT_C_PIN_6                        (Port_PinType)6
#define PORT_C_PIN_7                        (Port_PinType)7

#define PORT_D_PIN_0                        (Port_PinType)0
#define PORT_D_PIN_1                        (Port_PinType)1
#define PORT_D_PIN_2                        (Port_PinType)2
#define PORT_D_PIN_3                        (Port_PinType)3
#define PORT_D_PIN_4                        (Port_PinType)4
#define PORT_D_PIN_5                        (Port_PinType)5
#define PORT_D_PIN_6                        (Port_PinType)6
#define PORT_D_PIN_7                        (Port_PinType)7

#define PORT_E_PIN_0                        (Port_PinType)0
#define PORT_E_PIN_1                        (Port_PinType)1
#define PORT_E_PIN_2                        (Port_PinType)2
#define PORT_E_PIN_3                        (Port_PinType)3
#define PORT_E_PIN_4                        (Port_PinType)4
#define PORT_E_PIN_5                        (Port_PinType)5


#define PORT_F_PIN_0                        (Port_PinType)0
#define PORT_F_PIN_1                        (Port_PinType)1
#define PORT_F_PIN_2                        (Port_PinType)2
#define PORT_F_PIN_3                        (Port_PinType)3
#define PORT_F_PIN_4                        (Port_PinType)4


// Pin Mode
#define PORT_A_PIN_0_MODE           DIO
#define PORT_A_PIN_1_MODE           DIO
#define PORT_A_PIN_2_MODE           DIO
#define PORT_A_PIN_3_MODE           DIO
#define PORT_A_PIN_4_MODE           DIO
#define PORT_A_PIN_5_MODE           DIO
#define PORT_A_PIN_6_MODE           DIO
#define PORT_A_PIN_7_MODE           DIO

#define PORT_B_PIN_0_MODE           DIO
#define PORT_B_PIN_1_MODE           DIO
#define PORT_B_PIN_2_MODE           DIO
#define PORT_B_PIN_3_MODE           DIO
#define PORT_B_PIN_4_MODE           DIO
#define PORT_B_PIN_5_MODE           DIO
#define PORT_B_PIN_6_MODE           DIO
#define PORT_B_PIN_7_MODE           DIO

#define PORT_C_PIN_0_MODE           DIO
#define PORT_C_PIN_1_MODE           DIO
#define PORT_C_PIN_2_MODE           DIO
#define PORT_C_PIN_3_MODE           DIO
#define PORT_C_PIN_4_MODE           DIO
#define PORT_C_PIN_5_MODE           DIO
#define PORT_C_PIN_6_MODE           DIO
#define PORT_C_PIN_7_MODE           DIO

#define PORT_D_PIN_0_MODE           DIO
#define PORT_D_PIN_1_MODE           DIO
#define PORT_D_PIN_2_MODE           DIO
#define PORT_D_PIN_3_MODE           DIO
#define PORT_D_PIN_4_MODE           DIO
#define PORT_D_PIN_5_MODE           DIO
#define PORT_D_PIN_6_MODE           DIO
#define PORT_D_PIN_7_MODE           DIO

#define PORT_E_PIN_0_MODE           DIO
#define PORT_E_PIN_1_MODE           DIO
#define PORT_E_PIN_2_MODE           DIO
#define PORT_E_PIN_3_MODE           DIO
#define PORT_E_PIN_4_MODE           DIO
#define PORT_E_PIN_5_MODE           DIO


#define PORT_F_PIN_0_MODE           DIO
#define PORT_F_PIN_1_MODE           DIO
#define PORT_F_PIN_2_MODE           DIO
#define PORT_F_PIN_3_MODE           DIO
#define PORT_F_PIN_4_MODE           DIO



// Pin direction
#define PORT_A_PIN_0_DIR            INPUT
#define PORT_A_PIN_1_DIR            INPUT
#define PORT_A_PIN_2_DIR            INPUT
#define PORT_A_PIN_3_DIR            INPUT
#define PORT_A_PIN_4_DIR            INPUT
#define PORT_A_PIN_5_DIR            INPUT
#define PORT_A_PIN_6_DIR            INPUT
#define PORT_A_PIN_7_DIR            INPUT

#define PORT_B_PIN_0_DIR            INPUT
#define PORT_B_PIN_1_DIR            INPUT
#define PORT_B_PIN_2_DIR            INPUT
#define PORT_B_PIN_3_DIR            INPUT
#define PORT_B_PIN_4_DIR            INPUT
#define PORT_B_PIN_5_DIR            INPUT
#define PORT_B_PIN_6_DIR            INPUT
#define PORT_B_PIN_7_DIR            INPUT

#define PORT_C_PIN_0_DIR            INPUT
#define PORT_C_PIN_1_DIR            INPUT 
#define PORT_C_PIN_2_DIR            INPUT
#define PORT_C_PIN_3_DIR            INPUT
#define PORT_C_PIN_4_DIR            INPUT
#define PORT_C_PIN_5_DIR            INPUT 
#define PORT_C_PIN_6_DIR            INPUT
#define PORT_C_PIN_7_DIR            INPUT

#define PORT_D_PIN_0_DIR            INPUT
#define PORT_D_PIN_1_DIR            INPUT
#define PORT_D_PIN_2_DIR            INPUT 
#define PORT_D_PIN_3_DIR            INPUT
#define PORT_D_PIN_4_DIR            INPUT
#define PORT_D_PIN_5_DIR            INPUT
#define PORT_D_PIN_6_DIR            INPUT
#define PORT_D_PIN_7_DIR            INPUT

#define PORT_E_PIN_0_DIR            INPUT
#define PORT_E_PIN_1_DIR            INPUT
#define PORT_E_PIN_2_DIR            INPUT
#define PORT_E_PIN_3_DIR            INPUT
#define PORT_E_PIN_4_DIR            INPUT
#define PORT_E_PIN_5_DIR            INPUT

#define PORT_F_PIN_0_DIR            INPUT
#define PORT_F_PIN_1_DIR            OUTPUT/*LED PIN*/
#define PORT_F_PIN_2_DIR            INPUT
#define PORT_F_PIN_3_DIR            INPUT
#define PORT_F_PIN_4_DIR            INPUT/*SWITCH PIN */



// Pin INITIAL_VALUE.
#define PORT_A_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_1_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_2_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_4_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_5_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_6_INITIAL_VALUE          STD_LOW
#define PORT_A_PIN_7_INITIAL_VALUE          STD_LOW

#define PORT_B_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_1_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_2_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_4_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_5_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_6_INITIAL_VALUE          STD_LOW
#define PORT_B_PIN_7_INITIAL_VALUE          STD_LOW

#define PORT_C_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_1_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_2_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_4_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_5_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_6_INITIAL_VALUE          STD_LOW
#define PORT_C_PIN_7_INITIAL_VALUE          STD_LOW

#define PORT_D_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_1_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_2_INITIAL_VALUE          STD_LOW 
#define PORT_D_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_4_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_5_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_6_INITIAL_VALUE          STD_LOW
#define PORT_D_PIN_7_INITIAL_VALUE          STD_LOW

#define PORT_E_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_E_PIN_1_INITIAL_VALUE          STD_LOW
#define PORT_E_PIN_2_INITIAL_VALUE          STD_LOW
#define PORT_E_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_E_PIN_4_INITIAL_VALUE          STD_LOW
#define PORT_E_PIN_5_INITIAL_VALUE          STD_LOW


#define PORT_F_PIN_0_INITIAL_VALUE          STD_LOW
#define PORT_F_PIN_1_INITIAL_VALUE          STD_LOW/*LED PIN*/
#define PORT_F_PIN_2_INITIAL_VALUE          STD_LOW
#define PORT_F_PIN_3_INITIAL_VALUE          STD_LOW
#define PORT_F_PIN_4_INITIAL_VALUE          STD_HIGH/*SWITCH PIN*/

   
// Pin RESISTOR .
#define PORT_A_PIN_0_resistor         OFF
#define PORT_A_PIN_1_resistor         OFF
#define PORT_A_PIN_2_resistor         OFF
#define PORT_A_PIN_3_resistor         OFF
#define PORT_A_PIN_4_resistor         OFF
#define PORT_A_PIN_5_resistor         OFF
#define PORT_A_PIN_6_resistor         OFF
#define PORT_A_PIN_7_resistor         OFF

#define PORT_B_PIN_0_resistor         OFF
#define PORT_B_PIN_1_resistor         OFF
#define PORT_B_PIN_2_resistor         OFF
#define PORT_B_PIN_3_resistor         OFF
#define PORT_B_PIN_4_resistor         OFF
#define PORT_B_PIN_5_resistor         OFF
#define PORT_B_PIN_6_resistor         OFF
#define PORT_B_PIN_7_resistor         OFF

#define PORT_C_PIN_0_resistor         OFF
#define PORT_C_PIN_1_resistor         OFF 
#define PORT_C_PIN_2_resistor         OFF
#define PORT_C_PIN_3_resistor         OFF
#define PORT_C_PIN_4_resistor         OFF
#define PORT_C_PIN_5_resistor         OFF 
#define PORT_C_PIN_6_resistor         OFF
#define PORT_C_PIN_7_resistor         OFF

#define PORT_D_PIN_0_resistor         OFF
#define PORT_D_PIN_1_resistor         OFF
#define PORT_D_PIN_2_resistor         OFF
#define PORT_D_PIN_3_resistor         OFF
#define PORT_D_PIN_4_resistor         OFF
#define PORT_D_PIN_5_resistor         OFF
#define PORT_D_PIN_6_resistor         OFF
#define PORT_D_PIN_7_resistor         OFF

#define PORT_E_PIN_0_resistor         OFF
#define PORT_E_PIN_1_resistor         OFF
#define PORT_E_PIN_2_resistor         OFF
#define PORT_E_PIN_3_resistor         OFF
#define PORT_E_PIN_4_resistor         OFF
#define PORT_E_PIN_5_resistor         OFF


#define PORT_F_PIN_0_resistor         OFF
#define PORT_F_PIN_1_resistor         OFF/*LED PIN*/
#define PORT_F_PIN_2_resistor         OFF
#define PORT_F_PIN_3_resistor         OFF
#define PORT_F_PIN_4_resistor         PULL_UP /*SWITCH PIN*/

   
// Pin CHANGEE direction.
#define PORT_A_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_1_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_2_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_4_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_5_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_6_DIR_CHANGE         STD_OFF
#define PORT_A_PIN_7_DIR_CHANGE         STD_OFF

#define PORT_B_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_1_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_2_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_4_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_5_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_6_DIR_CHANGE         STD_OFF
#define PORT_B_PIN_7_DIR_CHANGE         STD_OFF

#define PORT_C_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_C_PIN_1_DIR_CHANGE         STD_OFF 
#define PORT_C_PIN_2_DIR_CHANGE         STD_OFF
#define PORT_C_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_C_PIN_4_DIR_CHANGE         STD_OFF
#define PORT_C_PIN_5_DIR_CHANGE         STD_OFF 
#define PORT_C_PIN_6_DIR_CHANGE         STD_OFF
#define PORT_C_PIN_7_DIR_CHANGE         STD_OFF

#define PORT_D_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_1_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_2_DIR_CHANGE         STD_OFF 
#define PORT_D_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_4_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_5_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_6_DIR_CHANGE         STD_OFF
#define PORT_D_PIN_7_DIR_CHANGE         STD_OFF

#define PORT_E_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_E_PIN_1_DIR_CHANGE         STD_OFF
#define PORT_E_PIN_2_DIR_CHANGE         STD_OFF
#define PORT_E_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_E_PIN_4_DIR_CHANGE         STD_OFF
#define PORT_E_PIN_5_DIR_CHANGE         STD_OFF


#define PORT_F_PIN_0_DIR_CHANGE         STD_OFF
#define PORT_F_PIN_1_DIR_CHANGE         STD_OFF
#define PORT_F_PIN_2_DIR_CHANGE         STD_OFF
#define PORT_F_PIN_3_DIR_CHANGE         STD_OFF
#define PORT_F_PIN_4_DIR_CHANGE         STD_OFF


// Pin mode CHANGEE.
#define PORT_A_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_1_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_2_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_4_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_5_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_6_MODE_CHANGE         STD_OFF
#define PORT_A_PIN_7_MODE_CHANGE         STD_OFF

#define PORT_B_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_1_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_2_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_4_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_5_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_6_MODE_CHANGE         STD_OFF
#define PORT_B_PIN_7_MODE_CHANGE         STD_OFF


#define PORT_C_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_C_PIN_1_MODE_CHANGE         STD_OFF 
#define PORT_C_PIN_2_MODE_CHANGE         STD_OFF
#define PORT_C_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_C_PIN_4_MODE_CHANGE         STD_OFF
#define PORT_C_PIN_5_MODE_CHANGE         STD_OFF 
#define PORT_C_PIN_6_MODE_CHANGE         STD_OFF
#define PORT_C_PIN_7_MODE_CHANGE         STD_OFF

#define PORT_D_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_1_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_2_MODE_CHANGE         STD_OFF 
#define PORT_D_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_4_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_5_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_6_MODE_CHANGE         STD_OFF
#define PORT_D_PIN_7_MODE_CHANGE         STD_OFF

#define PORT_E_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_E_PIN_1_MODE_CHANGE         STD_OFF
#define PORT_E_PIN_2_MODE_CHANGE         STD_OFF
#define PORT_E_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_E_PIN_4_MODE_CHANGE         STD_OFF
#define PORT_E_PIN_5_MODE_CHANGE         STD_OFF 


#define PORT_F_PIN_0_MODE_CHANGE         STD_OFF
#define PORT_F_PIN_1_MODE_CHANGE         STD_OFF
#define PORT_F_PIN_2_MODE_CHANGE         STD_OFF
#define PORT_F_PIN_3_MODE_CHANGE         STD_OFF
#define PORT_F_PIN_4_MODE_CHANGE         STD_OFF





#endif /* PORT_CFG_H */
