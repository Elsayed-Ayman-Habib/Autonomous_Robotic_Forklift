/**********************************************************************************************************************
 *
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PWM_Regs.h
 *       Module:  Pulse width modulation  Driver 
 *
 *  Description: Pulse width modulation Driver Registers     
 *  
 *********************************************************************************************************************/
#ifndef PWM_REGS_H
#define PWM_REGS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ******************************************************  MODULES BASE ADDRESS ***************************************************************/ 
#define PWM_MODULE_0_BASE_ADDRESS  0x40028000 
#define PWM_MODULE_1_BASE_ADDRESS  0x40029000 
/****************************************** REG OFFSET  ***********************************************/     
#define PWM_CTL_OFFSET                  0x000 
#define PWM_OUTPUT_ENABLE_OFFSET        0x008
#define PWM0CTL_OFFSET                  0x040
#define PWM1CTL_OFFSET                  0x080
#define PWM2CTL_OFFSET                  0x0C0 
#define PWM3CTL_OFFSET                  0x100 
#define PWM0LOAD_OFFSET                 0x050 
#define PWM1LOAD_OFFSET                 0x090
#define PWM2LOAD_OFFSET                 0x0D0
#define PWM3LOAD_OFFSET                 0x110
#define PWM0CMPA_OFFSET                 0x058   
#define PWM1CMPA_OFFSET                 0x098
#define PWM2CMPA_OFFSET                 0x0D8    
#define PWM3CMPA_OFFSET                 0x118
#define PWM0CMPB_OFFSET                 0x05C   
#define PWM1CMPB_OFFSET                 0x09C
#define PWM2CMPB_OFFSET                 0x0DC    
#define PWM3CMPB_OFFSET                 0x11C   
#define PWM0GENA_OFFSET                 0x060
#define PWM1GENA_OFFSET                 0x0A0 
#define PWM2GENA_OFFSET                 0x0E0
#define PWM3GENA_OFFSET                 0x120  
#define PWM0GENB_OFFSET                 0x064
#define PWM1GENB_OFFSET                 0x0A4 
#define PWM2GENB_OFFSET                 0x0E4
#define PWM3GENB_OFFSET                 0x124     
   
#define SYSCTL_RCC_R              (*((volatile uint32 *)0x400FE060)
#define SYSCTL_RCGCPWM_REG        (*((volatile uint32 *)0x400FE640))


#endif /*PWM_REGS.H*/ 