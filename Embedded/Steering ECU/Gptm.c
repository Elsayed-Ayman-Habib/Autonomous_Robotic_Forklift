/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gptm.c
*        \brief  General-Purpose Timer 
*
*      \details  Source file for General-Purpose Timer Driver 
*
*
*********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "Gptm.h"
#include "Gpt_Regs.h"
#include "Gptm_Cfg.h"
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
STATIC const Gpt_ConfigChannel * Gpt_Configuration = NULL_PTR;
STATIC uint8 Gpt_Status = GPTM_NOT_INITIALIZED;

static void (*GptNotification[GPT_CONFIGURED_CHANNLES]) (void);
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
void Gpt_init (const Gpt_ConfigType* ConfigPtr)
{
  Gpt_Status       = GPTM_INITIALIZED;
  
  Gpt_Configuration = ConfigPtr->Gpt_Channels;
  uint8 i ;
  for ( i = 0; i < GPT_CONFIGURED_CHANNLES; i++)
  {
    volatile uint32 * GPTM_Ptr = NULL_PTR;
    
    GptNotification[i]=Gpt_Configuration->GptNotifcation;
    
    switch (Gpt_Configuration[i].GptChannelId)
    {
    case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
    break ;
    case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
    break ;
    case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
    break ;
    case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
    break ;
    case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
    break ;
    case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
    break ;
    case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
    break ;
    case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
    break ;
    case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
    break ;
    case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
    break ;
    case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
    break ;
    case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
    break ;
    case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
    break ;
    case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
    break ;
    case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
    break ;
    case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
    break ;
    case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
    break ;
    case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
    break ;
    case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
    break ;
    case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
    break ;
    case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
    break ;
    case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
    break ;
    case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
    break ;
    case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
    break ; 
    }
    
    
//#if ((GPT_PREDEF_TIMER_1US_16BIT == GPT_DISABLE ) && (GPT_PREDEF_TIMER_1US_24BIT == GPT_DISABLE ) && (GPT_PREDEF_TIMER_1US_32BIT == GPT_DISABLE ) && (GPT_PREDEF_TIMER_100US_32BIT == GPT_DISABLE ))
    
    /* Enable clock for General-Purpose Timer */
    
    if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B))) 
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER5_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B_WIDE))) 
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER5_CLOCK_ENABLE;
    }
    else 
    {
      /* Do Nothing */
    }
    
    
    /* Defined The GPTMCFG values */
#if ( GPTMCFG_VALUE == 1 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_32_BIT_MODE;
#elif ( GPTMCFG_VALUE == 2 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_RTC_COUNTER;
#elif ( GPTMCFG_VALUE == 3 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_16_BIT_MODE;
#endif
    
    
    /* Define The TAMR values */
    if (((Gpt_Configuration[i].GptChannelId)%(2)) == 0)
    {
      /* Make sure that timer A And Timer B is disabled */
      // CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_A);
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TAEN_MASK;
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET)  |= TIMER_A;
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET)  |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = ((Gpt_Configuration[i].GptChannelTickValueMax)*(0xFFFF));
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAPR_BASE_OFFSET)=TIMER_PRESCALER;
    }
    else if (((Gpt_Configuration[i].GptChannelId)%(2)) == 1)
    {
      /* Make sure that timer A And Timer B is disabled */
      //CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_B);
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TBEN_MASK;
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET)  |= TIMER_B;
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET)  |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = ((Gpt_Configuration[i].GptChannelTickValueMax)*(0xFFFF)) ;
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBPR_BASE_OFFSET)=TIMER_PRESCALER;
    }
//#endif
    /////////////////////////////////////////////////////////////////////////////////////
#if ( GPT_PREDEF_TIMER_1US_16BIT == GPT_ENABLE )	
    
    /* Enable clock for General-Purpose Timer */
        if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B))) 
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER5_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B_WIDE))) 
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER5_CLOCK_ENABLE;
    }
    else 
    {
      /* Do Nothing */
    }
    
    
    /* Defined The GPTMCFG values */
#if ( GPTMCFG_VALUE == 3 )
    if ( ((Gpt_Configuration[i].GptChannelId) >= (TIMER0_A)) && ((Gpt_Configuration[i].GptChannelId) >= (TIMER5_B)) )
    {
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_TIMER_16_BIT_MODE;
    }
