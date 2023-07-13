/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dio-Cfg.h
 *       Module:  Dio-Cfg
 *
 *  Description:  configration file of Dio driver     
 *  
 *********************************************************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES             (17U)

/* Port ID's */
#define Dio_PortA                    (0U)
#define Dio_PortB                    (1U)
#define Dio_PortC                    (2U)
#define Dio_PortD                    (3U)
#define Dio_PortE                    (4U)
#define Dio_PortF                    (5U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_TX_CHANNEL_ID_INDEX                    (uint8)0x00
#define DioConf_RX_CHANNEL_ID_INDEX                    (uint8)0x01
#define DioConf_POT_CHANNEL_ID_INDEX                   (uint8)0x02
#define DioConf_M3_PWM_CHANNEL_ID_INDEX                (uint8)0x03
#define DioConf_M3_INT1_CHANNEL_ID_INDEX               (uint8)0x04
#define DioConf_M3_INT2_CHANNEL_ID_INDEX               (uint8)0x05
#define DioConf_ENCODER_A_CHANNEL_ID_INDEX             (uint8)0x06
#define DioConf_ENCODER_B_CHANNEL_ID_INDEX             (uint8)0x07
#define DioConf_LED1_CHANNEL_ID_INDEX                  (uint8)0x08
#define DioConf_BUZZER_CHANNEL_ID_INDEX                (uint8)0x09
#define DioConf_RIGHT_LED_1_CHANNEL_ID_INDEX           (uint8)0x0A
#define DioConf_RIGHT_LED_2_CHANNEL_ID_INDEX           (uint8)0x0B
#define DioConf_LEFT_LED_1_CHANNEL_ID_INDEX            (uint8)0x0C
#define DioConf_LEFT_LED_2_CHANNEL_ID_INDEX            (uint8)0x0D
#define DioConf_RED_LED_CHANNEL_ID_INDEX               (uint8)0x0E
#define DioConf_GREEN_LED_CHANNEL_ID_INDEX             (uint8)0x0F
#define DioConf_BLUE_LED_CHANNEL_ID_INDEX              (uint8)0x10

/* DIO Configured Port ID's  */
#define DioConf_TX_PORT_NUM                            (Dio_PortType)2 /* PORTC */
#define DioConf_RX_PORT_NUM                            (Dio_PortType)2 /* PORTC */
#define DioConf_POT_PORT_NUM                           (Dio_PortType)4 /* PORTE */
#define DioConf_M3_PWM_PORT_NUM                        (Dio_PortType)1 /* PORTB */
#define DioConf_M3_INT1_PORT_NUM                       (Dio_PortType)1 /* PORTB */
#define DioConf_M3_INT2_PORT_NUM                       (Dio_PortType)1 /* PORTB */
#define DioConf_BUZZER_PORT_NUM                        (Dio_PortType)0 /* PORTA */
#define DioConf_ENCODER_A_PORT_NUM                     (Dio_PortType)1 /* PORTB */
#define DioConf_ENCODER_B_PORT_NUM                     (Dio_PortType)1 /* PORTB */
#define DioConf_LED1_PORT_NUM                          (Dio_PortType)5 /* PORTF */
#define DioConf_RIGHT_LED_1_PORT_NUM                   (Dio_PortType)4 /* PORTE */
#define DioConf_RIGHT_LED_2_PORT_NUM                   (Dio_PortType)4 /* PORTE */
#define DioConf_LEFT_LED_1_PORT_NUM                    (Dio_PortType)0 /* PORTA */
#define DioConf_LEFT_LED_2_PORT_NUM                    (Dio_PortType)0 /* PORTA */
#define DioConf_RED_LED_PORT_NUM                       (Dio_PortType)4 /* PORTE */
#define DioConf_GREEN_LED_PORT_NUM                     (Dio_PortType)4 /* PORTE */
#define DioConf_BLUE_LED_PORT_NUM                      (Dio_PortType)4 /* PORTE */
   
/* DIO Configured Channel ID's */
#define DioConf_TX_CHANNEL_NUM                         (Dio_ChannelType)5 /* Pin_4 in PORTC */
#define DioConf_RX_CHANNEL_NUM                         (Dio_ChannelType)4 /* Pin_5 in PORTC */
#define DioConf_POT_CHANNEL_NUM                        (Dio_ChannelType)2 /* Pin_2 in PORTE */
#define DioConf_M3_PWM_CHANNEL_NUM                     (Dio_ChannelType)5 /* Pin_4 in PORTB */
#define DioConf_M3_INT1_CHANNEL_NUM                    (Dio_ChannelType)4 /* Pin_1 in PORTB */
#define DioConf_M3_INT2_CHANNEL_NUM                    (Dio_ChannelType)0 /* Pin_0 in PORTB */
#define DioConf_BUZZER_CHANNEL_NUM                     (Dio_ChannelType)4 /* Pin_4 in PORTA */
#define DioConf_ENCODER_A_CHANNEL_NUM                  (Dio_ChannelType)2 /* Pin_2 in PORTB */
#define DioConf_ENCODER_B_CHANNEL_NUM                  (Dio_ChannelType)1 /* Pin_1 in PORTB */
#define DioConf_LED1_CHANNEL_NUM                       (Dio_ChannelType)1 /* Pin_1 in PORTF */

#define DioConf_RIGHT_LED_1_CHANNEL_NUM                (Dio_ChannelType)4 /* Pin_4 in PORTE */
#define DioConf_RIGHT_LED_2_CHANNEL_NUM                (Dio_ChannelType)5 /* Pin_5 in PORTE */
#define DioConf_LEFT_LED_1_CHANNEL_NUM                 (Dio_ChannelType)5 /* Pin_5 in PORTA */
#define DioConf_LEFT_LED_2_CHANNEL_NUM                 (Dio_ChannelType)6 /* Pin_6 in PORTA */
#define DioConf_RED_LED_CHANNEL_NUM                    (Dio_ChannelType)1 /* Pin_1 in PORTE */
#define DioConf_GREEN_LED_CHANNEL_NUM                  (Dio_ChannelType)2 /* Pin_2 in PORTE */
#define DioConf_BLUE_LED_CHANNEL_NUM                   (Dio_ChannelType)3 /* Pin_3 in PORTE */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* DIO-CFG.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
