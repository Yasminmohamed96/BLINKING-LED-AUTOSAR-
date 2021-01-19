/******************************************************************************
*
* Module: Port
*
* File Name: Port.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
*
* Author: Yasmin Mohamed 
******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

STATIC const Port_ConfigChannel *port_PortChannels = NULL_PTR;
STATIC uint8 Port_Driver_Status = PORT_NOT_INITIALIZED;
/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*			   - give default values for the pins 
*              - Setup the pin as Digital or analoge pin according to the mode choosen
*              - Setup the direction of the pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr) 
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
/* check if the input configuration pointer is not a NULL_PTR */
if (NULL_PTR == ConfigPtr)
{
  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_PARAM_CONFIG);
}
else
#endif
{
  volatile uint32 * PortGPIOFromConfig_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  volatile uint32 * TempBase_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  volatile uint32 delay= 0;
  volatile uint32 mode= 0;
  volatile uint32 pin= 0;

  uint32 PORTS_COUNTER,itr = 0;
  port_PortChannels = (ConfigPtr->port_channels);/*point to array of structure contains all configuration needed */

  for (PORTS_COUNTER=0;PORTS_COUNTER < PORTS_TOTAL_COUNT;PORTS_COUNTER++)
  {	
      /* Enable clock for each PORT and allow time for clock to start*/
      SYSCTL_REGCGC2_REG |= (1 << PORTS_COUNTER);
      delay = SYSCTL_REGCGC2_REG;
  }
  port_PortChannels = (ConfigPtr->port_channels);/*point to array of structure contains all configuration needed */

  for (itr = 0; itr < PORT_CONFIGURED_CHANNLES; itr++)
  {
      mode=port_PortChannels[itr].mode;
      pin=port_PortChannels[itr].pin_num;	

      /*get port base address */
      switch (port_PortChannels[itr].port_num) 
      {
        case PORTA_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case PORTB_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTB_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case PORTC_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTC_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case PORTD_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTD_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case PORTE_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTE_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case PORTF_ID:
        TempBase_Ptr = (volatile uint32 * ) GPIO_PORTF_BASE_ADDRESS; /* PORTA Base Address */
        break;
      }
      if ((port_PortChannels[itr].port_num == PORTC_ID) && (port_PortChannels[itr].pin_num <= 3)) /* PC0 to PC3 */ 
      {
        continue;
        /* Do Nothing ...  this is the JTAG pins */
      }
      /*port d pin 7 & port f pin 0 need to be unlocked at the beginning */
      if ((( port_PortChannels[itr].port_num == PORTD_ID) && (port_PortChannels[itr].pin_num == PORT_PIN7)) || ((port_PortChannels[itr].port_num== PORTF_ID) && (port_PortChannels[itr].pin_num == PORT_PIN0)) ) /* PD7 or PF0 */ 
      {
        *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; /* Unlock the GPIOCR register */
        SET_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_COMMIT_REG_OFFSET), port_PortChannels[itr].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }

      /*set the direction for the pin and its initial value or resistor type */	
      if(port_PortChannels[itr].direction == OUTPUT)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_DIR_REG_OFFSET) , pin);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        if(port_PortChannels[itr].initial_value == STD_HIGH)
        {
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_DATA_REG_OFFSET) ,pin);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_DATA_REG_OFFSET) , pin);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
      }
      else if(port_PortChannels[itr].direction == INPUT)
      {
        if (port_PortChannels[itr].resistor == PULL_UP)
        {
          SET_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_PULL_UP_REG_OFFSET), pin); /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        } 
        else if (port_PortChannels[itr].resistor == PULL_DOWN) 
        {
           SET_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_PULL_DOWN_REG_OFFSET), pin); /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        } 
        else 
        {
           CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_PULL_UP_REG_OFFSET), pin); /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
           CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_PULL_DOWN_REG_OFFSET), pin); /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
      }	
      /*IF THE MODE WAS ONE OF THOSE ANALOGE MODE */
      if ((mode==ADC) ||(mode==Analog_Comparators)||(mode==USB))
      {
         CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), pin); /* DISABLE digital function for this pin by clear the corresponding bit in GPIODEN register */
         SET_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), pin); /* SET the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ALT_FUNC_REG_OFFSET) , port_PortChannels[itr].pin_num);             /* enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      }
      else
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , port_PortChannels[itr].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        *(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (port_PortChannels[itr].pin_num * 4));     /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , port_PortChannels[itr].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        if (mode==DIO)
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ALT_FUNC_REG_OFFSET) , port_PortChannels[itr].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        }	
        else
        {	
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ALT_FUNC_REG_OFFSET) , port_PortChannels[itr].pin_num);             /* enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
          /*IF THE MODE WAS DIGITAL MODE or SAME PIN MODE CAN BE CONFIGURED ON DIFFERENT PINS
          *FOR EXAMPLE : CAN0RX CAB BE CONFIGURED ON PORT F PIN 0 OR ON PORT B,E PIN 5 SO 
          *IN CASE OF PORT B AND E PORT CONTROL REGISTER SHOULD HAVE THIS VALUE 0x00000008 SHIFTED ACCORDING TO THE PIN NUMBER 
          *IN CASE OF PORT F PORT CONTROL REGISTER SHOULD HAVE THIS VALUE 0x00000003 SHIFTED ACCORDING TO THE PIN NUMBER 
          *SO IN PORT.H CAN0RX IS DEFINED AS 0x00000008 WHEN THE USER CHOOSE THE PIN IN PORT F IT IS CONSIDERED AS SPECIAL CASE AND HANDLED HER ELSE 
          *IT WILL JUST PUT THE VALUE OF THE MODE IN THE CONTROL REGISTER SHIFTED BY THE PIN NUMER 
          */
          if ((mode==CAN))
            {
              if((PORTF_ID==port_PortChannels[itr].port_num))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000003<< (pin * 4));} /* set the PMCx bits for this pin */
              else 
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (pin * 4));} /* set the PMCx bits for this pin */

            }
          
          else if ((mode==U1TS))
            {
              if((PORTC_ID==port_PortChannels[itr].port_num))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (pin * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (pin * 4));}
            }
  
          else if ((mode==UART))
            {
              if((PORTC_ID==port_PortChannels[itr].port_num))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000002<< (pin * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (pin * 4));}
            }
          else if (mode==SSI)
            {
              if((PORTD_ID==port_PortChannels[itr].port_num))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (pin * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000002<< (pin * 4));} /* set the PMCx bits for this pin */

            }

          else if ((mode==USB0PFLT)||(mode==USB0EPEN)||(mode==NMI))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (pin * 4)); /* set the PMCx bits for this pin */
            }
           else if ((mode==M0FAULT0)||(mode==M0PWM))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000004<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==M1FAULT0)||(mode==M1PWM))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000005<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==QEI))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000006<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==GPT))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000007<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==I2C))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000003<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==CORE))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x0000000E<< (pin * 4)); /* set the PMCx bits for this pin */
            }
          else
            {
              
            }			        	
          }
        }
      }
  Port_Driver_Status = PORT_INITIALIZED;	
  }
}

