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
#define DIO_CONFIGURED_CHANNLES             (21U)

/* Port ID's */
#define Dio_PortA                    (0U)
#define Dio_PortB                    (1U)
#define Dio_PortC                    (2U)
#define Dio_PortD                    (3U)
#define Dio_PortE                    (4U)
#define Dio_PortF                    (5U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_TX1_CHANNEL_ID_INDEX                    (uint8)0x00
#define DioConf_RX1_CHANNEL_ID_INDEX                    (uint8)0x01

#define DioConf_TX2_CHANNEL_ID_INDEX                    (uint8)0x02
#define DioConf_RX2_CHANNEL_ID_INDEX                    (uint8)0x03

#define DioConf_TX3_CHANNEL_ID_INDEX                    (uint8)0x04
#define DioConf_RX3_CHANNEL_ID_INDEX                    (uint8)0x05

#define DioConf_STEERING_PWM_CHANNEL_ID_INDEX           (uint8)0x06
#define DioConf_STEERING_INT1_CHANNEL_ID_INDEX          (uint8)0x07
#define DioConf_STEERING_INT2_CHANNEL_ID_INDEX          (uint8)0x08

#define DioConf_DIFFERENTIAL_PWM_CHANNEL_ID_INDEX       (uint8)0x09
#define DioConf_DIFFERENTIAL_INT1_CHANNEL_ID_INDEX      (uint8)0x0A
#define DioConf_DIFFERENTIAL_INT2_CHANNEL_ID_INDEX      (uint8)0x0B

#define DioConf_ENCODER_VELOCITY_A_CHANNEL_ID_INDEX     (uint8)0x0C
#define DioConf_ENCODER_VELOCITY_B_CHANNEL_ID_INDEX     (uint8)0x0D

#define DioConf_ENCODER_ANGLE_A_CHANNEL_ID_INDEX        (uint8)0x0E
#define DioConf_ENCODER_ANGLE_B_CHANNEL_ID_INDEX        (uint8)0x0F

#define DioConf_LED1_CHANNEL_ID_INDEX                   (uint8)0x10

#define DioConf_SPI_TX_CHANNEL_ID_INDEX                 (uint8)0x11
#define DioConf_SPI_RX_CHANNEL_ID_INDEX                 (uint8)0x12
#define DioConf_SPI_CLK_CHANNEL_ID_INDEX                (uint8)0x13
#define DioConf_SPI_FSS_CHANNEL_ID_INDEX                (uint8)0x14


/* DIO Configured Port ID's  */
#define DioConf_TX1_PORT_NUM                            (Dio_PortType)2 /* PORTC */
#define DioConf_RX1_PORT_NUM                            (Dio_PortType)2 /* PORTC */

#define DioConf_TX2_PORT_NUM                            (Dio_PortType)3 /* PORTD */
#define DioConf_RX2_PORT_NUM                            (Dio_PortType)3 /* PORTD */

#define DioConf_TX3_PORT_NUM                            (Dio_PortType)2 /* PORTC */
#define DioConf_RX3_PORT_NUM                            (Dio_PortType)2 /* PORTC */

#define DioConf_SPI_TX_PORT_NUM                         (Dio_PortType)0 /* PORTC */
#define DioConf_SPI_RX_PORT_NUM                         (Dio_PortType)0 /* PORTC */
#define DioConf_SPI_CLK_PORT_NUM                        (Dio_PortType)0 /* PORTC */
#define DioConf_SPI_FSS_PORT_NUM                         (Dio_PortType)0 /* PORTC */

#define DioConf_STEERING_PWM_PORT_NUM                   (Dio_PortType)4 /* PORTE */
#define DioConf_STEERING_INT1_PORT_NUM                  (Dio_PortType)4 /* PORTE */
#define DioConf_STEERING_INT2_PORT_NUM                  (Dio_PortType)4 /* PORTE */

