 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Yasmin Mohamed 
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1001U)

/* Dio Module Id */
#define PORT_MODULE_ID    (120U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 *  Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Port_Cfg.h"
   
/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"


/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT read Channel */
#define PORT_INIT_SID                       (uint8)0x00

/* Service ID for Sets the port pin direction */
#define PORT_SET_PIN_DIRECTION_SID            (uint8)0x01

/* Service ID for Refreshes port direction. */
#define PORT_REFRESH_PORT_DIRECTION_SID       (uint8)0x02

/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID            (uint8)0x03

/* Service ID for Sets the port pin mode. */
#define PORT_SET_PIN_MODE_SID                (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN                 (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG               (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE          (uint8)0x0D

/*
DET code to report API Port_SetPinMode service called when mode is unchangeable.
 */
#define PORT_E_MODE_UNCHANGEABLE           (uint8)0x0E

/*
 * API service called without module initialization
 */
#define PORT_E_UNINIT                         (uint8)0x0F

/*
 *APIs called with a Null Pointer
 */
#define PORT_E_PARAM_POINTER                   (uint8)0x10
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

   
/* Type definition forPort_PinType used by the DIO APIs */
typedef uint8 Port_PinType;
typedef uint8 Port_PortType;
typedef uint32 Port_modeType;
/* Type definition for Port_PinDirectionType used by the DIO APIs */
typedef uint8 Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the DIO APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;



/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{  
    Port_PortType port_num; 
    Port_PinType pin_num; 
    Port_PinDirection direction;
    Port_modeType mode;
    uint8 PinDirectionChangeable;
    uint8 PinModeChangeable;
    Port_InternalResistor resistor;
    uint8 initial_value;
} Port_ConfigChannel;

/*Type of the external data structure containing the initialization data for this module. */
typedef struct {
	Port_ConfigChannel port_channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;


#define DIO                     (Port_modeType)0
#define CAN                     (Port_modeType)1
#define I2C                     (Port_modeType)2
#define CORE	                (Port_modeType)3
#define UART	                (Port_modeType)4
#define U1TS	                (Port_modeType)5
#define SSI                     (Port_modeType)6
#define GPT	                (Port_modeType)7
#define M0PWM	                (Port_modeType)8
#define M1PWM           	(Port_modeType)9
#define QEI                     (Port_modeType)10
#define NMI	        	(Port_modeType)11
#define M0FAULT0	        (Port_modeType)12
#define M1FAULT0	        (Port_modeType)13
#define USB0PFLT	        (Port_modeType)14
#define USB0EPEN	        (Port_modeType)15
#define USB                     (Port_modeType)16
#define ADC                     (Port_modeType)17
#define Analog_Comparators      (Port_modeType)18


#define PORTA_ID							(Port_PortType)0
#define PORTB_ID							(Port_PortType)1
#define PORTC_ID							(Port_PortType)2
#define PORTD_ID							(Port_PortType)3
#define PORTE_ID							(Port_PortType)4
#define PORTF_ID							(Port_PortType)5

#define PORT_PIN0 							(Port_PinType)0
#define PORT_PIN1 							(Port_PinType)1
#define PORT_PIN2 							(Port_PinType)2
#define PORT_PIN3 							(Port_PinType)3
#define PORT_PIN4 							(Port_PinType)4
#define PORT_PIN5 							(Port_PinType)5
#define PORT_PIN6 							(Port_PinType)6
#define PORT_PIN7 							(Port_PinType)7

#define PORT_PINS_COUNT						(8U)
#define PORT_PINS_PER_PORT_COUNT	                        (7U)
#define PORTF_PINS_COUNT					(5U)

#define PORTS_TOTAL_COUNT				(6U)


#define PINS_NUM				        (43U)
#define PINS_PER_PORT					(8U)
#define NUMBER_OF_PORTS					(6U)

#define PORT_A_START					(0U)
#define PORT_A_FINISH					(7U)

#define PORT_B_START					(8U)
#define PORT_B_FINISH					(15U)

#define PORT_C_START					(16U)
#define PORT_C_FINISH					(23U)

#define PORT_D_START					(24U)
#define PORT_D_FINISH					(31U)


#define PORT_E_START					(32U)
#define PORT_E_FINISH					(37U)

#define PORT_F_START					(38U)
#define PORT_F_FINISH					(42U)

#define PIN_0							(0U)/* START OF PORT A*/
#define PIN_1							(1U)
#define PIN_2							(2U)
#define PIN_3							(3U)
#define PIN_4							(4U)
#define PIN_5							(5U)
#define PIN_6							(6U)
#define PIN_7							(7U)
#define PIN_8							(8U)/* START OF PORT B*/
#define PIN_9							(9U)
#define PIN_10							(10U)
#define PIN_11							(11U)
#define PIN_12							(12U)
#define PIN_13							(13U)
#define PIN_14							(14U)
#define PIN_15							(15U)
#define PIN_16							(16U)/* START OF PORT C*/
#define PIN_17							(17U)
#define PIN_18							(18U)
#define PIN_19							(19U)
#define PIN_20							(20U)
#define PIN_21							(21U)
#define PIN_22							(22U)
#define PIN_23							(23U)
#define PIN_24							(24U)/* START OF PORT D*/
#define PIN_25							(25U)
#define PIN_26							(26U)
#define PIN_27							(27U)
#define PIN_28							(28U)
#define PIN_29							(29U)
#define PIN_30							(30U)
#define PIN_31							(31U)
#define PIN_32							(32U)/* START OF PORT E*/
#define PIN_33							(33U)
#define PIN_34							(34U)
#define PIN_35							(35U)
#define PIN_36							(36U)
#define PIN_37							(37U)
#define PIN_38							(38U)/* START OF PORT F*/
#define PIN_39							(39U)
#define PIN_40							(40U)
#define PIN_41							(41U)
#define PIN_42							(42U)




/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Initializes the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Sets the port pin direction if PORT_SET_PIN_DIRECTION_API is enabled.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in):  None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection( void );


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in):  None
* Parameters (inout): None
* Parameters (out):  versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description:Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Sets the port pin mode if PORT_SET_PIN_DIRECTION_API is enabled. 
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType mode );
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;
#endif /* PORT_H */
