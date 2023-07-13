/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio_PBcfg.c
 *        \brief  Dio_PBcfg
 *
 *      \details  Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dio.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/* PB structure used with Dio_Init API */
const Dio_ConfigType Dio_Configuration = {
                                        DioConf_TX_PORT_NUM                 ,DioConf_TX_CHANNEL_NUM,       
                                        DioConf_RX_PORT_NUM                 ,DioConf_RX_CHANNEL_NUM,
                                        DioConf_POT_PORT_NUM                ,DioConf_POT_CHANNEL_NUM,
                                        DioConf_M3_PWM_PORT_NUM             ,DioConf_M3_PWM_CHANNEL_NUM,
                                        DioConf_M3_INT1_PORT_NUM            ,DioConf_M3_INT1_CHANNEL_NUM,
                                        DioConf_M3_INT2_PORT_NUM            ,DioConf_M3_INT2_CHANNEL_NUM,
                                        DioConf_ENCODER_A_PORT_NUM          ,DioConf_ENCODER_A_CHANNEL_NUM,
                                        DioConf_ENCODER_B_PORT_NUM          ,DioConf_ENCODER_B_CHANNEL_NUM,
                                        DioConf_LED1_PORT_NUM               ,DioConf_LED1_CHANNEL_NUM,
                                        DioConf_BUZZER_PORT_NUM             ,DioConf_BUZZER_CHANNEL_NUM,
                                        DioConf_RIGHT_LED_1_PORT_NUM        ,DioConf_RIGHT_LED_1_CHANNEL_NUM,
                                        DioConf_RIGHT_LED_2_PORT_NUM        ,DioConf_RIGHT_LED_2_CHANNEL_NUM,
                                        DioConf_LEFT_LED_1_PORT_NUM         ,DioConf_LEFT_LED_1_CHANNEL_NUM,
                                        DioConf_LEFT_LED_2_PORT_NUM         ,DioConf_LEFT_LED_2_CHANNEL_NUM,
                                        DioConf_RED_LED_PORT_NUM            ,DioConf_RED_LED_CHANNEL_NUM,
                                        DioConf_GREEN_LED_PORT_NUM          ,DioConf_GREEN_LED_CHANNEL_NUM,
                                        DioConf_BLUE_LED_PORT_NUM           ,DioConf_BLUE_LED_CHANNEL_NUM
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
