/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port.c
 *        \brief  Port Driver
 *
 *      \details  Source file for Port Driver
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Port.h"
#include "Port_Regs.h"
#include "Port_Cfg.h"
#include "tm4c123gh6pm_registers.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
STATIC const Port_ConfigChannel * Port_Configuration = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType * ConfigPtr)        
* \Description     : Function to Init the Port driver                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : *ConfigPtr   Pointer to link configuration data                     
* \Parameters (out): None                                                      
* \Return value:   : None                                 
*******************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
      /*
      * Set the module state to initialized and point to the PB configuration structure using a global pointer.
      * This global pointer is global to be used by other functions to read the PB configuration structures
      */
      Port_Status       = PORT_INITIALIZED;
      Port_Configuration = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */

      uint8 i ;

    for( i = 0; i < PORT_CONFIGURED_CHANNLES; i++)
	{
      volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
      volatile uint32 delay = 0;
      /*
      * Switch case to determine the Base address of the Port from the attribute port_num in the struct ConfigPtr
      */
      switch(Port_Configuration[i].port_num)
      {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
      }

      /* Enable clock for PORT and allow time for clock to start*/
      SYSCTL_REGCGC2_REG |= (1<<Port_Configuration[i].port_num);
      delay = SYSCTL_REGCGC2_REG;

      if( ((Port_Configuration[i].port_num == 3) && (Port_Configuration[i].pin_num == 7)) || ((Port_Configuration[i].port_num == 5) && (Port_Configuration[i].pin_num == 0)) ) /* PD7 or PF0 */
      {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = GPIO_COMMIT_UNLOCK_NUMBER;                     /* Unlock the GPIOCR register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Configuration[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }
      else if( (Port_Configuration[i].port_num == 2) && (Port_Configuration[i].pin_num <= 3) ) /* PC0 to PC3 */
      {
        continue;
        /* Do Nothing ...  this is the JTAG pins */
      }
      else
      {
        /* Do Nothing ... No need to unlock the commit register for this pin */
      }

      if(Port_Configuration[i].mode == PORT_PIN_MODE_ADC)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[i].pin_num);      /* SET the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configuration[i].pin_num);             /* Disable Digitale Enable for this pin by clear the corresponding bit in GPIODEN register */
      }
      else if(Port_Configuration[i].mode == PORT_PIN_MODE_DIO){
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Configuration[i].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configuration[i].pin_num * 4));     /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configuration[i].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      else{
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Configuration[i].pin_num);              /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((0x0000000F & Port_Configuration[i].mode) << (Port_Configuration[i].pin_num * 4));
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Configuration[i].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }

      if(Port_Configuration[i].direction == PORT_PIN_OUT)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[i].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        if(Port_Configuration[i].init_Val == STD_HIGH)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Configuration[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Configuration[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
      }
      else if(Port_Configuration[i].direction == PORT_PIN_IN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Configuration[i].pin_num);           /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        if(Port_Configuration[i].resistor_state == PULL_UP)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Configuration[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(Port_Configuration[i].resistor_state == PULL_DOWN)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Configuration[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
		else if(Port_Configuration[i].resistor_state == OPEN_DRAIN)
		{
		  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ODR_REG_OFFSET) , Port_Configuration[i].pin_num);          /* Set the corresponding bit in the GPIOPDR register to disable the internal open drain pin */
		}
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Configuration[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Configuration[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ODR_REG_OFFSET) , Port_Configuration[i].pin_num);         /* Clear the corresponding bit in the GPIOPDR register to disable the internal open drain pin */
		}
      }
      else
      {
        /* Do Nothing */
      }
	  
	  if (Port_Configuration[i].output_current == OUT_CURRENT_NA)
	  {
		  CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR2R_REG_OFFSET ) , Port_Configuration[i].pin_num );    /* Clear the corresponding bit in the GPIODR2R register to out 2-mA drive */
		  CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR4R_REG_OFFSET ) , Port_Configuration[i].pin_num );    /* Clear the corresponding bit in the GPIODR4R register to out 4-mA drive */
		  CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR8R_REG_OFFSET ) , Port_Configuration[i].pin_num );    /* Clear the corresponding bit in the GPIODR8R register to out 8-mA drive */
	  }
	  else if (Port_Configuration[i].output_current == OUT_CURRENT_2MA) 
	  {
		 SET_BIT  (*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR2R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Set the corresponding bit in the GPIODR2R register to out 2-mA drive */
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR4R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Clear the corresponding bit in the GPIODR4R register to out 4-mA drive */
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR8R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Clear the corresponding bit in the GPIODR8R register to out 8-mA drive */
	  }
	  else if (Port_Configuration[i].output_current == OUT_CURRENT_4MA) 
	  {
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR2R_REG_OFFSET ) , Port_Configuration[i].pin_num );      /* Clear the corresponding bit in the GPIODR2R register to out 2-mA drive */
		 SET_BIT  (*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR4R_REG_OFFSET ) , Port_Configuration[i].pin_num );      /* Set the corresponding bit in the GPIODR4R register to out 4-mA drive */
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR8R_REG_OFFSET ) , Port_Configuration[i].pin_num );      /* Clear the corresponding bit in the GPIODR8R register to out 8-mA drive */
	  }
	   else if (Port_Configuration[i].output_current == OUT_CURRENT_8MA) 
	  {
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR2R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Clear the corresponding bit in the GPIODR2R register to out 2-mA drive */
		 CLEAR_BIT(*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR4R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Clear the corresponding bit in the GPIODR4R register to out 4-mA drive */
		 SET_BIT  (*(volatile uint32 *) ((volatile uint8 *) PortGpio_Ptr + PORT_DR8R_REG_OFFSET ) , Port_Configuration[i].pin_num );     /* Set the corresponding bit in the GPIODR8R register to out 8-mA drive */
	  }
	  else 
	  {
		/* Do Nothing */  
	  }
	}
}
