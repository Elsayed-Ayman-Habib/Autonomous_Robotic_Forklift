/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio.c
 *        \brief  Dio
 *
 *      \details  Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio.h"
#include "Dio_Regs.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
STATIC const Dio_ConfigPorts * Dio_Ports = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

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
* \Syntax          : Std_ReturnType Dio_ReadChannel(Dio_ChannelType ChannelId)        
* \Description     : Function to return the value of the specified DIO_channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_ChannelType ChannelId                     
* \Parameters (out): VALUE_READ                                                      
* \Return value:   : boolean  STD_HIGH
*                             STD_LOW                                  
*******************************************************************************/

void Dio_Init(const Dio_ConfigType * ConfigPtr)
{
        Dio_Status       = DIO_INITIALIZED;
        Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
}
/******************************************************************************
* \Syntax          : Std_ReturnType Dio_ReadChannel(Dio_ChannelType ChannelId)        
* \Description     : Function to return the value of the specified DIO_channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_ChannelType ChannelId                     
* \Parameters (out): VALUE_READ                                                      
* \Return value:   : boolean  STD_HIGH
*                             STD_LOW                                  
*******************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean VALUE_READ = STD_LOW; 
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
                if (BIT_IS_SET(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num))
                {
                  VALUE_READ = STD_HIGH;
                }
                else if (BIT_IS_CLEAR(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num))
                {
                  VALUE_READ = STD_LOW;
                }

        return VALUE_READ ;
}
/******************************************************************************
* \Syntax          : Std_ReturnType Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);        
* \Description     : Function of write channel.                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_ChannelType ChannelId, Dio_LevelType Level                    
* \Parameters (out): None                                                      
* \Return value:   : None                                 
*******************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  volatile uint32 * Port_Ptr = NULL_PTR;
  switch(Dio_PortChannels[ChannelId].Port_Num)
  {
  case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
  break;
  case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
  break;
  case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
  break;
  case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
  break;
  case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
  break;
  case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
  break;
  }
  if(Level == STD_HIGH)
  {
    /* Write Logic High */
    SET_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num);
  }
  else if(Level == STD_LOW)
  {
    /* Write Logic Low */
    CLEAR_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num);
  }
}

/******************************************************************************
* \Syntax          : Std_ReturnType Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);        
* \Description     : Function to flip the level and return the level after flip.                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_ChannelType ChannelId                     
* \Parameters (out): VALUE_FLIP                                                      
* \Return value:   : boolean  STD_HIGH
*                             STD_LOW                                   
*******************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
  volatile uint32 * Port_Ptr = NULL_PTR;
  boolean VALUE_FLIP = STD_LOW;
  switch(Dio_PortChannels[ChannelId].Port_Num)
  {
  case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
  break;
  case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
  break;
  case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
  break;
  case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
  break;
  case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
  break;
  case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
  break;
  }
  if (BIT_IS_SET(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num))
  {
    TOGGLE_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num);
    VALUE_FLIP = STD_LOW;
  }
  else if (BIT_IS_CLEAR(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num))
  {
    TOGGLE_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Channel_Num);
    VALUE_FLIP = STD_HIGH;
  }
return VALUE_FLIP ;
}
/******************************************************************************
* \Syntax          : Std_ReturnType Dio_ReadPort(Dio_PortType PortId);        
* \Description     : Function Read Port level .                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_PortType PortId                     
* \Parameters (out): VALUE_READ                                                      
* \Return value:   : uint8 ( data )  
*                           range of data from 0 to 255 read from data register                                 
*******************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
  volatile uint32 * Port_Ptr = NULL_PTR;
  uint8 VALUE_READ = STD_LOW;
  switch(Dio_Ports[PortId].Port_Num)
  {
  case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
  break;
  case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
  break;
  case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
  break;
  case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
  break;
  case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
  break;
  case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
  break;
  }
  VALUE_READ = *Port_Ptr;
  return VALUE_READ ;
}
/******************************************************************************
* \Syntax          : Std_ReturnType Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);        
* \Description     : Function Write Port level.                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Dio_PortType PortId, Dio_PortLevelType Level                     
* \Parameters (out): None                                                      
* \Return value:   : uint8 ( data )  
*                           range of data from 0 to 255 write from data register                                 
*******************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
  volatile uint32 * Port_Ptr = NULL_PTR;
  switch(Dio_Ports[PortId].Port_Num)
  {
  case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
  break;
  case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
  break;
  case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
  break;
  case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
  break;
  case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
  break;
  case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
  break;
  }
  *Port_Ptr = Level ;
}
/**********************************************************************************************************************
 *  END OF FILE: Dio.c
 *********************************************************************************************************************/
