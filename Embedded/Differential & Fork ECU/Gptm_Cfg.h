/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gptm_Cfg.h
 *       Module:  General-Purpose Timer Module Configration
 *
 *  Description:  General-Purpose Timer Configration Header File    
 *  
 *********************************************************************************************************************/
#ifndef GPTM_CFG.H
#define GPTM_CFG.H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define GPT_CONFIGURED_CHANNLES              (3U)

/* Channel Id of the GPT channel. This value will be assigned to the symbolic name derived of the Gpt_ConfigChannel container short name */
#define TIMER0_A  (0U)
#define TIMER0_B  (1U)
#define TIMER1_A  (2U)
#define TIMER1_B  (3U)
#define TIMER2_A  (4U)
#define TIMER2_B  (5U)
#define TIMER3_A  (6U)
#define TIMER3_B  (7U)
#define TIMER4_A  (8U)
#define TIMER4_B  (9U)
#define TIMER5_A  (10U)
#define TIMER5_B  (11U)
#define TIMER0_A_WIDE  (12U)
#define TIMER0_B_WIDE  (13U)
#define TIMER1_A_WIDE  (14U)
#define TIMER1_B_WIDE  (15U)
#define TIMER2_A_WIDE  (16U)
#define TIMER2_B_WIDE  (17U)
#define TIMER3_A_WIDE  (18U)
#define TIMER3_B_WIDE  (19U)
#define TIMER4_A_WIDE  (20U)
#define TIMER4_B_WIDE  (21U)
#define TIMER5_A_WIDE  (22U)
#define TIMER5_B_WIDE  (23U)

#define TIMER0_CLOCK_ENABLE  0x01
#define TIMER1_CLOCK_ENABLE  0x02
#define TIMER2_CLOCK_ENABLE  0x04
#define TIMER3_CLOCK_ENABLE  0x08
#define TIMER4_CLOCK_ENABLE  0x10
#define TIMER5_CLOCK_ENABLE  0x20

#define ONE_SHOT_TIMER_MODE  0x01
#define PERIODIC_TIMER_MODE  0x02
#define CAPTURE_MODE         0x03

#define GPTMCFG_VALUE 3

#if( GPTMCFG_VALUE == 1)
    #define TIMER_32_BIT_MODE   0x0
#endif

#if ( GPTMCFG_VALUE == 2)
    #define TIMER_RTC_COUNTER  0x1
#endif

#if ( GPTMCFG_VALUE == 3)
    #define TIMER_16_BIT_MODE   0x4
#endif

#define TIMER_A       0x00
#define TIMER_B       0x00
   
#define TIMER_A_ENABLE  0x01
#define TIMER_B_ENABLE  0x80

#define TIMER_A_INTERRUPT       0x20
#define TIMER_B_INTERRUPT       0x20

#define ENABLE_COUNT_DIRECTION  0

#if ( ENABLE_COUNT_DIRECTION == 0)
	#define TIMER_COUNT_DOWN  0X0
#endif

#if ( ENABLE_COUNT_DIRECTION == 1)
	#define TIMER_COUNT_UP 0X10
#endif

#define GPT_ENABLE   1
#define GPT_DISABLE  0

#define GPT_PREDEF_TIMER_1US_16BIT    GPT_DISABLE
#define GPT_PREDEF_TIMER_1US_24BIT    GPT_DISABLE
#define GPT_PREDEF_TIMER_1US_32BIT    GPT_DISABLE
#define GPT_PREDEF_TIMER_100US_32BIT  GPT_DISABLE


#define GPT_INTERRUPT_ENABLE   0xFFFFFFFF
#define GPT_INTERRUPT_DISABLE  0x00000000

#define GPT_SYSTEM_CLOCK		16000000u

#define Clear_BIT               0X00
#define Set_BIT                 0X01

#define TickFrequency           62500ul
#define TickValueMax            50

#define TIMER_PRESCALER    0xFF




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

 
#endif  /* GPTM_CFG.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
