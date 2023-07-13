/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
*        \brief
*
*      \details
*
*
*********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Port.h"
#include "Dio.h"
#include "Port_Regs.h"
#include "Port_Cfg.h"
#include "Encoder.h"
#include "Encoder_Cfg.h"
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
STATIC const Encoder_ConfigChannel * Encoder_Configuration1 = NULL_PTR;
STATIC const Encoder_ConfigChanne2 * Encoder_Configuration2 = NULL_PTR;
volatile long encoder_pos =0;
unsigned int IntCtrl_Status = 0;

STATIC uint8 Encoder_Status = ENCODER_NOT_INITIALIZED;
extern float32 measurement;
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
* \Syntax          :void EncoderChannelA_Init (const Encoder_ConfigType * ConfigPtr)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void EncoderChannelA_Init (const Encoder_ConfigType1 * ConfigPtr)
{

  Encoder_Status       = ENCODER_INITIALIZED;
  Encoder_Configuration1 = ConfigPtr->Channels1; /* address of the first Channels structure --> Channels[0] */
uint8 i ;
  for( i = 0; i < ENCODER_CONFIGURED_CHANNLES; i++)
  {

    if (Encoder_Configuration1[i].Sense == EDGE)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin2);
    }
    else if (Encoder_Configuration1[i].Sense == LEVEL)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin2);
    }

    if (Encoder_Configuration1[i].Detect_Edges == SINGLE)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin2);

      if (Encoder_Configuration1[i].Edge == RISING)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin2);
      }
      else if (Encoder_Configuration1[i].Edge == FALLING)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin2);
      }
    }
    else if (Encoder_Configuration1[i].Detect_Edges == BOTH)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin2);
    }

    SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin2);

    if (Encoder_Configuration1[i].Encoder_Notification == INTERRUPT_Off)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin2);
    }
    else if (Encoder_Configuration1[i].Encoder_Notification == INTERRUPT_On)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin2);
    }
  }
}

/******************************************************************************
* \Syntax          :void EncoderChannelA_Init (const Encoder_ConfigType * ConfigPtr)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void EncoderChannelB_Init (const Encoder_ConfigType2 * ConfigPtr)
{

  Encoder_Status       = ENCODER_INITIALIZED;
  Encoder_Configuration2 = ConfigPtr->Channels2; /* address of the first Channels structure --> Channels[0] */
uint8 i ;
  for( i = 0; i < ENCODER_CONFIGURED_CHANNLES; i++)
  {

    if (Encoder_Configuration2[i].Sense == EDGE)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin1);
    }
    else if (Encoder_Configuration2[i].Sense == LEVEL)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin1);
    }

    if (Encoder_Configuration2[i].Detect_Edges == SINGLE)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin1);

      if (Encoder_Configuration2[i].Edge == RISING)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin1);
      }
      else if (Encoder_Configuration2[i].Edge == FALLING)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin1);
      }
    }
    else if (Encoder_Configuration2[i].Detect_Edges == BOTH)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin1);
    }

     SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin1);

    if (Encoder_Configuration2[i].Encoder_Notification == INTERRUPT_Off)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin1);
    }
    else if (Encoder_Configuration2[i].Encoder_Notification == INTERRUPT_On)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin1);
    }
  }
}

/******************************************************************************
* \Syntax          : void GPIOPortF_Handler(void)
* \Description     : GPIO PORTF External Interrupt - ISR
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void GPIOPortB_Handler(void)
{
 IntCtrl_Status = (*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIORIS_REG_OFFSET));

  if (IntCtrl_Status & GPIO_PIN_2)
  {
    if ( (*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + PORT_DATA_REG_OFFSET)) & GPIO_PIN_1)
    {
      encoder_pos++;
    }
    else
    {
      encoder_pos--;
    }
    measurement=encoder_pos/1130.0;
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin2);
  }

//  if (IntCtrl_Status & GPIO_PIN_1)
//  {
//    if ( (*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + PORT_DATA_REG_OFFSET)) & GPIO_PIN_2)
//    {
//      encoder_pos--;
//    }
//    else
//    {
//      encoder_pos++;
//    }
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin1);
//}
}

/******************************************************************************
* \Syntax          : void GPIOPortF_Handler(void)
* \Description     : GPIO PORTF External Interrupt - ISR
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
int Encoder_GetPosition(void)
{
    return encoder_pos;
}

/**********************************************************************************************************************
*  END OF FILE: FileName.c
*********************************************************************************************************************/