#define DioConf_DIFFERENTIAL_PWM_PORT_NUM               (Dio_PortType)1 /* PORTB */
#define DioConf_DIFFERENTIAL_INT1_PORT_NUM              (Dio_PortType)1 /* PORTB */
#define DioConf_DIFFERENTIAL_INT2_PORT_NUM              (Dio_PortType)1 /* PORTB */

#define DioConf_ENCODER_VELOCITY_A_PORT_NUM             (Dio_PortType)1 /* PORTB */
#define DioConf_ENCODER_VELOCITY_B_PORT_NUM             (Dio_PortType)1 /* PORTB */

#define DioConf_ENCODER_ANGLE_A_PORT_NUM                (Dio_PortType)3 /* PORTB */
#define DioConf_ENCODER_ANGLE_B_PORT_NUM                (Dio_PortType)3 /* PORTB */

#define DioConf_LED1_PORT_NUM                           (Dio_PortType)5 /* PORTF */


/* DIO Configured Channel ID's */
#define DioConf_TX1_CHANNEL_NUM                         (Dio_ChannelType)5 /* Pin_5 in PORTC */
#define DioConf_RX1_CHANNEL_NUM                         (Dio_ChannelType)4 /* Pin_4 in PORTC */

#define DioConf_TX2_CHANNEL_NUM                         (Dio_ChannelType)7 /* Pin_7 in PORTD */
#define DioConf_RX2_CHANNEL_NUM                         (Dio_ChannelType)6 /* Pin_6 in PORTD */

#define DioConf_TX3_CHANNEL_NUM                         (Dio_ChannelType)7 /* Pin_7 in PORTC */
#define DioConf_RX3_CHANNEL_NUM                         (Dio_ChannelType)6 /* Pin_6 in PORTC */

#define DioConf_SPI_TX_CHANNEL_NUM                      (Dio_ChannelType)2 /* Pin_2 in PORTA */
#define DioConf_SPI_RX_CHANNEL_NUM                      (Dio_ChannelType)3 /* Pin_3 in PORTA */
#define DioConf_SPI_CLK_CHANNEL_NUM                     (Dio_ChannelType)4 /* Pin_4 in PORTA */
#define DioConf_SPI_FSS_CHANNEL_NUM                     (Dio_ChannelType)5 /* Pin_5 in PORTA */

#define DioConf_STEERING_PWM_CHANNEL_NUM                (Dio_ChannelType)4 /* Pin_4 in PORTE */
#define DioConf_STEERING_INT1_CHANNEL_NUM               (Dio_ChannelType)1 /* Pin_1 in PORTE */
#define DioConf_STEERING_INT2_CHANNEL_NUM               (Dio_ChannelType)2 /* Pin_2 in PORTE */

#define DioConf_DIFFERENTIAL_PWM_CHANNEL_NUM            (Dio_ChannelType)5 /* Pin_5 in PORTB */
#define DioConf_DIFFERENTIAL_INT1_CHANNEL_NUM           (Dio_ChannelType)6 /* Pin_6 in PORTB */
#define DioConf_DIFFERENTIAL_INT2_CHANNEL_NUM           (Dio_ChannelType)7 /* Pin_7 in PORTB */

#define DioConf_ENCODER_VELOCITY_A_CHANNEL_NUM          (Dio_ChannelType)2 /* Pin_2 in PORTB */
#define DioConf_ENCODER_VELOCITY_B_CHANNEL_NUM          (Dio_ChannelType)1 /* Pin_1 in PORTB */

#define DioConf_ENCODER_ANGLE_A_CHANNEL_NUM             (Dio_ChannelType)2 /* Pin_2 in PORTD */
#define DioConf_ENCODER_ANGLE_B_CHANNEL_NUM             (Dio_ChannelType)1 /* Pin_1 in PORTD */

#define DioConf_LED1_CHANNEL_NUM                        (Dio_ChannelType)1 /* Pin_1 in PORTF */
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
