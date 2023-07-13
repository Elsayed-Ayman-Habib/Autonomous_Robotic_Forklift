/**********************************************************************************************************************

*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*         File:  <Write File Name>
*       Module:  -
*
*  Description:  <Write File DESCRIPTION here>     
*  
*********************************************************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/


/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/
/* Adc priority specification */
#define ADC_PRIORITY_IMPLEMENTATION          (ADC_PRIORITY_NONE)

/* Adc group access mode type */
#define ADC_GROUP_ACCCESS_MODE               (ADC_ACCESS_MODE_SINGLE)

/* Adc group conversion mode */
#define ADC_GROUP_CONVERSION_MODE            (ADC_CONV_MODE_CONTINUOUS)

/* Adc group Id */
#define ADC_GROUP_ID                         ((Adc_GroupType)0U)

/* Number of configured Adc channels */

/* Adc configured channel */
#define AdcConf_CHANNEL_ADC0_ID                   (0) 

#define AdcConf_CHANNEL_ADC1_ID                   ((Adc_ChannelType)1) 

/* Adc resolution number */
/* for 12-bit conversion */
#define AdcConf_RESOLUTION                   ((Adc_ResolutionType)12U)    

/* Adc sample rate, 125K sample/sec The number is uC specific */
#define AdcConf0_SAMPLE_RATE_125K                 ((uint32)0x00000000U)

/* Adc sample rate, 250K sample/sec The number is uC specific */
#define AdcConf0_SAMPLE_RATE_250K                 ((uint32)0x00000100U)

/* Adc sample rate, 500K sample/sec The number is uC specific */
#define AdcConf0_SAMPLE_RATE_500K                 ((uint32)0x00000200U)

/* Adc sample rate, 1M sample/sec The number is uC specific */
#define AdcConf0_SAMPLE_RATE_1M                   ((uint32)0x00000300U)

/* Adc sample rate, 125K sample/sec The number is uC specific */
#define AdcConf1_SAMPLE_RATE_125K                 ((uint32)0x00000000U)

/* Adc sample rate, 250K sample/sec The number is uC specific */
#define AdcConf1_SAMPLE_RATE_250K                 ((uint32)0x00000400U)

/* Adc sample rate, 500K sample/sec The number is uC specific */
#define AdcConf1_SAMPLE_RATE_500K                 ((uint32)0x00000800U)

/* Adc sample rate, 1M sample/sec The number is uC specific */
#define AdcConf1_SAMPLE_RATE_1M                   ((uint32)0x00000C00U)

#define ADC0_ENABLE_CLOCK                    0x00010000
#define ADC1_ENABLE_CLOCK                    0x00020000

#define ADC_CONFIGURED_CHANNELS              (1U)

/* Adc configured ports Id */
/* PORTA */
#define PORT_PortA                            (0U)

/* PORTB */
#define AdcConf_PORTB_ID                      (1U) 

/* PORTC */
#define PORT_PortC                            (2U)

/* PORTD */   
#define AdcConf_PORTD_ID                      (3U) 

/* PORTE */
#define AdcConf_PORTE_ID                      (4U) 

/* PORTF */
#define PORT_PortF                            (5U)

#define ENABLE_sequencer0     0x1
#define DISABLE_sequencer0    0x0

#define ENABLE_sequencer1     0x2
#define DISABLE_sequencer1    0x0

#define ENABLE_sequencer2     0x4
#define DISABLE_sequencer2    0x0
 
#define ENABLE_sequencer3     0x8
#define DISABLE_sequencer3    0x0

#define CLEAR_sequencer3      0x8

#define SS3_Trigger 0xF000

#define SS2_Trigger 0x0F00

#define SS1_Trigger 0x00F0

#define SS0_Trigger 0x000F

#define CLEAR_SEQUENCER 0x0

/* configure END0 and IE0 */
#define Intetrrupt_State  0x6

/* set channel */
#define PB4_Ain10    10
#define PB5_Ain11    11
#define PD0_Ain7     7
#define PD1_Ain6     6
#define PD2_Ain5     5
#define PD3_Ain4     4
#define PE0_Ain3     3
#define PE1_Ain2     2
#define PE2_Ain1     1
#define PE3_Ain0     0
#define PE4_Ain9     9
#define PE5_Ain8     8

/*
 * set periority of Sequenser 3 highest periority 
 * set SSO = 0x3 
 * set SS1 = 0x2
 * set SS2 = 0x1
 * set SS3 = 0x0
 * that mean Sequenser 3 is the highest periorty because 0x0 is highest
 */
#define SEQUENSER_PERIORITY 0x123

#define ADC_SS3_INIT  0x08

#define SYSTEM_VOLTAGE  (3.3F)
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

 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
