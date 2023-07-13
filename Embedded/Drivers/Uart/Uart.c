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
#include "Uart.h"
#include "Uart_Regs.h"
#include "tm4c123gh6pm_registers.h"
#include "Dio.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define TIMEOUT_VALUE 10000
/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
STATIC const Uart_ConfigChannel * Uart_Configuration = NULL_PTR;
STATIC uint8 Uart_Status = UART_NOT_INITIALIZED;  
volatile uint32 * Uart_Ptr_global = NULL_PTR; /* global point to the required Port Registers base address to be used in ISR*/  
volatile  uint32 * Uart_Ptr_global_TX = NULL_PTR; /* global point to the required Port Registers base address to be used in ISR*/ 
float32 IBRD_VALUE =0.0;
float32 IBRD_SAVE = 0.0;
float32 FBRD_SAVE = 0.0;
float32 FBRD_VALUE = 0.0 ;

/*
 * ESP -> TIVA
 */
int receive_index_1 = 0;
int whole_num_esp_1 = 0;
int fraction_num_esp_1 = 0 ;
float Number_esp_1 = 0.0;
int whole_num_esp_2 = 0;
int fraction_num_esp_2 = 0 ;
float Number_esp_2 = 0.0;
int value_check = 0;

char receive_buffer_clear ;
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
void Uart_init(const Uart_ConfigType * ConfigPtr)
{
    Uart_Status       = UART_INITIALIZED;
    Uart_Configuration = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */

    uint8 i ;

    for( i = 0; i < UART_CONFIGURED_CHANNLES; i++)
    {

        volatile uint32 * Uart_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        volatile uint32 delay = 0;
        /*
         * Switch case to determine the Base address of the Port from the attribute port_num in the struct ConfigPtr
         */
        switch(Uart_Configuration[i].Channel)
        {
        case  0: Uart_Ptr = (volatile uint32 *)UART0_BASE_ADDRESS; /* UART_0 Base Address */
        break;
        case  1: Uart_Ptr = (volatile uint32 *)UART1_BASE_ADDRESS; /* UART_1 Base Address */
        break;
        case  2: Uart_Ptr = (volatile uint32 *)UART2_BASE_ADDRESS; /* UART_2 Base Address */
        break;
        case  3: Uart_Ptr = (volatile uint32 *)UART3_BASE_ADDRESS; /* UART_3 Base Address */
        break;
        case  4: Uart_Ptr = (volatile uint32 *)UART4_BASE_ADDRESS; /* UART_4 Base Address */
        break;
        case  5: Uart_Ptr = (volatile uint32 *)UART5_BASE_ADDRESS; /* UART_5 Base Address */
        break;
        case  6: Uart_Ptr = (volatile uint32 *)UART6_BASE_ADDRESS; /* UART_6 Base Address */
        break;
        case  7: Uart_Ptr = (volatile uint32 *)UART7_BASE_ADDRESS; /* UART_7 Base Address */
        break;
        }

        SYSCTL_RCGCUART_REG |= (1<<Uart_Configuration[i].Channel);
        delay = SYSCTL_RCGCUART_REG;

        CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),ENABLE_BIT) ;

        IBRD_VALUE = ((UART_SYSTEM_CLOCK)/(IBRD_BITS*(Uart_Configuration[i].Boud_Rate)));
        IBRD_SAVE = IBRD_VALUE ;
        *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTIBRD_BASE_OFFSET) = (uint32)IBRD_VALUE ;
        FBRD_VALUE = (((IBRD_SAVE) - ((uint32)IBRD_VALUE))*(FBRD_BITS));
        FBRD_SAVE = FBRD_VALUE;
        if (((FBRD_SAVE) - ((uint32)FBRD_VALUE)) > FBRD_CHECK )
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTFBRD_BASE_OFFSET) = ((uint32)FBRD_VALUE) + 1 ;
        }
        else if (((FBRD_SAVE) - ((uint32)FBRD_VALUE)) < FBRD_CHECK )
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTFBRD_BASE_OFFSET) = ((uint32)FBRD_VALUE);
        }
        else
        {
            /* Do Nathing */
        }

        *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) = (Uart_Configuration[i].Data_Length << DATA_LENGTH_BIT );

        if((Uart_Configuration[i].Partity_State) == PARITY)
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |= PARITY_ENABLE ;
            if (EVEN_PARITY == 1)
            {
                *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |= EVEN_PARITY_SELECT ;
            }
            else if(EVEN_PARITY == 2)
            {
                *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |= EVEN_PARITY_SELECT ;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else if((Uart_Configuration[i].Partity_State) == NO_PARITY)
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |= PARITY_DISABLE ;
        }
        else
        {
            //DO_NOTHING
        }

        if  ( STOP_BIT == 1 )
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |=  STOP_SELECT ;
        }
        else if ( STOP_BIT == 2 )
        {
            *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTLCRH_BASE_OFFSET) |=  STOP_SELECT ;
        }
        else
        {
            /* Do Nothing */
        }

        *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCC_BASE_OFFSET) = UART_SYS_CLOCK ;

        SET_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),ENABLE_BIT) ;

        if (Uart_Configuration[i].State == TRANSMIT)
        {
            SET_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),TRANSMIT_BIT) ;
            SET_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),RECEIVE_BIT) ;
            CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTIM_BASE_OFFSET),TRANSMIT_INTERRUPT_BIT) ;
            CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTIM_BASE_OFFSET),RECEIVE_INTERRUPT_BIT) ;
        }
        else if (Uart_Configuration[i].State == RECEIVE)
        {
            SET_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),TRANSMIT_BIT) ;
            SET_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTCTL_BASE_OFFSET),RECEIVE_BIT) ;
            CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTIM_BASE_OFFSET),RECEIVE_INTERRUPT_BIT) ;
            CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)Uart_Ptr + UARTIM_BASE_OFFSET),TRANSMIT_INTERRUPT_BIT) ;
        }
    }
}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
char Uart_RX (Uart_Channel UART_ID ) {
    volatile uint32 * Uart_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    char data = 0;
    switch(Uart_Configuration[UART_ID].Channel)
    {
    case  0: Uart_Ptr = (volatile uint32 *)UART0_BASE_ADDRESS; /* UART_0 Base Address */
    break;
    case  1: Uart_Ptr = (volatile uint32 *)UART1_BASE_ADDRESS; /* UART_1 Base Address */
    break;
    case  2: Uart_Ptr = (volatile uint32 *)UART2_BASE_ADDRESS; /* UART_2 Base Address */
    break;
    case  3: Uart_Ptr = (volatile uint32 *)UART3_BASE_ADDRESS; /* UART_3 Base Address */
    break;
    case  4: Uart_Ptr = (volatile uint32 *)UART4_BASE_ADDRESS; /* UART_4 Base Address */
    break;
    case  5: Uart_Ptr = (volatile uint32 *)UART5_BASE_ADDRESS; /* UART_5 Base Address */
    break;
    case  6: Uart_Ptr = (volatile uint32 *)UART6_BASE_ADDRESS; /* UART_6 Base Address */
    break; 
    case  7: Uart_Ptr = (volatile uint32 *)UART7_BASE_ADDRESS; /* UART_7 Base Address */
    break;
    }

    uint32 timeout_counter = TIMEOUT_VALUE;
    while(BIT_IS_SET((*(volatile uint8 *)((volatile uint8 *)Uart_Ptr + UARTFR_BASE_OFFSET)), FIFO_RX))
    {
        if(timeout_counter == 0)
        {
            return 0;   // Timeout period elapsed, exit loop and return default value
        }
        timeout_counter--;
    }
    data = (*(volatile uint8 *)((volatile uint8 *)Uart_Ptr + UARTDR_BASE_OFFSET)) ; //READ DATA
    return data;
} 

