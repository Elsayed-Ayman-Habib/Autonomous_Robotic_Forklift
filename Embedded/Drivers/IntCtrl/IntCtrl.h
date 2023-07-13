/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl.h
 *       Module:  Nested Vector Interrupt Driver
 *
 *  Description:  The Configure Of All MCU interrupts Priority into gorups and subgroups
 *                and Enable NVIC Interrupt Gate for Peripherals     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_H
#define INTCTRL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "IntCtrl_Cfg.h"
#include "Std_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 Interrupt_ChannelType;
   
typedef uint32 InterruptPeripheralGates ;

typedef uint8 InterruptGroupPriority ;

typedef uint8 InterruptSub_GroupPriority ;

typedef enum
{
	NVIC_GPIO_PortA							,		/* 0 */
	NVIC_GPIO_PortB							,		/* 1 */
	NVIC_GPIO_PortC							,		/* 2 */
	NVIC_GPIO_PortD							,		/* 3 */
	NVIC_GPIO_PortE							,		/* 4 */
	
	NVIC_UART_0									,		/* 5 */
	NVIC_UART_1									,		/* 6 */
	
	NVIC_SSI_0									,		/* 7 */
	NVIC_I2C_0									,		/* 8 */
	
	NVIC_PWM0_Fault							,		/* 9 */
	NVIC_PWM0_Gen_0							,		/*10 */
	NVIC_PWM0_Gen_1							,		/*11 */
	NVIC_PWM0_Gen_2							,		/*12 */
	
	NVIC_QEI_0  								,		/*13 */
	
	NVIC_ADC0_Sequence_0				,		/*14 */
	NVIC_ADC0_Sequence_1				,		/*15 */
	NVIC_ADC0_Sequence_2				,		/*16 */
	NVIC_ADC0_Sequence_3				,		/*17 */
	
	NVIC_Watchdog								,		/*18 */
	
	NVIC_16_32_Bit_Timer_0_A		,		/*19 */
	NVIC_16_32_Bit_Timer_0_B		,		/*20 */
	NVIC_16_32_Bit_Timer_1_A		,		/*21 */
	NVIC_16_32_Bit_Timer_1_B		,		/*22 */
	NVIC_16_32_Bit_Timer_2_A		,		/*23 */
	NVIC_16_32_Bit_Timer_2_B		,		/*24 */
	
	NVIC_Analog_Comparator_0		,		/*25 */
	NVIC_Analog_Comparator_1		,		/*26 */
	NVIC_Analog_Comparator_2		,		/*27 */
	
	NVIC_System_Control					,		/*28 */
	NVIC_Flash_COntrol					,		/*29 */
	
	NVIC_GPIO_PortF							,		/*30 */
	NVIC_GPIO_PortG							,		/*31 */
	NVIC_GPIO_PortH							,		/*32 */
	
	NVIC_UART_2									,		/*33 */
	NVIC_SSI_1									,		/*34 */
	
	NVIC_Timer_3_A							,		/*35 */
	NVIC_Timer_3_B							,		/*36 */
	
	NVIC_I2C_1									,		/*37 */
	NVIC_QEI_1									,		/*38 */
	
	NVIC_CAN_0									,		/*39 */
	NVIC_CAN_1									,		/*40 */
	NVIC_CAN_2									,		/*41 */
	
	NVIC_Ethernet								,		/*42 */
	NVIC_Hibernate							,		/*43 */
	NVIC_USB0										,		/*44 */
	NVIC_PWM_Generator_3			  ,		/*45 */
	NVIC_uDMA_Software					,		/*46 */
	NVIC_uDMA_Error							,		/*47 */
	
	NVIC_ADC1_Sequence_0				,		/*48 */
	NVIC_ADC1_Sequence_1				,		/*49 */
	NVIC_ADC1_Sequence_2				,		/*50 */
	NVIC_ADC1_Sequence_3				,		/*51 */
	
	/*-----------52-56 Reserved----------*/																
													
	NVIC_SSI_2=57 							,		/*57 */
	NVIC_SSI_3									,		/*58 */
	NVIC_UART_3									,		/*59 */
	NVIC_UART_4									,		/*60 */
	NVIC_UART_5									,		/*61 */
	NVIC_UART_6									,		/*62 */
	NVIC_UART_7									,		/*63 */
	
	/*-----------64-67 Reserved----------*/
	
	NVIC_I2C_2=68								,		/*68 */
	NVIC_I2C_3									,		/*69 */
	NVIC_16_32_Bit_Timer_4_A		,		/*70 */
	NVIC_16_32_Bit_Timer_4_B		,		/*70 */
	
	/*-----------71-92 Reserved----------*/
	
	NVIC_16_32_Bit_Timer_5_A=92	,		/*92 */
	NVIC_16_32_Bit_Timer_5_B		,		/*93 */
	NVIC_32_64_Bit_Timer_0_A		,		/*94 */
	NVIC_32_64_Bit_Timer_0_B		,		/*95 */
	NVIC_32_64_Bit_Timer_1_A		,		/*96 */
	NVIC_32_64_Bit_Timer_1_B		,		/*97 */
	NVIC_32_64_Bit_Timer_2_A		,		/*98 */
	NVIC_32_64_Bit_Timer_2_B		,		/*99 */
	NVIC_32_64_Bit_Timer_3_A		,		/*100*/
	NVIC_32_64_Bit_Timer_3_B		,		/*101*/
	NVIC_32_64_Bit_Timer_4_A		,		/*102*/
	NVIC_32_64_Bit_Timer_4_B		,		/*103*/
	NVIC_32_64_Bit_Timer_5_A		,		/*104*/
	NVIC_32_64_Bit_Timer_5_B		,		/*105*/
	NVIC_SYSTEM_Exception				,		/*106*/
	
	/*----------107-133 Reserved---------*/	
	
	NVIC_PWM1_Generator_0=134		,		/*134*/
	NVIC_PWM1_Generator_1				,		/*135*/
	NVIC_PWM1_Generator_2				,		/*136*/
	NVIC_PWM1_Generator_3				,		/*137*/
	NVIC_PWM1_Fault							,		/*138*/
}IntCtrl_InterruptType;

typedef struct{
	IntCtrl_InterruptType IntCtrl_Interrupt_Number;
	InterruptGroupPriority group;
	InterruptSub_GroupPriority sub_group;
}IntCtrl_ConfigChannel;

typedef struct
{
	IntCtrl_ConfigChannel Interrupt[INTCTRL_CONFIGURED_INTERRUPT];
}IntCtrl_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const IntCtrl_ConfigType IntCtrl_ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void IntCtrl_init(const IntCtrl_ConfigType* ConfigPtr);

void Interrupt_Pending(Interrupt_ChannelType Interrupt);
 
#endif  /* INTCTRL.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
