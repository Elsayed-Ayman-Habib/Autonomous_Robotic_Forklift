/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
*        \brief  
*
*      \details  
*
*
*********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Adc.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
*  LOCAL DATA 
*********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL DATA
*********************************************************************************************************************/
STATIC const Adc_ConfigChannel * Adc_Configuration = NULL_PTR;
STATIC uint8 Adc_Status = ADC_NOT_INITIALIZED;
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
void ADC_InitChannel(const Adc_ConfigType * ConfigPtr)
{
  Adc_Status       = ADC_INITIALIZED;
  Adc_Configuration = ConfigPtr->Adc_Channels; /* address of the first Channels structure --> Channels[0] */
  uint8 i;
  for( i = 0; i < ADC_CONFIGURED_CHANNELS; i++)
  {
    volatile uint32 * ADC_Ptr = NULL_PTR; /* point to the required ADC Registers base address */
    volatile uint32 delay = 0;
    
    switch(Adc_Configuration[i].Adc_ChannelId)
    {
    case  0: ADC_Ptr = (volatile uint32 *)ADC0_BASE_ADDRESS; /* ADC0 Base Address */
    break;
    case  1: ADC_Ptr = (volatile uint32 *)ADC1_BASE_ADDRESS; /* ADC1 Base Address */
    break;
    }
    
    switch (Adc_Configuration[i].Adc_ChannelId)
    {
      
      /*
                .o.       oooooooooo.     .oooooo.                 .oooo.   
               .888.      `888'   `Y8b   d8P'  `Y8b               d8P'`Y8b  
              .8"888.      888      888 888                      888    888 
             .8' `888.     888      888 888                      888    888 
            .88ooo8888.    888      888 888                      888    888 
           .8'     `888.   888     d88' `88b    ooo              `88b  d88' 
          o88o     o8888o o888bood8P'    `Y8bood8P'  ooooooooooo  `Y8bd8P'  
                                                        
      */
    case AdcConf_CHANNEL_ADC0_ID :
      /* Enable clock for ADC and allow time for clock to start*/
      SYSCTL_RCGC0_R |= ADC0_ENABLE_CLOCK;
      delay = SYSCTL_RCGC0_R;
      
      /* sets the rate at which ADC0 samples */
      if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_125K )
      {
        SYSCTL_RCGC0_R |= AdcConf0_SAMPLE_RATE_125K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_250K )
      {
        SYSCTL_RCGC0_R |= AdcConf0_SAMPLE_RATE_250K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_500K )
      {
        SYSCTL_RCGC0_R |= AdcConf0_SAMPLE_RATE_500K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_1M )
      {
        SYSCTL_RCGC0_R |= AdcConf0_SAMPLE_RATE_1M;
      }
      else
      {
        /* Do Nothing*/
      }
      
      *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSPRI_REG_OFFSET) = SEQUENSER_PERIORITY;
      if (Adc_Configuration[i].sequencer == SEQUENCER0)
      {
        /* Disable sequencer0 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer0;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS0_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER1)
      {
        /* Disable sequencer1 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer1;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS1_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER2)
      {
        /* Disable sequencer2 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer2;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS2_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER3)
      {
        /* Disable sequencer3 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer3;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS3_Trigger;
        }
        
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSMUX3_REG_OFFSET) = CLEAR_SEQUENCER;
        /* set channel 1, PE2 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSMUX3_REG_OFFSET) += PE2_Ain1;
        
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSCTL3_REG_OFFSET) |= Intetrrupt_State;
     
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= ENABLE_sequencer3;
      }
      break;
      
      /*
                      .o.       oooooooooo.     .oooooo.                 .o  
                     .888.      `888'   `Y8b   d8P'  `Y8b              o888  
                    .8"888.      888      888 888                       888  
                   .8' `888.     888      888 888                       888  
                  .88ooo8888.    888      888 888                       888  
                 .8'     `888.   888     d88' `88b    ooo               888  
                o88o     o8888o o888bood8P'    `Y8bood8P'  ooooooooooo o888o 
      */
      
    case AdcConf_CHANNEL_ADC1_ID:
      /* Enable clock for ADC and allow time for clock to start*/
      SYSCTL_RCGC0_R |= ADC1_ENABLE_CLOCK;
      delay = SYSCTL_RCGC0_R;
      
      /* sets the rate at which ADC0 samples */
      if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_125K )
      {
        SYSCTL_RCGC0_R |= AdcConf1_SAMPLE_RATE_125K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_250K )
      {
        SYSCTL_RCGC0_R |= AdcConf1_SAMPLE_RATE_250K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_500K )
      {
        SYSCTL_RCGC0_R |= AdcConf1_SAMPLE_RATE_500K;
      }
      else if (Adc_Configuration[i].Adc_SampleRate == SAMPLE_RATE_1M )
      {
        SYSCTL_RCGC0_R |= AdcConf1_SAMPLE_RATE_1M;
      }
      else
      {
        /* Do Nothing*/
      }
      
      *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSPRI_REG_OFFSET) |= SEQUENSER_PERIORITY;
      if (Adc_Configuration[i].sequencer == SEQUENCER0)
      {
        /* Disable sequencer0 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer0;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS0_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER1)
      {
        /* Disable sequencer1 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer1;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS1_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER2)
      {
        /* Disable sequencer2 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer2;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS2_Trigger;
        }
      }
      else if (Adc_Configuration[i].sequencer == SEQUENCER3)
      {
        /* Disable sequencer3 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= DISABLE_sequencer3;
        if (Adc_Configuration[i].Adc_TriggerSource == ADC_TRIGG_SRC_SW)
        {
          *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_EMUX_REG_OFFSET) |= SS3_Trigger;
        }
        
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSMUX3_REG_OFFSET) = CLEAR_SEQUENCER;
        /* set channel 1, PE2 */
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSMUX3_REG_OFFSET) += PE2_Ain1;
        
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSCTL3_REG_OFFSET) |= Intetrrupt_State;
        
        *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ACTSS_REG_OFFSET) |= ENABLE_sequencer3;
      }
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
Adc_Samples ADC_GetSamples(Adc_ChannelType Channel)
{
  Adc_Samples sample = 0;
  
  volatile uint32 * ADC_Ptr = NULL_PTR; /* point to the required ADC Registers base address */
  switch(Adc_Configuration[Channel].Adc_ChannelId)
  {
  case  0: ADC_Ptr = (volatile uint32 *)ADC0_BASE_ADDRESS; /* ADC0 Base Address */
  break;
  case  1: ADC_Ptr = (volatile uint32 *)ADC1_BASE_ADDRESS; /* ADC1 Base Address */
  break;
  }
  
  *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_PSSI_REG_OFFSET) |= ADC_SS3_INIT;
  
   while ((*(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_RIS_REG_OFFSET) & ADC_SS3_INIT) == 0);
  //while(GET_BIT(!(*(volatile uint8 *)((volatile uint8 *)ADC_Ptr + ADC_RIS_REG_OFFSET)) , 8 )){}
  sample = *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_SSFIFO3_REG_OFFSET);
  
  *(volatile uint32 *)((volatile uint8 *)ADC_Ptr + ADC_ISC_REG_OFFSET) = CLEAR_sequencer3;
  return sample;
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
float32 ADC_Convert(uint32 adc_sampling, uint32 adc_resolution)
{
	return ((float32)(SYSTEM_VOLTAGE * (float32)(adc_sampling >> adc_resolution)));
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
