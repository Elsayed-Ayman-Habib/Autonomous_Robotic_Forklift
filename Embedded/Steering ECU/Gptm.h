/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gptm.h
 *       Module:  General-Purpose Timer Module (GPTM)
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef GPTM_H
#define GPTM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "Gptm_Cfg.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define GPTM_INITIALIZED                (1U)
#define GPTM_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum{
  GPT_MODE_NORMAL,GPT_MODE_SLEEP
}Gpt_ModeType;

typedef enum
{
  INITIALIZED, RUNNING, STOPPED, EXPIRED
} Gpt_StateType;

typedef enum
{
  GPT_CONTINUOUS,GPT_ONE_SHOTT,GPT_CAPTURE
} Gpt_RunningMode;

typedef enum
{
  INTERRUPT_OFF, INTERRUPT_ON
} Gpt_InterruptOption;


typedef struct{ 
  Gpt_ChannelType      GptChannelId;
  Gpt_ModeType         Gpt_ChannelMode;
  Gpt_StateType        Gpt_ChannelState;
  Gpt_ValueType        GptChannelTickFrequency;
  Gpt_ValueType        GptChannelTickValueMax;
  Gpt_InterruptOption  Gpt_EnableChannelNotification;
  Gpt_RunningMode      ChannelMode;
  void 		       (*GptNotifcation)(void);
}Gpt_ConfigChannel;

typedef struct{
  Gpt_ConfigChannel Gpt_Channels[GPT_CONFIGURED_CHANNLES];
}Gpt_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Gpt_ConfigType Gpt_ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Gpt_init (const Gpt_ConfigType* ConfigPtr);

void Gpt_DisableNotification (Gpt_ChannelType Channel);

void Gpt_EnableNotification (Gpt_ChannelType Channel);

void Gpt_StartTimer (Gpt_ChannelType Channel,Gpt_ValueType Value);

void Gpt_StopTimer (Gpt_ChannelType Channel);

Gpt_ValueType Gpt_GetTimerElapsed (Gpt_ChannelType Channel);
 
Gpt_ValueType Gpt_TimerRemaining (Gpt_ChannelType Channel);


#endif  /* GPTM.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
