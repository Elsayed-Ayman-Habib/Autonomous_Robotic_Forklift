/**********************************************************************************************************************

*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*         File:  <Write File Name>
*       Module:  -
*
*  Description:  <Write File DESCRIPTION here>     
*  
*********************************************************************************************************************/
#ifndef UART_H
#define UART_H

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Uart_Cfg.h"
#include "Common_Macros.h"
/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/
#define UART_INITIALIZED                (1U)
#define UART_NOT_INITIALIZED            (0U)

#define BUFFER_SIZE_1 11
#define BUFFER_SIZE_2 6
/**********************************************************************************************************************
*  GLOBAL FUNCTION MACROS
*********************************************************************************************************************/
/*
 * ESP -> TIVA
 */
char receive_buffer_1[BUFFER_SIZE_1]; // Initialize the receive buffer and index
char incoming_1 ;
char value_string_1[11] ;
int Integer_Part_esp_1 ;
float Fractional_part_esp_1 ;
int Integer_Fractional_part_esp_1;
int Integer_Part_esp_2 ;
float Fractional_part_esp_2 ;
int Integer_Fractional_part_esp_2;
extern float Number_esp_1;
extern float Number_esp_2;
/**********************************************************************************************************************
*  GLOBAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/
typedef uint8 Uart_Channel;

typedef uint32 Uart_BoudRate;

typedef uint8 Uart_DataLength;

typedef enum 
{
  PARITY,NO_PARITY
}Uart_PartityState;

typedef enum 
{
  TRANSMIT, RECEIVE
}Uart_State;
  
typedef enum
{
  Turn_INTERRUPT_OFF, Turn_INTERRUPT_ON
} Uart_InterruptOption;

typedef struct{
  Uart_Channel         Channel;
  Uart_BoudRate        Boud_Rate;
  Uart_PartityState    Partity_State;
  Uart_DataLength      Data_Length;
  Uart_State           State;
  Uart_InterruptOption Interrupt_State;
}Uart_ConfigChannel;

typedef struct {
  Uart_ConfigChannel Channels[UART_CONFIGURED_CHANNLES];
} Uart_ConfigType;

/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/
extern const Uart_ConfigType Uart_ConfigPtr;
extern uint8 RECEIVED_DATA ; 
extern uint8 TRANSMIT_DATA ; 
/**********************************************************************************************************************
*  GLOBAL FUNCTION PROTOTYPES
*********************************************************************************************************************/
void Uart_init(const Uart_ConfigType * ConfigPtr);   

char Uart_RX (Uart_Channel UART_ID) ;

void Uart_TX (Uart_Channel UART_ID , uint8 TRANS_DATA);

void Send_String(Uart_Channel UART_ID  , char *str);

void parse_message(char* message , char* dst);

int combineCharsToInt(char highByte, char lowByte);

float intToFloat(char sign , int wholeNum, int fracNum);

void Clear_Uart_Bus(Uart_Channel UART_ID );

void uart_receive_string_esp(char *receive_buffer_1, char* value_string_1);

void Float_to_chars_esp(float num1 , float num2 , char* str);


#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
*  END OF FILE: Std_Types.h
*********************************************************************************************************************/
