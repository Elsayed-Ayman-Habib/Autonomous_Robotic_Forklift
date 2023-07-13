/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PWM_CFG.H
 *       Module:  Pulse Width Modulation Module Configration
 *
 *  Description:  Pulse Width Modulation Configration Header File    
 *  
 *********************************************************************************************************************/
#ifndef PWM_CFG_H
#define PWM_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PWM_CONFIGURED_CHANNLES              (1U)
#define EXTRA_FEATURES       STD_OFF
/* Channel Id of the PWM channel and Modules , Generators . This value will be assigned to the symbolic name derived of the PWM_ConfigChannel container short name */ 
/* Modules Defines */   
#define  PWM_MODULE0   0
#define  PWM_MODULE1   1  
/* Generators Defines */  
#define PWM_Generator0   0
#define PWM_Generator1   1 
#define PWM_Generator2   2
#define PWM_Generator3   3  
/* Channels IDs */   
#define PWM_CHANNEL_0A    1  
#define PWM_CHANNEL_0B    2 
#define PWM_CHANNEL_1A    3  
#define PWM_CHANNEL_1B    4 
#define PWM_CHANNEL_2A    5 
#define PWM_CHANNEL_2B    6 
#define PWM_CHANNEL_3A    7 
#define PWM_CHANNEL_3B    8 
/* Duty cycles percentage */ 
#define full_Duty 100.0
#define Duty0     0.0 
#define Duty10    0.1 
#define Duty17    0.17
#define Duty18    0.18
#define Duty15    0.15
#define Duty20    0.2 
#define Duty25    0.25 
#define Duty30    0.3
#define Duty35    0.35
#define Duty40    0.4
#define Duty50    0.5
#define Duty60    0.6
#define Duty70    0.7
#define Duty75    0.75
#define Duty80    0.8
#define Duty82    0.82
#define Duty83    0.83
#define Duty85    0.85
#define Duty90    0.9
#define Duty100   1.0 
/*******************************************************************/  
#define LOW  0 
#define HIGH 1
#define SYSTEM_CLOCK		16000000UL
#define DIV_BIT    20
#define DIV_LEAST  17 
#define DIV_MED    18 
#define DIV_HIGHEST 19 
#define BIT_MODE    1 
#define VAL_DCOUNTING_A 0x0000008C  
#define VAL_DCOUNTING_B 0x0000080C   
#define Freq_1Khz   1000.0  
#define Freq_7Khz   7000.0
#define Freq_5Khz   5000.0 
#define Freq_2Khz   2000.0 
#define Freq_10Khz  10000.0 
#define Freq_8Khz   8000.0 
#define PWM_SYSTEM_CLOCK	16000000.0

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

 
#endif  /* PWM_CFG.H*/

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
