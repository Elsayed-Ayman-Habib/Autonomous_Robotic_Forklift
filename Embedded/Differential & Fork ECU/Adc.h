/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "Adc_Cfg.h"
#include "Adc_Regs.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ADC_INITIALIZED                (1U)
#define ADC_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Adc Ch Type */
typedef uint8 Adc_ChannelType;

/* Adc resolution type */
typedef uint8 Adc_ResolutionType;
   
typedef uint32 Adc_Samples;

typedef enum{
  ADC_CONV_MODE_ONESHOT,ADC_CONV_MODE_CONTINUOUS
}Adc_GroupConvModeType;

typedef enum {
      ADC_TRIGG_SRC_SW,ADC_TRIGG_SRC_HW
}Adc_TriggerSourceType;

typedef enum{
 SAMPLE_RATE_125K, 
 SAMPLE_RATE_250K,
 SAMPLE_RATE_500K,
 SAMPLE_RATE_1M
}Adc_SAMPLE_RATE;

typedef enum{
 SEQUENCER0,SEQUENCER1,SEQUENCER2,SEQUENCER3
}Adc_sequencer ;

typedef struct
{
	uint8                  Adc_PortId;           
	Adc_ChannelType        Adc_ChannelId;
	Adc_ResolutionType     Adc_ChannelResolution;
	Adc_SAMPLE_RATE        Adc_SampleRate;
	Adc_TriggerSourceType  Adc_TriggerSource;
    Adc_GroupConvModeType  ModeType;
    Adc_sequencer          sequencer;
}Adc_ConfigChannel;

/* Adc Configuration Type */
typedef struct
{
	Adc_ConfigChannel Adc_Channels[ADC_CONFIGURED_CHANNELS];
}Adc_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* Extern PB configurtion structure to be used by the Adc.c */
extern const Adc_ConfigType Adc_ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void ADC_InitChannel(const Adc_ConfigType * ConfigPtr);

Adc_Samples ADC_GetSamples(Adc_ChannelType Channel);

float32 ADC_Convert(uint32 adc_sampling, uint32 adc_resolution);

#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
