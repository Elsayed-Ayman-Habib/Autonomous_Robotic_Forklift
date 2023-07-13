/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PWM.h
 *       Module:  Pulse Width Modulation (PWM) 
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef PWM_H 
#define PWM_H  
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "PWM_Cfg.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PWM_INITIALIZED                (1U)
#define PWM_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define Memory(X,Y)			 	(*((volatile uint32*)(((uint32)X)+((uint32)Y))))

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/  
typedef uint8 Pwm_ChannelType ;  
typedef float32 Pwm_PeriodType ;   
typedef float32  Pwm_DutyCyle ;  
typedef uint8  Idle_State ;   
typedef uint8 Pwm_Polarity ;  
typedef uint8  Pwm_Module ; 
/**************************** ENUMS ************************************************************************/  
typedef enum { 
  PWM_LOW , PWM_HIGH  

}Pwm_OutputStateType ;   
typedef enum {
PWM_FALLING_EDGE , PWM_RAISING_EDGE , BOTH_EDGES 
}Pwm_EdgeNotificationType ;    
typedef enum {
PWM_VARIABLE_PERIOD , PWM_FIXED_PERIOD , PWM_FIXED_PERIOD_SHIFTED
}Pwm_ChannelClassType ;   
typedef enum {
PWM_SERVICE_ACCEPTED , PWM_NOT_INIT , PWM_SEQUENCE_ERROR , PWM_HW_FAILURE , PWM_POWER_STATE_NOT_SUPP , PWM_TRANS_NOT_POSSIBLE 
}Pwm_PowerStateRequestResultType;   
typedef enum {
NO_POWER , FULL_POWER=255 
}Pwm_PowerStateType ;   
typedef enum {
  sys_clk_div2,
  sys_clk_div4,
  sys_clk_div8,
  sys_clk_div16,
  sys_clk_div32,
  sys_clk_div64 ,
  sys_clk_no_div   
}PWM_DIVISOR; 
typedef uint32 Output_Frequncy  ; 

typedef enum {
DOWN_MODE , UP_MODE  
}PWM_MODE ;    
typedef enum {
 //PWM MODULE 0
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
}pwm_channel ; 
typedef enum { 
PWM_ENABLE_BIT_0  ,   //ENABLE CHANNEL 0 
PWM_ENABLE_BIT_1  ,  //ENABLE CHANNEL 1
PWM_ENABLE_BIT_2  ,   //ENABLE CHANNEL 2
PWM_ENABLE_BIT_3  ,  //ENABLE CHANNEL 3 
PWM_ENABLE_BIT_4 ,   //ENABLE CHANNEL 4
PWM_ENABLE_BIT_5  , //ENABLE CHANNEL 5 
PWM_ENABLE_BIT_6  , //ENABLE CHANNEL 6 
PWM_ENABLE_BIT_7  //ENABLE CHANNEL 7 
} BIT_FIELD_ENABLE;
typedef struct { 
  Pwm_Module Module ;  
  Pwm_ChannelType  channel ;   
  Pwm_DutyCyle  DutyCyle ;      
  Pwm_PeriodType  freq ;  
  PWM_MODE mode ;  
  Pwm_OutputStateType  Output ;        
  PWM_DIVISOR DIV ; 
#if (EXTRA_FEATURES == STD_ON) 
  Pwm_EdgeNotificationType Edge  ;   
  Pwm_ChannelClassType  channel_class ;  
  Idle_State idlestate ;  
#endif 
}Pwm_ConfigChannel ;  
typedef struct {

Pwm_ConfigChannel PWM_Channels [PWM_CONFIGURED_CHANNLES]  ;

}Pwm_ConfigType ;    

extern const Pwm_ConfigType Pwm_ConfigPtr;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/  
void Pwm_Init(const Pwm_ConfigType* ConfigPtr);  
void set_DutyCycle( Pwm_ChannelType channel , float32 DutyCyle , uint8 MODE) ; 
//void setPortPin(uint8  Channel ,  uint8  Module ) ;  
void Clear_DutyCycle( Pwm_ChannelType channel , uint8 MODE);
#endif 
