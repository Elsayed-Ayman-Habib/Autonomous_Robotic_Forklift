/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port_Lcfg.c
 *        \brief  Port_Lcfg
 *
 *      \details  Port Link Configuration Source File
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Port.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
const Port_ConfigType Port_ConfigPtr = {
		PORT_PortA , PORT_Pin0, PORT_PIN_IN  , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA, 
		PORT_PortA , PORT_Pin1, PORT_PIN_IN  , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin2, PORT_PIN_IN  , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin3, PORT_PIN_IN  , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin4, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin5, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin6, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortA , PORT_Pin7, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,

		PORT_PortB , PORT_Pin0, PORT_PIN_OUT, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin1, PORT_PIN_IN, PULL_UP, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin2, PORT_PIN_IN , PULL_UP, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin3, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin4, PORT_PIN_OUT, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin5, PORT_PIN_OUT, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_PWM0 , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin6, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortB , PORT_Pin7, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,

		PORT_PortC , PORT_Pin0, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin1, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin2, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin3, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin4, PORT_PIN_IN, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_UART1, OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin5, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_UART1, OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin6, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,
		PORT_PortC , PORT_Pin7, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO  , OUT_CURRENT_NA,

		PORT_PortD , PORT_Pin0, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin1, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin2, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin3, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin4, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin5, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin6, PORT_PIN_IN , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_UART , OUT_CURRENT_NA,
		PORT_PortD , PORT_Pin7, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_UART , OUT_CURRENT_NA,

		PORT_PortE , PORT_Pin0, PORT_PIN_IN  , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortE , PORT_Pin1, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortE , PORT_Pin2, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortE , PORT_Pin3, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortE , PORT_Pin4, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortE , PORT_Pin5, PORT_PIN_OUT , OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,

		PORT_PortF , PORT_Pin0, PORT_PIN_IN, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortF , PORT_Pin1, PORT_PIN_OUT,OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortF , PORT_Pin2, PORT_PIN_OUT,OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortF , PORT_Pin3, PORT_PIN_OUT,OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA,
		PORT_PortF , PORT_Pin4, PORT_PIN_IN, OPEN_DRAIN, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , OUT_CURRENT_NA
};
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
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
