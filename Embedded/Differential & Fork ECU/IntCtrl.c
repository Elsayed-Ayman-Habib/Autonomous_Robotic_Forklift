/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl.c
 *        \brief  Nested Vector Interrupt Driver
 *
 *      \details  Source file for Nested Vector Interrupt Driver 
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl.h"
#include "IntCtrl_Regs.h"
#include "IntCtrl_Cfg.h"
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
STATIC const IntCtrl_ConfigChannel * IntCtrl_Configuration = NULL_PTR;
STATIC uint8 IntCtrl_Status = INTCTRL_NOT_INITIALIZED ;
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
* \Syntax          : void IntCtrl_init(void)        
* \Description     : Function to Init the Nested Vector Interrupt driver                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void IntCtrl_init(const IntCtrl_ConfigType* ConfigPtr)
{
  IntCtrl_InterruptType IntCtl_Number;
  uint32 EnableRegOffset,EnableOffsetBit,PriorityRegOffset,PriorityOffsetBit,PriorityOffsetInterrupt,PriorityRegSelection;
  IntCtrl_Status        = INTCTRL_INITIALIZED;
  IntCtrl_Configuration = ConfigPtr->Interrupt;
  volatile uint32 * IntCtrl_Interrupt_Ptr = (volatile uint32 *)INTCTRL_BASE_ADDRESS;
  
  uint8 i ;

  for( i = 0; i < INTCTRL_CONFIGURED_INTERRUPT ; i++)
  {
    
    IntCtl_Number = IntCtrl_Configuration[i].IntCtrl_Interrupt_Number;
    
    /* 
    *enable the corresponding interrupt 
    */
    EnableRegOffset=(IntCtl_Number/REG_LENGTH_BIT);
    EnableOffsetBit=IntCtl_Number%REG_LENGTH_BIT;
    switch(EnableRegOffset)
    {
    case 0: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN0_BASE_OFFSET),EnableOffsetBit); 
    break;
    case 1: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN1_BASE_OFFSET),EnableOffsetBit); 
    break;
    case 2: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN2_BASE_OFFSET),EnableOffsetBit); 
    break;
    case 3: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN3_BASE_OFFSET),EnableOffsetBit); 
    break;
    case 4: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_EN3_BASE_OFFSET),EnableOffsetBit); 
    break;
    }
    
    /*
    *The APINT register provides priority grouping control for the exception model , This field determines the split of group priority from subpriority 
    */	
    
    if ( (IntCtrl_Configuration[i].group == INTCTRL_GROUP7) && (IntCtrl_Configuration[i].sub_group == INTCTRL_SUBGROUP0) )
    {
      *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_APINT_BASE_OFFSET) = ((((INTCTRL_VALUE_TO_WRITE_NUMBER) << (APINT_VECTKEY_NUM))&((INTCTRL_APINT_VECTKEY_MASK)))+((NVIC_PRIORITY_GROUPS_7_SUB_0) << (APINT_PRIGROUP_NUM))); 
    }
    else if ( (IntCtrl_Configuration[i].group == INTCTRL_GROUP0) && (IntCtrl_Configuration[i].sub_group == INTCTRL_SUBGROUP7) )
    {
      *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_APINT_BASE_OFFSET) = ((((INTCTRL_VALUE_TO_WRITE_NUMBER) << (APINT_VECTKEY_NUM))&((INTCTRL_APINT_VECTKEY_MASK)))+((NVIC_PRIORITY_GROUPS_0_SUB_7) << (APINT_PRIGROUP_NUM))); 
    }
    else if ( (IntCtrl_Configuration[i].group == INTCTRL_GROUP3) && (IntCtrl_Configuration[i].sub_group == INTCTRL_SUBGROUP1) )
    {
      *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_APINT_BASE_OFFSET) = ((((INTCTRL_VALUE_TO_WRITE_NUMBER) << (APINT_VECTKEY_NUM))&((INTCTRL_APINT_VECTKEY_MASK)))+((NVIC_PRIORITY_GROUPS_3_SUB_1) << (APINT_PRIGROUP_NUM))); 
    }
    else if ( (IntCtrl_Configuration[i].group == INTCTRL_GROUP1) && (IntCtrl_Configuration[i].sub_group == INTCTRL_SUBGROUP3) )
    {
      *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_APINT_BASE_OFFSET) = ((((INTCTRL_VALUE_TO_WRITE_NUMBER) << (APINT_VECTKEY_NUM))&((INTCTRL_APINT_VECTKEY_MASK)))+((NVIC_PRIORITY_GROUPS_1_SUB_3) << (APINT_PRIGROUP_NUM))); 
    }
    
    /* 
    *set the priority 
    */
    
    PriorityRegOffset =(IntCtl_Number/REG_LENGTH_BYTE);
    PriorityOffsetBit =(IntCtl_Number%REG_LENGTH_BYTE);
    switch(PriorityRegOffset)
    {
    case 0: PriorityRegSelection = INTCTRL_PRI0_BASE_OFFSET;
    break;
    case 1: PriorityRegSelection = INTCTRL_PRI1_BASE_OFFSET;
    break;
    case 2: PriorityRegSelection = INTCTRL_PRI2_BASE_OFFSET;
    break;
    case 3: PriorityRegSelection = INTCTRL_PRI3_BASE_OFFSET;
    break;
    case 4: PriorityRegSelection = INTCTRL_PRI4_BASE_OFFSET;
    break;
    case 5: PriorityRegSelection = INTCTRL_PRI5_BASE_OFFSET;
    break;
    case 6: PriorityRegSelection = INTCTRL_PRI6_BASE_OFFSET;
    break;
    case 7: PriorityRegSelection = INTCTRL_PRI7_BASE_OFFSET;
    break;
    case 8: PriorityRegSelection = INTCTRL_PRI8_BASE_OFFSET;
    break;
    case 9: PriorityRegSelection = INTCTRL_PRI9_BASE_OFFSET;
    break;
    case 10: PriorityRegSelection = INTCTRL_PRI10_BASE_OFFSET;
    break;
    case 11: PriorityRegSelection = INTCTRL_PRI11_BASE_OFFSET;
    break;
    case 12: PriorityRegSelection = INTCTRL_PRI12_BASE_OFFSET;
    break;
    case 13: PriorityRegSelection = INTCTRL_PRI13_BASE_OFFSET;
    break;
    case 14: PriorityRegSelection = INTCTRL_PRI14_BASE_OFFSET;
    break;
    case 15: PriorityRegSelection = INTCTRL_PRI15_BASE_OFFSET;
    break;
    case 16: PriorityRegSelection = INTCTRL_PRI16_BASE_OFFSET;
    break;
    case 17: PriorityRegSelection = INTCTRL_PRI17_BASE_OFFSET;
    break;
    case 18: PriorityRegSelection = INTCTRL_PRI18_BASE_OFFSET;
    break;
    case 19: PriorityRegSelection = INTCTRL_PRI19_BASE_OFFSET;
    break;
    case 20: PriorityRegSelection = INTCTRL_PRI20_BASE_OFFSET;
    break;
    case 21: PriorityRegSelection = INTCTRL_PRI21_BASE_OFFSET;
    break;
    case 22: PriorityRegSelection = INTCTRL_PRI22_BASE_OFFSET;
    break;
    case 23: PriorityRegSelection = INTCTRL_PRI23_BASE_OFFSET;
    break;
    case 24: PriorityRegSelection = INTCTRL_PRI24_BASE_OFFSET;
    break;
    case 25: PriorityRegSelection = INTCTRL_PRI25_BASE_OFFSET;
    break;
    case 26: PriorityRegSelection = INTCTRL_PRI26_BASE_OFFSET;
    break;
    case 27: PriorityRegSelection = INTCTRL_PRI27_BASE_OFFSET;
    break;
    case 28: PriorityRegSelection = INTCTRL_PRI28_BASE_OFFSET;
    break;
    case 29: PriorityRegSelection = INTCTRL_PRI29_BASE_OFFSET;
    break;
    case 30: PriorityRegSelection = INTCTRL_PRI30_BASE_OFFSET;
    break;
    case 31: PriorityRegSelection = INTCTRL_PRI31_BASE_OFFSET;
    break;
    case 32: PriorityRegSelection = INTCTRL_PRI32_BASE_OFFSET;
    break;
    case 33: PriorityRegSelection = INTCTRL_PRI33_BASE_OFFSET;
    break;
    case 34: PriorityRegSelection = INTCTRL_PRI34_BASE_OFFSET;
    break;
    }
    
    
    switch(PriorityOffsetBit)
    {
    case 0: PriorityOffsetInterrupt =((( INTCTRL_PRIX_BASE_ADDRESS + PriorityRegSelection )&(INTCTRL_PRIX_INTA_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTA_NUM)));
    break;
    case 1: PriorityOffsetInterrupt =((( INTCTRL_PRIX_BASE_ADDRESS + PriorityRegSelection )&(INTCTRL_PRIX_INTB_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTB_NUM)));
    break;
    case 2: PriorityOffsetInterrupt =((( INTCTRL_PRIX_BASE_ADDRESS + PriorityRegSelection )&(INTCTRL_PRIX_INTC_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTC_NUM)));
    break;
    case 3: PriorityOffsetInterrupt =((( INTCTRL_PRIX_BASE_ADDRESS + PriorityRegSelection )&(INTCTRL_PRIX_INTD_MASK))|((IntCtrl_Configuration[i].group) << (PRIX_INTD_NUM)));
    break;
    }
    
    *(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + PriorityRegSelection) = PriorityOffsetInterrupt;
  }
}

