/**********************************************************************************************************************
 *
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Encoder.h
 *       Module:  Encoder
 *
 *  Description:  Header File Of the Encoder Driver     
 *  
 *********************************************************************************************************************/
#ifndef ENCODER.H
#define ENCODER.H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "Encoder_Cfg.h"
#include "Std_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ENCODER_INITIALIZED                (1U)
#define ENCODER_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Type definition for Edge */
typedef enum{
  FALLING,RISING
}Edge_Detect;

/* Type definition for Sense */
typedef enum{
  EDGE,LEVEL
}Edge_Sense;

/* Type definition for Deetect Edges */
typedef enum{
  BOTH,SINGLE
}Edge_BothSingle;

typedef enum
{
  INTERRUPT_Off, INTERRUPT_On
} Encoder_InterruptOption;

typedef struct{
        Edge_Detect              Edge;
        Edge_Sense               Sense;   
        Edge_BothSingle          Detect_Edges;
        Encoder_InterruptOption  Encoder_Notification;
}Encoder_ConfigChannel;

typedef struct{
        Edge_Detect              Edge;
        Edge_Sense               Sense;   
        Edge_BothSingle          Detect_Edges;
        Encoder_InterruptOption  Encoder_Notification;
}Encoder_ConfigChanne2;

typedef struct {
	Encoder_ConfigChannel Channels1[ENCODER_CONFIGURED_CHANNLES];
} Encoder_ConfigType1;

 typedef struct {
	Encoder_ConfigChanne2 Channels2[ENCODER_CONFIGURED_CHANNLES];
} Encoder_ConfigType2;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Encoder_ConfigType1 Encoder_ConfigPtr1;

extern const Encoder_ConfigType2 Encoder_ConfigPtr2;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void EncoderChannelA_Init (const Encoder_ConfigType1 * ConfigPtr);

void EncoderChannelB_Init (const Encoder_ConfigType2 * ConfigPtr);

void calc_vel_wheel();

int Encoder_GetPosition(void);
 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
