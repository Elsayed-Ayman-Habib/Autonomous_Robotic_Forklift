/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef UART_CFG_H
#define UART_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define UART_CONFIGURED_CHANNLES  (3U)
   
#define UART_0  0 
#define UART_1  1 
#define UART_2  2 
#define UART_3  3 
#define UART_4  4 
#define UART_5  5 
#define UART_6  6 
#define UART_7  7 
   
#define BAUD_RATE9600    9600 
#define BAUD_RATE115200  115200   
#define BAUD_RATE14400   14400  
#define BAUD_RATE19200   19200   
#define BAUD_RATE38400   38400   
#define BAUD_RATE57600   57600  
#define BAUD_RATE128000  128000  
#define BAUD_RATE256000  256000

#define LENGTH_5                0x0
#define LENGTH_6                0x1
#define LENGTH_7                0x2
#define LENGTH_8                0x3

#define PARITY_ENABLE           0x82
#define PARITY_DISABLE          0x00
   
#define STOP_BIT                3

#define DATA_LENGTH_BIT         5   
 
#define ENABLE_BIT              0

#define TRANSMIT_BIT            8
#define RECEIVE_BIT             9 

#define RECEIVE_INT_BIT         4 
#define TRANSMIT_INT_BIT        5
  
#define FIFO_TR                 5
#define FIFO_RX                 4

#define TRANSMIT_INTERRUPT_BIT  5
#define RECEIVE_INTERRUPT_BIT   4

#define FBRD_BITS               64.0
#define IBRD_BITS               16.0
   
#define FBRD_CHECK              0.5
#define UART_SYSTEM_CLOCK       16000000u

#define UART_SYS_CLOCK          0x0

#define STOP_BIT                1 

#if( STOP_BIT == 1)
    #define STOP_SELECT   0x0
#endif

#if ( STOP_BIT == 2)
    #define STOP_SELECT   0x8
#endif
   
#define EVEN_PARITY       2 

#if( EVEN_PARITY == 1)
    #define EVEN_PARITY_SELECT   0x4
#endif

#if ( EVEN_PARITY == 2)
    #define EVEN_PARITY_SELECT   0x0
#endif
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/

