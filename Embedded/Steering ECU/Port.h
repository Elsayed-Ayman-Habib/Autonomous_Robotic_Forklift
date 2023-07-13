/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port.h
 *       Module:  port
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Common_Macros.h"
#include "Port_Cfg.h"
#include "Std_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Type definition for Pin mode */
typedef uint8 Pin_Mode;

/* Type definition for Input Pin Initial value  */
typedef uint8 Pin_InitialValue;

/* Type definition for the symbolic name of a port pin.*/
typedef uint8 Port_PinType;

/* Type definition for Pin Mode */
typedef uint8 Port_PinModeType;

/* Type definition for Input Pin Internal Resistor */
typedef enum{
  OPEN_DRAIN,PULL_UP,PULL_DOWN
}Port_PinInternalAttachType;

typedef enum{
	OUT_CURRENT_NA,OUT_CURRENT_2MA,OUT_CURRENT_4MA,OUT_CURRENT_8MA
}Port_PinOutputCurrentType;

/* Type definition for Pin Direction */
typedef enum{
  PORT_PIN_IN,PORT_PIN_OUT
} Port_PinDirectionType;

typedef struct{
    uint8 port_num;
    uint8 pin_num;
    Port_PinDirectionType direction;
    Port_PinInternalAttachType resistor_state;
    Pin_InitialValue init_Val;
    Pin_Mode mode;      
    Port_PinOutputCurrentType output_current;	
}Port_ConfigChannel;

typedef struct {
	Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_ConfigPtr;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* Function for Port Initialization API */
void Port_Init(const Port_ConfigType * ConfigPtr);
 
#endif  /* PORT.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