/******************************************************************************
 * \Syntax          : void Uart_TX (uint8 UART_ID , uint8 TRANS_DATA)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Uart_TX (Uart_Channel UART_ID , uint8 TRANS_DATA) {
    volatile uint32 * Uart_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    switch(Uart_Configuration[UART_ID].Channel)
    {
    case  0: Uart_Ptr = (volatile uint32 *)UART0_BASE_ADDRESS; /* UART_0 Base Address */
    break;
    case  1: Uart_Ptr = (volatile uint32 *)UART1_BASE_ADDRESS; /* UART_1 Base Address */
    break;
    case  2: Uart_Ptr = (volatile uint32 *)UART2_BASE_ADDRESS; /* UART_2 Base Address */
    break;
    case  3: Uart_Ptr = (volatile uint32 *)UART3_BASE_ADDRESS; /* UART_3 Base Address */
    break;
    case  4: Uart_Ptr = (volatile uint32 *)UART4_BASE_ADDRESS; /* UART_4 Base Address */
    break;
    case  5: Uart_Ptr = (volatile uint32 *)UART5_BASE_ADDRESS; /* UART_5 Base Address */
    break;
    case  6: Uart_Ptr = (volatile uint32 *)UART6_BASE_ADDRESS; /* UART_6 Base Address */
    break; 
    case  7: Uart_Ptr = (volatile uint32 *)UART7_BASE_ADDRESS; /* UART_7 Base Address */
    break;
    }
    while (GET_BIT((*(volatile uint8 *)((volatile uint8 *)Uart_Ptr + UARTFR_BASE_OFFSET)),(FIFO_TR))){}
    *(volatile uint8 *)((volatile uint8 *)Uart_Ptr + UARTDR_BASE_OFFSET) = TRANS_DATA ; //TRANSMITT DATA

}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Send_String(Uart_Channel UART_ID  , char *str)
{
    while(*str)
    {
        Uart_TX (UART_ID ,*(str++));
    }

}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void parse_message(char* message , char* dst)
{
    int i = 0;
    while (message[i] != '\0') {
        dst[i] =  message[i] ;
        i++;
    }
    dst[i] = '\0';

}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
int combineCharsToInt(char highByte, char lowByte) {
    if (value_check < 10 )
    {
        if (highByte > 0)
        {
            int result = (highByte - '0') * 10 + (lowByte - '0');
            return result;
        }
        else if (highByte == 0)
        {
            int result = (lowByte - '0');
            return result;
        }
    }
    else if (value_check >= 10)
    {
        int result = (highByte - '0') * 10 + (lowByte - '0');
        return result;
    }
}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
float intToFloat(char sign , int wholeNum, int fracNum) {
    if (sign == '+')
    {
        float result = wholeNum + (fracNum / 100.0);
        return result;
    }
    else if (sign == '-')
    {
        float result = -1 * (wholeNum + (fracNum / 100.0));
        return result;
    }
}
/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void uart_receive_string_esp(char *receive_buffer_1, char* value_string_1)
{
    uint8 x = 0;
    incoming_1 = Uart_RX (UART_2);  // Receive data into buffer

    if (incoming_1 == '*')
    {

        while(receive_index_1 <= 10)
        {
            incoming_1 = Uart_RX (UART_2);  // Receive data into buffer
            receive_buffer_1[receive_index_1 ] = incoming_1 ;
            receive_index_1++;
        }
    }

    // Check if entire message has been received
    receive_index_1 = 0;  // Reset receive buffer for next message
    parse_message(receive_buffer_1 , value_string_1); // Parse received data

    whole_num_esp_1 = combineCharsToInt(value_string_1[1], value_string_1[2]);
    fraction_num_esp_1 = combineCharsToInt(value_string_1[3], value_string_1[4]);
    if (value_string_1 != NULL_PTR  &&
            (value_string_1[0] == '+' || value_string_1[0] == '-') &&
            (whole_num_esp_1 >= 0 && whole_num_esp_1 <= 99) &&
            (fraction_num_esp_1 >= 0 && fraction_num_esp_1 <= 99))
    {
        Number_esp_1 = intToFloat(value_string_1[0], whole_num_esp_1, fraction_num_esp_1);
    }

    whole_num_esp_2 = combineCharsToInt(value_string_1[6], value_string_1[7]);
    fraction_num_esp_2 = combineCharsToInt(value_string_1[8], value_string_1[9]);
    if (value_string_1 != NULL_PTR  &&
            (value_string_1[5] == '+' || value_string_1[5] == '-') &&
            (whole_num_esp_2 >= 0 && whole_num_esp_2 <= 99) &&
            (fraction_num_esp_2 >= 0 && fraction_num_esp_2 <= 99))
    {
        Number_esp_2 = intToFloat(value_string_1[5], whole_num_esp_2, fraction_num_esp_2);
    }
}