#endif
    
    
    /* Define The TAMR values */
    if (((Gpt_Configuration[i].GptChannelId)%(2)) == 0)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      //CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_A);
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TAEN_MASK;
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_A;
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
      else 
      {
        /* Do Nothing */
        
      }
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = ((1000000)/(GPT_SYSTEM_CLOCK));
    }
    else if (((Gpt_Configuration[i].GptChannelId)%(2)) == 1)
    {
      /* Make sure that timer A And Timer B is disabled */
      //CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_B);
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TBEN_MASK;
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_B;
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
      else 
      {
        /* Do Nothing */
      }
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = ((1000000)/(GPT_SYSTEM_CLOCK));
    }
    
#endif		 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////	 
#if ( GPT_PREDEF_TIMER_1US_24BIT == GPT_ENABLE )
    
    /* Enable clock for General-Purpose Timer */
       if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B))) 
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER5_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B_WIDE))) 
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER5_CLOCK_ENABLE;
    }
    else 
    {
      /* Do Nothing */
    }
    
    /* Defined The GPTMCFG values */
#if ( GPTMCFG_VALUE == 1 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_32_BIT_MODE;
#elif ( GPTMCFG_VALUE == 2 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_RTC_COUNTER;
#elif ( GPTMCFG_VALUE == 3 )
    if ( ((Gpt_Configuration[i].GptChannelId) >= (TIMER0_A_WIDE)) && ((Gpt_Configuration[i].GptChannelId) >= (TIMER5_B_WIDE)) )
    {
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_16_BIT_MODE;
    }	
#endif
    
    
    /* Define The TAMR values */
    if (((Gpt_Configuration[i].GptChannelId)%(2)) == 0)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_A);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = ((1000000)/(GPT_SYSTEM_CLOCK));
    }
    else if (((Gpt_Configuration[i].GptChannelId)%(2)) == 1)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_B);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = ((1000000)/(GPT_SYSTEM_CLOCK));
    }
    
#endif
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ( GPT_PREDEF_TIMER_1US_32BIT == GPT_ENABLE )
    /* Enable clock for General-Purpose Timer */
    
        if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B))) 
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER5_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B_WIDE))) 
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER5_CLOCK_ENABLE;
    }
    else 
    {
      /* Do Nothing */
    }
    
    /* Defined The GPTMCFG values */
#if ( GPTMCFG_VALUE == 1 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_32_BIT_MODE;
#elif ( GPTMCFG_VALUE == 2 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_RTC_COUNTER;
#elif ( GPTMCFG_VALUE == 3 )
    if ( ((Gpt_Configuration[i].GptChannelId) >= (TIMER0_A_WIDE)) && ((Gpt_Configuration[i].GptChannelId) >= (TIMER5_B_WIDE)) )
    {
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_16_BIT_MODE;
    }	
#endif
    
    
    /* Define The TAMR values */
    if (((Gpt_Configuration[i].GptChannelId)%(2)) == 0)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_A);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = ((10000)/(GPT_SYSTEM_CLOCK));
    }
    else if (((Gpt_Configuration[i].GptChannelId)%(2)) == 1)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_B);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = ((10000)/(GPT_SYSTEM_CLOCK));
    }
    
#endif
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ( GPT_PREDEF_TIMER_100US_32BIT == GPT_ENABLE )
    /* Enable clock for General-Purpose Timer */
    
        if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B)))
    {
      SYSCTL_RCGCTIMER_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B))) 
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B)))
    {	 			 
      SYSCTL_RCGCTIMER_REG |= TIMER5_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER0_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER0_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER0_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER1_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER1_B_WIDE)))
    {
      SYSCTL_RCGCW_REG |= TIMER1_CLOCK_ENABLE;
    } 	
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER2_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER2_B_WIDE))) 
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER2_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER3_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER3_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER3_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER4_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER4_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER4_CLOCK_ENABLE;
    }
    else if (((Gpt_Configuration[i].GptChannelId)==(TIMER5_A_WIDE)) || ((Gpt_Configuration[i].GptChannelId)==(TIMER5_B_WIDE)))
    {	 			 
      SYSCTL_RCGCW_REG |= TIMER5_CLOCK_ENABLE;
    }
    else 
    {
      /* Do Nothing */
    }
    
    /* Defined The GPTMCFG values */
#if ( GPTMCFG_VALUE == 1 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_32_BIT_MODE;
#elif ( GPTMCFG_VALUE == 2 )
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_RTC_COUNTER;
#elif ( GPTMCFG_VALUE == 3 )
    if ( ((Gpt_Configuration[i].GptChannelId) >= (TIMER0_A_WIDE)) && ((Gpt_Configuration[i].GptChannelId) >= (TIMER5_B_WIDE)) )
    {
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCFG_BASE_OFFSET) = TIMER_16_BIT_MODE;
    }	
