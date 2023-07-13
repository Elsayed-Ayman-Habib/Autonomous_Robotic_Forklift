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
                                        DioConf_TX1_PORT_NUM                ,DioConf_TX1_CHANNEL_NUM,
                                        DioConf_RX1_PORT_NUM                ,DioConf_RX1_CHANNEL_NUM,
                                        DioConf_TX2_PORT_NUM                ,DioConf_TX2_CHANNEL_NUM,
                                        DioConf_RX2_PORT_NUM                ,DioConf_RX2_CHANNEL_NUM,
                                        DioConf_TX3_PORT_NUM                ,DioConf_TX3_CHANNEL_NUM,
                                        DioConf_RX3_PORT_NUM                ,DioConf_RX3_CHANNEL_NUM,
                                        DioConf_STEERING_PWM_PORT_NUM       ,DioConf_STEERING_PWM_CHANNEL_NUM,
                                        DioConf_STEERING_INT1_PORT_NUM      ,DioConf_STEERING_INT1_CHANNEL_NUM,
                                        DioConf_STEERING_INT2_PORT_NUM      ,DioConf_STEERING_INT2_CHANNEL_NUM,
                                        DioConf_DIFFERENTIAL_PWM_PORT_NUM   ,DioConf_DIFFERENTIAL_PWM_CHANNEL_NUM,
                                        DioConf_DIFFERENTIAL_INT1_PORT_NUM  ,DioConf_DIFFERENTIAL_INT1_CHANNEL_NUM,
                                        DioConf_DIFFERENTIAL_INT2_PORT_NUM  ,DioConf_DIFFERENTIAL_INT2_CHANNEL_NUM,
                                        DioConf_ENCODER_VELOCITY_A_PORT_NUM ,DioConf_ENCODER_VELOCITY_A_CHANNEL_NUM,
                                        DioConf_ENCODER_VELOCITY_B_PORT_NUM ,DioConf_ENCODER_VELOCITY_B_CHANNEL_NUM,
                                        DioConf_ENCODER_ANGLE_A_PORT_NUM    ,DioConf_ENCODER_ANGLE_A_CHANNEL_NUM,
                                        DioConf_ENCODER_ANGLE_B_PORT_NUM    ,DioConf_ENCODER_ANGLE_B_CHANNEL_NUM,
                                        DioConf_LED1_PORT_NUM               ,DioConf_LED1_CHANNEL_NUM,
                                        DioConf_SPI_TX_PORT_NUM             ,DioConf_SPI_TX_CHANNEL_NUM,
                                        DioConf_SPI_RX_PORT_NUM             ,DioConf_SPI_RX_CHANNEL_NUM,
                                        DioConf_SPI_CLK_PORT_NUM            ,DioConf_SPI_CLK_CHANNEL_NUM,
                                        DioConf_SPI_FSS_PORT_NUM            ,DioConf_SPI_FSS_CHANNEL_NUM
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
