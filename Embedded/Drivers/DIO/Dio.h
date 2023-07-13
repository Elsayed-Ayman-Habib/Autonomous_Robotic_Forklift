/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO.h
 *       Module:  DIO
 *
 *  Description:  header file for DIO driver    
 *  
 *********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h" 
#include "Common_Macros.h" 
#include "Dio_Cfg.h"
#include "Port_Regs.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Type definition for Dio_ChannelType */
typedef uint8 Dio_ChannelType ;

/* Type definition for Dio_PortType */
typedef uint8 Dio_PortType ;

/* Type definition for Dio_LevelType */
typedef uint8 Dio_LevelType ;

/* Type definition for Dio_PortLevelType */
typedef uint8 Dio_PortLevelType ;

typedef struct
{
	Dio_PortType Port_Num;
}Dio_ConfigPorts;

typedef struct
{
        Dio_PortType Port_Num;
        Dio_ChannelType Channel_Num ;
	
}Dio_ConfigChannel;

typedef struct Dio_ConfigType
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
	/*Dio_ConfigPorts Ports[DIO_PORTS_IDS];*/
} Dio_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Dio_ConfigType Dio_Configuration;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr);

/* Function prototype of DIO_read_Port_API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function prototype of DIO_write_Port_API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Function prototype of DIO_read_Channel_API */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Function prototype of DIO_write_Channel_API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function prototype of DIO_flip_channel_API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);


#endif  /* DIO.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/