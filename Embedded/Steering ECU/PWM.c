/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PWM.c
*        \brief  PWM Driver 
*
*      \details  Source file for PWM Driver
*
*
*********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "PWM.h"
#include "PWM_Regs.h"
#include "PWM_Cfg.h"
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
STATIC const Pwm_ConfigChannel* PWM_Configuration = NULL_PTR;
STATIC uint8 PWM_Status = PWM_NOT_INITIALIZED ;  
/****************************** FUNCTIONS ******************************************************/  
void Pwm_Init(const Pwm_ConfigType* ConfigPtr ) {
  uint32 delay =0 ; 
  PWM_Status = PWM_INITIALIZED;  
  PWM_Configuration = ConfigPtr->PWM_Channels;  /* address of the first Module  structure --> Channels[0] */ 
  uint8 i ;
  for ( i = 0; i < PWM_CONFIGURED_CHANNLES; i++)
  {    
    volatile uint32 * Pwm_Ptr = NULL_PTR; /* point to the required PWM Registers base address */
    /*
    * Switch case to determine the Base address of the Port from the attribute port_num in the struct ConfigPtr
    */
    switch(PWM_Configuration[i].Module)
    {
    case  PWM_MODULE0 : Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */
    break;
    case  PWM_MODULE1 : Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
    break;
    }
    SYSCTL_RCGCPWM_REG |= (1<<PWM_Configuration[i].Module); // ENABLE THE GATE OF THE MODULE 
    delay = SYSCTL_RCGCPWM_REG;     //Wait till being enabled
    switch(PWM_Configuration[i].DIV)
    {
    case  sys_clk_no_div  :     
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // DISABLE DIVISOR 
      break; 
    case  sys_clk_div2  :    //ENABLE 2_DIVISOR 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break;   
    case  sys_clk_div4  :    // ENABLE 4_DIVISOR
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break;   
    case  sys_clk_div8 :     //ENABLE 8_DIVISOR 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break;    
    case  sys_clk_div16 :     //ENABLE 16_DIVISOR 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break; 
    case  sys_clk_div32  :   //ENABLE 32_DIVISOR
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      CLEAR_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break;   
    case  sys_clk_div64  :     //ENABLE 64_DIVISOR 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_BIT  )   ; // ENABLE DIVISOR   
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_LEAST  ) ; 
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_MED  )  ;
      SET_BIT(SYSCTL_RCGCPWM_REG  , DIV_HIGHEST  );
      break;  
    }
    
    /*********************************** looping the channels *********************************************/ 
    switch(PWM_Configuration[i].channel) {     
      /********************************** FIRST CHANNEL *****************************************************/ 
    case PWM0_PB6  :   // FIRST CHANNEL  MODULE 0 GEN 0   A DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENA_OFFSET)) = VAL_DCOUNTING_A ; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq); 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */ 
        
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      
      break;   
      
      /****************************** SECOND CHANNEL ************************************************/    
    case PWM0_PB7 :   // SECOND CHANNEL MODULE 0 GEN 0  B  DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_1) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq); 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_1) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */ 
        
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break;  
      /******************************************* THIRD CHANNEL ***********************************/   
    case PWM0_PB4:    // THIRD CHANNEL MODULE 0 GEN 1 A     DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq); 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))=((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break;  
      /***************************************** FOURTH CHANNEL *************************************************/    
    case PWM0_PB5 :   // FOURTH CHANNEL MODULE 0 GEN 1 B   DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */
        /*
        * a7na elmafrod n8yer e type cast batt3 el volatile men float32 l uint32 
        * 
        */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break;    
      /************************************************* FIFTH CHANNEL *****************************************/ 
    case PWM0_PE4 :     // MODULE 0  GEN 2 A DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))=(PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= (1.0-(PWM_Configuration[i].DutyCyle/100.0))*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } break;   
      /*********************************************************SIXTH CHANNEL *********************************************/    
    case PWM0_PE5 :     // MODULE 0 GEN 2 B DONE
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENB_OFFSET) = VAL_DCOUNTING_B); /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ;
      }
      break;  
      /****************************************** SEVENTH CHANNEL ***********************************************/     
    case PWM0_PC4 :   // MODULE 0 GEN 3 A
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break;  
      
      /************************************************ EIGHTH CHANNEL *************************************************/     
    case PWM0_PC5 :  // MODULE 0 GEN 3  B
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break; 
      /************************************************  FIRST CHANNEL Module 1 ************************************/     
    case PWM1_PD0 : 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {    // CONFIGURE UP_MODE 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */ 
        
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      
      break; 
      /************************************************  SECOND  CHANNEL Module 1 ************************************/     
    case PWM1_PD1 :     // DONE 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_1) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_1) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */ 
        
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator0) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_0) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      
      break;   
      /*************************************** THIRD CHANNEL MODULE 1 *********************************************/    
    case PWM1_PA6 :      // MODULE 1  GEN 1 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENA_OFFSET) = VAL_DCOUNTING_A); /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_2) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      
      break;   
      /***************************************** FOURTH CHANNEL MODULE 1 *************************************/     
    case PWM1_PA7 :   //MODULE 1 GEN 1 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator1) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_3) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break;   
      /****************************************** FIFTH CHANNEL MODULE 1  ********************************************/    
    case PWM1_PF0 : 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_4) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }  break;  
      /***************************************** SIXTH CHANNEL MODULE 1  *********************************/  
    case PWM1_PF1 : 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator2) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_5) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CTL_OFFSET),PWM_ENABLE_BIT_0) ;
      }  break; 
      /***********************************************  SEVENTH CHANNEL MODULE 1 **********************************************/    
    case  PWM1_PF2 :
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENA_OFFSET)) = VAL_DCOUNTING_A; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */  
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENA_OFFSET)) = 0x00000023; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_6) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }break;  
      /********************************************** EIGHTH CHANNEL MODULE  1 **********************************************/    
    case PWM1_PF3 : 
      SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;    // DIASBLE OUTPUT IN INITIALIZIATION 
      CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      if(PWM_Configuration[i].mode == DOWN_MODE)  {     // configure down mode 
        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENB_OFFSET)) = VAL_DCOUNTING_B; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/PWM_Configuration[i].freq);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(1.0-PWM_Configuration[i].DutyCyle)) ;   /* set duty cyle */ 
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      } 
      else {
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),BIT_MODE) ;  /* select down count mode of counter 0*/ 
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3GENB_OFFSET)) = 0x00000203; /* Set PWM outpu1 when counter reloaded and clear when matches PWMCMPA */  
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(PWM_Configuration[i].freq));    /* set load value  */
        (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= (PWM_Configuration[i].DutyCyle/100.0)*(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_CTL_OFFSET),PWM_Generator3) ;  // ENABLE GENERATOR 
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM_OUTPUT_ENABLE_OFFSET )  , PWM_ENABLE_BIT_7) ;   
        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CTL_OFFSET),PWM_ENABLE_BIT_0) ; 
      }
      break; 
    }
  } 
}
void set_DutyCycle( Pwm_ChannelType channel , float32 DutyCyle , uint8 MODE)  { 
  volatile uint32 * Pwm_Ptr = NULL_PTR ; /* point to the required PWM Registers base address */
  switch(channel) {  
    //MODULE 0 
  case PWM0_PB6 : 
    if(MODE == DOWN_MODE) {
      /*
      * da el sa7 zabt elba2y 3aleh
      */
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(DutyCyle)) ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB7  :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      if (DutyCyle == Duty0)
      {
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= 0x8EC ;
      } 
      else 
      {
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(1.0-DutyCyle)) ;
      }
    }
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PE4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
     if (DutyCyle == Duty0)
      {
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= 0x8EC ; 
      } 
      else 
      {
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
        (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(1.0-DutyCyle)) ; 
      }
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PE5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PC4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PC5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;   
    
    // MODULE 1 
  case PWM1_PD0 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM1_PD1 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM1_PA6:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(DutyCyle))-1.0 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }     
    break ;  
  case PWM1_PA7:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))*(DutyCyle))-1.0 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;   
  case PWM1_PF0:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(DutyCyle))-1.0 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ; 
  case PWM1_PF1:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))*(DutyCyle))-1.0 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }      
    break ;
  case PWM1_PF2:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(DutyCyle))-1.0 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;
  case PWM1_PF3:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz);    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))*(DutyCyle))-1.0 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;
  }
} 
/*PWM MODULE 0
PWM0_PB6,//G0/pin0
PWM0_PB7,//G0/pin1
PWM0_PB4,//G1/pin0
PWM0_PB5,//G1/pin1
PWM0_PE4,//G2/pin0
PWM0_PE5,//G2/pin1
PWM0_PC4,//G3/pin0
PWM0_PC5,//G3/pin1
//PWM MODULE 1
PWM1_PD0,//G0/pin0
PWM1_PD1,//G0/pin01
PWM1_PA6,//G1/pin0
PWM1_PA7,//G1/pin1
PWM1_PF0,//G2/pin0
PWM1_PF1,//G2/pin1
PWM1_PF2,//G3/pin0
PWM1_PF3 //G3/pin1 
 case  PWM_MODULE0 : Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address 
break;
    case  PWM_MODULE1 : Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address 
*/
void Clear_DutyCycle( Pwm_ChannelType channel , uint8 MODE)  { 
  uint8 DutyCyle = 0;
  volatile uint32 * Pwm_Ptr = NULL_PTR ; /* point to the required PWM Registers base address */
  switch(channel) {  
    //MODULE 0 
  case PWM0_PB6 : 
    if(MODE == DOWN_MODE) {
      /*
      * da el sa7 zabt elba2y 3aleh
      */
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB7  :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PB5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PE4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PE5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PC4 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM0_PC5 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_0_BASE_ADDRESS ; /* PWM_0 Base Address */  
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;   
    
    // MODULE 1 
  case PWM1_PD0 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM1_PD1 :   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= 0x0000 ; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM0LOAD_OFFSET)) ;   /* set duty cyle */
    }
    break ;  
  case PWM1_PA6:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= 0x0000; 
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    }     
    break ;  
  case PWM1_PA7:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= 0x0000;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM1LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;   
  case PWM1_PF0:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= 0x0000 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ; 
  case PWM1_PF1:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= 0x0000 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM2LOAD_OFFSET)) ;   /* set duty cyle */
    }      
    break ;
  case PWM1_PF2:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= 0x0000 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPA_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;
  case PWM1_PF3:   
    if(MODE == DOWN_MODE) {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= (PWM_SYSTEM_CLOCK/Freq_7Khz)*0;    /* set load value  */
      (*(volatile uint32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= 0x0000 ;
    } 
    else {
      Pwm_Ptr = (volatile uint32 *)PWM_MODULE_1_BASE_ADDRESS ; /* PWM_1 Base Address */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET))= ((16000000.0)/(Freq_7Khz));    /* set load value  */
      (*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3CMPB_OFFSET))= ((100.0-DutyCyle)/100.0)*(*(volatile float32 *)((volatile uint8 *)Pwm_Ptr + PWM3LOAD_OFFSET)) ;   /* set duty cyle */
    } 
    break ;
  }
} 