#endif
    
    
    /* Define The TAMR values */
    if (((Gpt_Configuration[i].GptChannelId)%(2)) == 0)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_A);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = ((10000)/(GPT_SYSTEM_CLOCK));
    }
    else if (((Gpt_Configuration[i].GptChannelId)%(2)) == 1)
    {
      
      /* Make sure that timer A And Timer B is disabled */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) , TIMER_B);
      
      if ( Gpt_Configuration[i].ChannelMode == GPT_ONE_SHOTT )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= ONE_SHOT_TIMER_MODE;
      }
      else if ( Gpt_Configuration[i].ChannelMode == GPT_CONTINUOUS )
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= PERIODIC_TIMER_MODE;
      }
#if ( GPTMCFG_VALUE == 2 )
      
      else if (Gpt_Configuration[i].ChannelMode == GPT_CAPTURE)
      {
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) &= GPT_GPTMTAMR_TAMR_MASK;
        *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= CAPTURE_MODE;
      }
#endif
      else 
      {
        /* Do Nothing */
      }
      
      /* Define the counter direction up or down */
#if ( ENABLE_COUNT_DIRECTION == 0)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_DOWN;
#endif
      
#if ( ENABLE_COUNT_DIRECTION == 1)
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBMR_BASE_OFFSET) |= TIMER_COUNT_UP;
#endif
      
      Gpt_DisableNotification (Gpt_Configuration[i].GptChannelId);
      
      *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = ((10000)/(GPT_SYSTEM_CLOCK));
    }