/*******************************************************************************************************************************************************/
/************************************************************************************
* Service Name: FIND OUT WHICH PORT A SAPACIFIC PIN BELONGS TO
* Parameters (in): Pin - Port Pin ID number 
* Return value: PORT_ID
* Description:return the port number or id .
************************************************************************************/ 
 STATIC Port_PortType Get_Port_Id(Port_PinType pin){
	Port_PortType port_id ;
	if ((pin >= PORT_A_START) && (pin <= PORT_A_FINISH))
	{
		port_id = PORTA_ID;
	}
	else if ((pin >= PORT_B_START) && (pin <= PORT_B_FINISH))
	{
		port_id = PORTB_ID;
	}
	else if ((pin >= PORT_C_START) && (pin <= PORT_C_FINISH))
	{
		port_id = PORTC_ID;
	}
	else if ((pin >= PORT_D_START) && (pin <= PORT_D_FINISH))
	{
		port_id = PORTD_ID;

	}
	else if ((pin >= PORT_E_START) && (pin <= PORT_E_FINISH))
	{
		port_id = PORTE_ID;

	}
	else if ((pin >= PORT_F_START) && (pin <= PORT_F_FINISH))
	{
		port_id = PORTF_ID;

	}
	else
	{

	}

	return port_id;
}

