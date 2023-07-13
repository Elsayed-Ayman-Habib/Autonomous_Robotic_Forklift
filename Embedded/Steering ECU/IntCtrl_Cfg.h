/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  Nested Vector Interrupt Configration
 *
 *  Description:  Port Configuration Header file     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define INTCTRL_CONFIGURED_INTERRUPT  (3U)
						
/* Interrupt Group Priority Number */
#define INTCTRL_GROUP0	(0U)
#define INTCTRL_GROUP1	(1U)
#define INTCTRL_GROUP2	(2U)
#define INTCTRL_GROUP3	(3U)
#define INTCTRL_GROUP4	(4U)
#define INTCTRL_GROUP5	(5U)
#define INTCTRL_GROUP6	(6U)
#define INTCTRL_GROUP7	(7U)

/* Interrupt Sub Group Priority Number */
#define INTCTRL_SUBGROUP0	(0U)
#define INTCTRL_SUBGROUP1	(1U)
#define INTCTRL_SUBGROUP2	(2U)
#define INTCTRL_SUBGROUP3	(3U)
#define INTCTRL_SUBGROUP4	(4U)
#define INTCTRL_SUBGROUP5	(5U)
#define INTCTRL_SUBGROUP6	(6U)
#define INTCTRL_SUBGROUP7	(7U)

/* Fixed Group Priority Number */
#define RESET_GROUP_PRIORITY                     (-3)
#define NON_MASKABLE_INTERRUPT_GROUP_PRIORITY    (-2)
#define HARD_FAULT_GROUP_PRIORITY                (-1)

/* Fixed Sub-Group Priority Number */
#define RESET_SUP_GROUP_PRIORITY                     (-3)
#define NON_MASKABLE_INTERRUPT_SUP_GROUP_PRIORITY    (-2)
#define HARD_FAULT_SUP_GROUP_PRIORITY                (-1)

/* Write and Read(VECTKEY)Bits in order to change the bits in this register.*/
#define INTCTRL_VALUE_TO_WRITE_NUMBER  0x05FA
#define INTCTRL_VALUE_TO_READ_NUMBER   0xFA05

/* Shift Bit In Register (VECTKEY) & (PRIGROUP) */
#define APINT_VECTKEY_NUM  (16)
#define APINT_PRIGROUP_NUM  (8)

/* Interrupt Priority Levels Group And Sub-Group */
#define NVIC_PRIORITY_GROUPS_7_SUB_0                     0x4
#define NVIC_PRIORITY_GROUPS_0_SUB_7                     0x7
#define NVIC_PRIORITY_GROUPS_3_SUB_1                     0x5
#define NVIC_PRIORITY_GROUPS_1_SUB_3                     0x6

/* Macros for IntCtrl Status */
#define INTCTRL_INITIALIZED                (1U)
#define INTCTRL_NOT_INITIALIZED            (0U)

#define PRIX_INTA_NUM      (5)
#define PRIX_INTB_NUM      (13)
#define PRIX_INTC_NUM      (21)
#define PRIX_INTD_NUM      (29)

#define REG_LENGTH_BIT   32
#define REG_LENGTH_BYTE  4

/* Enable Exceptions */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions */
#define Disable_Exceptions()   __asm("CPSID I")

/* Enable Faults */
#define Enable_Faults()        __asm("CPSIE F")

/* Disable Faults */
#define Disable_Faults()       __asm("CPSID F") 

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")


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

 
#endif  /* INTCTRL_CFG.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