#endif
  }
}

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
void Gpt_DisableNotification (Gpt_ChannelType Channel)
{
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  
  if (Gpt_Configuration[Channel].Gpt_EnableChannelNotification == INTERRUPT_ON )
  {
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) &= GPT_GPTMIMR_MUSK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) |= GPT_INTERRUPT_DISABLE;
  }
}

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
void Gpt_EnableNotification (Gpt_ChannelType Channel)
{
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  if (Gpt_Configuration[Channel].Gpt_EnableChannelNotification == INTERRUPT_ON )
  {
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) &= GPT_GPTMIMR_MUSK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) |= GPT_INTERRUPT_ENABLE;
  }
}

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
void Gpt_StartTimer (Gpt_ChannelType Channel,Gpt_ValueType Value)
{
  
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  
  if ( ((Gpt_Configuration[Channel].GptChannelId)%(2)) == 0 )
  {
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET) = (uint16)Value; // put the value
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TAEN_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_A_ENABLE;
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &=  GPT_GPTMTAMR_TAMIE_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_A_INTERRUPT;
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) &=  GPT_GPTMIMR_TATOIM_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) |= TIMER_A_ENABLE;
    
  }
  else if ( ((Gpt_Configuration[Channel].GptChannelId)%(2)) == 1 )
  {
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET) = (uint16)Value; // put the value
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TBEN_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_B_ENABLE;
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) &=  GPT_GPTMTAMR_TAMIE_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAMR_BASE_OFFSET) |= TIMER_B_INTERRUPT;
    
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) &=  GPT_GPTMIMR_TBTOIM_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMIMR_BASE_OFFSET) |= TIMER_B_ENABLE;
  }
  Gpt_EnableNotification(Gpt_Configuration[Channel].GptChannelId);
}

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
void Gpt_StopTimer (Gpt_ChannelType Channel)
{
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  
  if ( ((Gpt_Configuration[Channel].GptChannelId)%(2)) == 0 )
  {
    //CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET)  , TIMER_A);
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TAEN_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_A;
  }
  else if ( ((Gpt_Configuration[Channel].GptChannelId)%(2)) == 1 )
  {
    //CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET)  , TIMER_B);
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) &=  GPT_GPTMCTL_TBEN_MASK;
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMCTL_BASE_OFFSET) |= TIMER_B;
  }
  Gpt_DisableNotification(Gpt_Configuration[Channel].GptChannelId);
}

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
Gpt_ValueType Gpt_GetTimerElapsed (Gpt_ChannelType Channel)
{
  uint32 Timer_Value_Elapsed = STD_LOW;
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  if (((Gpt_Configuration[Channel].GptChannelId)%(2)) == 0)
  {
    switch (Gpt_Configuration[Channel].Gpt_ChannelState)
    {
    case INITIALIZED : return 0 ;
    break;
    case RUNNING : Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAR_BASE_OFFSET);
    return Timer_Value_Elapsed;
    break;
    case STOPPED : Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET);
    return Timer_Value_Elapsed;
    break;
    case EXPIRED :
      Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET);
      return Timer_Value_Elapsed;
      break;
    }
  }
  else if (((Gpt_Configuration[Channel].GptChannelId)%(2)) == 1)
  {
    switch (Gpt_Configuration[Channel].Gpt_ChannelState)
    {
    case INITIALIZED : return 0 ;
    break;
    case RUNNING : Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBR_BASE_OFFSET);
    return Timer_Value_Elapsed;
    break;
    case STOPPED : Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET);
    return Timer_Value_Elapsed;
    break;
    case EXPIRED :
      Timer_Value_Elapsed = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET);
      return Timer_Value_Elapsed;
      break;
    }
  }
}

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
Gpt_ValueType Gpt_TimerRemaining (Gpt_ChannelType Channel)
{
  uint32 Timer_Value_Remaining = STD_LOW;
  volatile uint32 * GPTM_Ptr = NULL_PTR;
  switch (Gpt_Configuration[Channel].GptChannelId)
  {
  case  0: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  1: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
  break ;
  case  2: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  3: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  break ;
  case  4: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  5: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  break ;
  case  6: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  7: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_3_BASE_ADDRESS;
  break ;
  case  8: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case  9: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_4_BASE_ADDRESS;
  break ;
  case 10: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 11: GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_5_BASE_ADDRESS;
  break ;
  case 12: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 13: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS;
  break ;
  case 14: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 15: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS;
  break ;
  case 16: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 17: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS;
  break ;
  case 18: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 19: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS;
  break ;
  case 20: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 21: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS;
  break ;
  case 22: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ;
  case 23: GPTM_Ptr = (volatile uint32 *)GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS;
  break ; 
  }
  if (((Gpt_Configuration[Channel].GptChannelId)%(2)) == 0)
  {
    switch (Gpt_Configuration[Channel].Gpt_ChannelState)
    {
    case INITIALIZED : Timer_Value_Remaining = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET);
    return Timer_Value_Remaining;
    break;
    case RUNNING : Timer_Value_Remaining = ((*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAILR_BASE_OFFSET))-(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTAR_BASE_OFFSET)));
    return Timer_Value_Remaining;
    break;
    case STOPPED : return 0;
    break;
    case EXPIRED : return 0;
    break;
    }
  }
  else if (((Gpt_Configuration[Channel].GptChannelId)%(2)) == 1)
  {
    switch (Gpt_Configuration[Channel].Gpt_ChannelState)
    {
    case INITIALIZED : Timer_Value_Remaining = *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET);
    return Timer_Value_Remaining;
    break;
    case RUNNING : Timer_Value_Remaining = ((*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBILR_BASE_OFFSET))-(*(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMTBR_BASE_OFFSET)));
    return Timer_Value_Remaining;
    break;
    case STOPPED : return 0;
    break;
    case EXPIRED : return 0;
    break;
    }
  }
}

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
//void TIMER0A_Handler(void) __attribute__((used));
void TIMER0A_Handler(void)
{
  volatile uint32 * GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_0_BASE_ADDRESS;
 
  if(GptNotification[0] != NULL_PTR)
  {
    /*Call the funciton*/
    //GptNotification[1]();
    (Gpt_Configuration[0].GptNotifcation)();
    /*Clear the flag*/
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMICR_BASE_OFFSET) = Set_BIT;
  }
  else 
  {
    /* Do Noting */
    
  }
  
}

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
//void TIMER1A_Handler(void) __attribute__((used));
void TIMER1A_Handler(void)
{
  volatile uint32 * GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_1_BASE_ADDRESS;
  
  if(GptNotification[2] != NULL_PTR)
  {
    /*Call the funciton*/
    //GptNotification[2]();
    (Gpt_Configuration[2].GptNotifcation)();
    
    /*Clear the flag*/
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMICR_BASE_OFFSET) = Set_BIT;
  }
  else 
  {
    /* Do Noting */
  }
  
}

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
//void TIMER2A_Handler(void) __attribute__((used));
void TIMER2A_Handler(void)
{
  volatile uint32 * GPTM_Ptr = (volatile uint32 *)GPT_16_32_BIT_TIMER_2_BASE_ADDRESS;
  
  if(GptNotification[4] != NULL_PTR)
  {
    /*Call the funciton*/
    //GptNotification[4]();
    (Gpt_Configuration[4].GptNotifcation)();
    /*Clear the flag*/
    *(volatile uint32 *)((volatile uint8 *)GPTM_Ptr + GPT_GPTMICR_BASE_OFFSET) = Set_BIT;
  }
  else 
  {
    /* Do Noting */
  }
  
}

/**********************************************************************************************************************
*  END OF FILE: FileName.c
*********************************************************************************************************************/