/************************************************************************************
* Service Name: RETURN PIN NUMBER MAPPED FROM 0 TO 7 
* Parameters (in): Pin - Port Pin ID number 
* Description:RETURN PIN NUMBER MAPPED FROM 0 TO 7 .
************************************************************************************/
STATIC Port_PinType Get_Pin_Id(Port_PinType pin)
{
	Port_PinType pin_id ;
	pin_id = ( pin% PINS_PER_PORT )-1;/*as pins start from 0 to 7 */
	return pin_id;
}
/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
 void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
 {
	 Port_PortType PORT_ID_MAPPED;
	 Port_PinType  PIN_ID_MAPPED;
	 volatile uint32 * Port_Ptr = NULL_PTR;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
        if (Port_Driver_Status == PORT_NOT_INITIALIZED)
        {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_UNINIT);
        }
        else
	#endif
	{
          PORT_ID_MAPPED = Get_Port_Id(Pin);
          PIN_ID_MAPPED = Get_Pin_Id(Pin);
	  #if (PORT_DEV_ERROR_DETECT == STD_ON)
          if(port_PortChannels[Pin].PinDirectionChangeable == STD_OFF)
          {
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_DIRECTION_UNCHANGEABLE);
          }
          if ((PIN_ID_MAPPED > PORT_PINS_PER_PORT_COUNT)||(PIN_ID_MAPPED <0))
           {
             Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_PARAM_PIN);
           }
	else 
	#endif
	{
          switch (PORT_ID_MAPPED) {
          case PORTA_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTB_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTB_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTC_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTC_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTD_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTD_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTE_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTE_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTF_ID:
          Port_Ptr = (volatile uint32 * ) GPIO_PORTF_BASE_ADDRESS; /* PORTA Base Address */
          break;
          }
         if (Direction == OUTPUT) 
           {
           SET_BIT( * (volatile uint32 * )((volatile uint8 * ) Port_Ptr + PORT_DIR_REG_OFFSET), Pin); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
           } 
         else if (Direction == INPUT)
            {
           CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) Port_Ptr + PORT_DIR_REG_OFFSET),Pin); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            }
          } 
        }
}
#endif


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
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif 
	{
		/* the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/*  Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/*software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
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
void Port_RefreshPortDirection( void )
{       
       uint8 itr;
       volatile uint32 * Port_Ptr = NULL_PTR;
       #if (PORT_DEV_ERROR_DETECT == STD_ON)
	if (Port_Driver_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_UNINIT);
	}
	else
	#endif
	{
	for (itr = 0; itr < PORT_CONFIGURED_CHANNLES; itr++)
	{
          if (port_PortChannels[itr].PinDirectionChangeable==STD_ON){continue;}
          else {
		/*get port */
		switch (port_PortChannels[itr].port_num) 
		{
			case PORTA_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			break;
			case PORTB_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTB_BASE_ADDRESS; /* PORTA Base Address */
			break;
			case PORTC_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTC_BASE_ADDRESS; /* PORTA Base Address */
			break;
			case PORTD_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTD_BASE_ADDRESS; /* PORTA Base Address */
			break;
			case PORTE_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTE_BASE_ADDRESS; /* PORTA Base Address */
			break;
			case PORTF_ID:
			Port_Ptr = (volatile uint32 * ) GPIO_PORTF_BASE_ADDRESS; /* PORTA Base Address */
			break;
		}
		if (port_PortChannels[itr].direction == OUTPUT)
			{
				SET_BIT( * (volatile uint32 * )((volatile uint8 * ) Port_Ptr + PORT_DIR_REG_OFFSET), port_PortChannels[itr].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
			}
		else if (port_PortChannels[itr].direction == INPUT) 
			{
				CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) Port_Ptr + PORT_DIR_REG_OFFSET), port_PortChannels[itr].pin_num); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
			}
		}
	}
    }
}
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Sets the port pin mode..
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType mode )
{
	Port_PortType PORT_ID_MAPPED;
	Port_PinType  PIN_ID_MAPPED;
	PORT_ID_MAPPED = Get_Port_Id(Pin);
	PIN_ID_MAPPED = Get_Pin_Id(Pin);
	volatile uint32 * TempBase_Ptr = NULL_PTR;

	#if (PORT_DEV_ERROR_DETECT == STD_ON)
	if (Port_Driver_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_UNINIT);
	}
	if ((mode!= USB)||(USB0PFLT)||(mode!=USB0EPEN )||(mode!=ADC)||(mode!=Analog_Comparators )||(mode!=DIO)||(mode!=CAN )
            ||(mode!=I2C)||(mode!=CORE )||(mode!=UART)||(mode!=U1TS )||(mode!=SSI)
            ||(mode!= GPT)||(mode!=M0PWM)||(mode!=QEI )||(mode!=NMI)||(mode!=M0FAULT0 )
            ||(mode!=M1FAULT0)||(mode!=M1PWM ))
        {
            Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_PARAM_INVALID_MODE);
        }
	
	 if((port_PortChannels[Pin].PinModeChangeable == STD_OFF))
	 {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_MODE_UNCHANGEABLE);
	 }
	 
	 
	if (PIN_ID_MAPPED > PORT_PINS_PER_PORT_COUNT)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_PARAM_PIN);
	}
       
	else
        #endif
	{
	
	/*get port base address  */
	switch (PORT_ID_MAPPED) 
	{
          case PORTA_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTB_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTB_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTC_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTC_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTD_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTD_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTE_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTE_BASE_ADDRESS; /* PORTA Base Address */
          break;
          case PORTF_ID:
          TempBase_Ptr = (volatile uint32 * ) GPIO_PORTF_BASE_ADDRESS; /* PORTA Base Address */
          break;
	}
	*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PIN_ID_MAPPED * 4));     /* Clear the PMCx bits for this pin */
 /*each mode represent a number which is same as the one should be written in the control register so i shift that number according to the pin number then put it in ctrl reg*/
	/*IF THE MODE WAS ONE OF THOSE ANALOGE MODE */
	if ((mode==ADC) ||(mode==Analog_Comparators)||(mode==USB))
	{
          CLEAR_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), PIN_ID_MAPPED); /* DISABLE digital function for this pin by clear the corresponding bit in GPIODEN register */
          SET_BIT( * (volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), PIN_ID_MAPPED); /* SET the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                  
	}
	else{
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PIN_ID_MAPPED);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            *(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PIN_ID_MAPPED * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PIN_ID_MAPPED);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        if (mode==DIO) 
	{
          *(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_CTL_REG_OFFSET) &= ~(mode << (PIN_ID_MAPPED* 4));     /* Clear the PMCx bits for this pin */	
	}	
	else{	
      
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)TempBase_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PIN_ID_MAPPED);             /* enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

        if ((mode==CAN))
            {
              if((PORTF_ID==PORT_ID_MAPPED))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000003<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */
              else 
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */

            }
          
          else if ((mode==U1TS))
            {
              if((PORTC_ID==PORT_ID_MAPPED))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (PIN_ID_MAPPED * 4));}
            }
  
          else if ((mode==UART))
            {
              if((PORTC_ID==PORT_ID_MAPPED))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000002<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (PIN_ID_MAPPED * 4));}
            }
          else if (mode==SSI)
            {
              if((PORTD_ID==PORT_ID_MAPPED))
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000001<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */
              else
              {*(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000002<< (PIN_ID_MAPPED * 4));} /* set the PMCx bits for this pin */

            }
          else if ((mode==USB0PFLT)||(mode==USB0EPEN)||(mode==NMI))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000008<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
           else if ((mode==M0FAULT0)||(mode==M0PWM))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000004<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==M1FAULT0)||(mode==M1PWM))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000005<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==QEI))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000006<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==GPT))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000007<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==I2C))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x00000003<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else if ((mode==CORE))
            {
              *(volatile uint32 * )((volatile uint8 * ) TempBase_Ptr + PORT_CTL_REG_OFFSET) |=(0x0000000E<< (PIN_ID_MAPPED * 4)); /* set the PMCx bits for this pin */
            }
          else
            {				

	    }
	}
    }	
  }
}
#endif