/******************************************************************************
 * \Syntax          : void Uart_RX (uint8 UART_ID )
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Clear_Uart_Bus(Uart_Channel UART_ID )
{
    volatile uint32 * Uart_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    switch(Uart_Configuration[UART_ID].Channel)
    {
    case  0: Uart_Ptr = (volatile uint32 *)UART0_BASE_ADDRESS; /* UART_0 Base Address */
    break;
    case  1: Uart_Ptr = (volatile uint32 *)UART1_BASE_ADDRESS; /* UART_1 Base Address */
    break;
    case  2: Uart_Ptr = (volatile uint32 *)UART2_BASE_ADDRESS; /* UART_2 Base Address */
    break;
    case  3: Uart_Ptr = (volatile uint32 *)UART3_BASE_ADDRESS; /* UART_3 Base Address */
    break;
    case  4: Uart_Ptr = (volatile uint32 *)UART4_BASE_ADDRESS; /* UART_4 Base Address */
    break;
    case  5: Uart_Ptr = (volatile uint32 *)UART5_BASE_ADDRESS; /* UART_5 Base Address */
    break;
    case  6: Uart_Ptr = (volatile uint32 *)UART6_BASE_ADDRESS; /* UART_6 Base Address */
    break;
    case  7: Uart_Ptr = (volatile uint32 *)UART7_BASE_ADDRESS; /* UART_7 Base Address */
    break;
    }
    *(volatile uint8 *)((volatile uint8 *)Uart_Ptr + UARTDR_BASE_OFFSET) &= 0x00  ; //READ DATA
}