/******************************************************************************
* \Syntax          : void Interrupt_Pending(Interrupt_ChannelType Interrupt)        
* \Description     : Function to Init the Nested Vector Interrupt driver                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Interrupt_Pending(Interrupt_ChannelType Interrupt)
{
  IntCtrl_InterruptType IntCtl_Number;
  uint32 PendingRegOffset,PendingOffsetBit;
  volatile uint32 * IntCtrl_Interrupt_Ptr = (volatile uint32 *)INTCTRL_BASE_ADDRESS;
  
  IntCtl_Number = IntCtrl_Configuration[Interrupt].IntCtrl_Interrupt_Number;
  
  PendingRegOffset=(IntCtl_Number/REG_LENGTH_BIT);
  PendingOffsetBit=IntCtl_Number%REG_LENGTH_BIT;
  switch(PendingRegOffset)
  {
  case 0: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PEND0_BASE_OFFSET),PendingOffsetBit); 
  break;
  case 1: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PEND1_BASE_OFFSET),PendingOffsetBit); 
  break;
  case 2: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PEND2_BASE_OFFSET),PendingOffsetBit); 
  break;
  case 3: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PEND3_BASE_OFFSET),PendingOffsetBit); 
  break;
  case 4: SET_BIT(*(volatile uint32 *)((volatile uint8 *)IntCtrl_Interrupt_Ptr + INTCTRL_PEND4_BASE_OFFSET),PendingOffsetBit); 
  break;
  }
}
/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/