/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Float_to_chars_esp(float num1 , float num2 , char* str1)
{
    if (num1 < 0 )
    {
        Integer_Part_esp_1 = (-1 * ((int) num1));
        Fractional_part_esp_1 = (-1 * num1) - (float) Integer_Part_esp_1;
        Integer_Fractional_part_esp_1 = Fractional_part_esp_1 * 100;
    }
    else if (num1 > 0 )
    {
        Integer_Part_esp_1 = (int) num1;
        Fractional_part_esp_1 = num1 - (float) Integer_Part_esp_1;
        Integer_Fractional_part_esp_1 = Fractional_part_esp_1 * 100;
    }
    if (num2 < 0 )
    {
        Integer_Part_esp_2 = (-1 * ((int) num2));
        Fractional_part_esp_2 = (-1 * num2) - (float) Integer_Part_esp_2;
        Integer_Fractional_part_esp_2 = Fractional_part_esp_2 * 100;
    }
    else if (num2 > 0)
    {
        Integer_Part_esp_2 = (int) num2;
        Fractional_part_esp_2 = num2 - (float) Integer_Part_esp_2;
        Integer_Fractional_part_esp_2 = Fractional_part_esp_2 * 100;
    }

    /* For First Number */
    if (num1 >= 0)
    {
        str1[0] = '+';
    }
    else if (num1 < 0)
    {
        str1[0] = '-';
    }
    if (Integer_Part_esp_1 < 10 )
    {
        str1[1] = 0 + '0';
        str1[2] = Integer_Part_esp_1 + '0';
    }
    else if (Integer_Part_esp_1 >= 10 )
    {
        // Extract the first digit
        str1[1] = Integer_Part_esp_1 / 10 + '0';

        // Extract the second digit
        str1[2] = Integer_Part_esp_1 % 10 + '0';
    }
    if (Integer_Fractional_part_esp_1 < 10 )
    {
        str1[3] = 0 + '0';
        str1[4] = Integer_Fractional_part_esp_1 + '0';
    }
    else if (Integer_Fractional_part_esp_1 >= 10 )
    {
        // Extract the first digit
        str1[3] = Integer_Fractional_part_esp_1 / 10 + '0';

        // Extract the second digit
        str1[4] = Integer_Fractional_part_esp_1 % 10 + '0';
    }

    /* For Second Number */
    if (num2 >= 0)
    {
        str1[5] = '+';
    }
    else if (num2 < 0)
    {
        str1[5] = '-';
    }
    if (Integer_Part_esp_2 < 10 )
    {
        str1[6] = 0 + '0';
        str1[7] = Integer_Part_esp_2 + '0';
    }
    else if (Integer_Part_esp_2 >= 10 )
    {
        // Extract the first digit
        str1[6] = Integer_Part_esp_2 / 10 + '0';

        // Extract the second digit
        str1[7] = Integer_Part_esp_2 % 10 + '0';
    }
    if (Integer_Fractional_part_esp_2 < 10 )
    {
        str1[8] = 0 + '0';
        str1[9] = Integer_Fractional_part_esp_2 + '0';
    }
    else if (Integer_Fractional_part_esp_2 >= 10 )
    {
        // Extract the first digit
        str1[8] = Integer_Fractional_part_esp_2 / 10 + '0';

        // Extract the second digit
        str1[9] = Integer_Fractional_part_esp_2 % 10 + '0';
    }

    str1[10] = '\n';
//    str1[11] = '\0';
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
