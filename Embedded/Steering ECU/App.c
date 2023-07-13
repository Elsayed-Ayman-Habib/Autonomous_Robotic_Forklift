/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  App.c
 *        \brief  Application Driver
 *
 *      \details  Source File For Application Driver
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "App.h"
#include "Port.h"
#include "Dio.h"
#include "Gptm.h"
#include "IntCtrl.h"
#include "Adc.h"
#include "Uart.h"
#include "PID.h"
#include "PWM.h"
#include "Buzzer.h"
#include "Encoder.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 Bluetooth_Value;
float32 output ;

float32 measurement=0.0;
int Integer_Part_1 ;
float Fractional_part_1 ;
int Integer_Fractional_part_1;

int Integer_Part_2 ;
float Fractional_part_2 ;
int Integer_Fractional_part_2 ;
float32 Numbers_Send_PID;
char sending_buffer_PID[6] ;
float32 SetPoint=0.0;

float measurement_old;
float measurement_new;

uint64 LED_TICK = 0;

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
void Init_Drivers (void)
{
    //  Enable_Exceptions();
    Dio_Init(&Dio_Configuration);
    Port_Init(&Port_ConfigPtr);
    Uart_init(&Uart_ConfigPtr);
    Gpt_init(&Gpt_ConfigPtr);
    Gpt_StartTimer (TIMER0_A,800);
    //Gpt_StartTimer (TIMER1_A,62500);
    Gpt_EnableNotification(TIMER0_A);
    //  ADC_InitChannel(&Adc_ConfigPtr);
    Pwm_Init(&Pwm_ConfigPtr);
    EncoderChannelA_Init (&Encoder_ConfigPtr1);
    EncoderChannelB_Init (&Encoder_ConfigPtr2);
    IntCtrl_init(&IntCtrl_ConfigPtr);

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
void Timer0A_ISR()
{
    //    measurement=encoder_pos/1130.0;
    //
    //    PID_Compute(ptr,SetPoint, measurement);
    //
    //    if (ptr->Output >0.0)
    //    {
    //        set_DutyCycle( PWM0_PB5 , (ptr->Output)/1000.0  ,DOWN_MODE);
    //        Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX, STD_HIGH);
    //        Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_LOW);
    //    }
    //
    //    if (ptr->Output < 0.0)
    //    {
    //
    //        set_DutyCycle( PWM0_PB5 , (1.0-(1.0-((ptr->Output)))/1000.0) ,DOWN_MODE);
    //        Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX, STD_LOW );
    //        Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_HIGH);
    //    }
    //
    //    if (ptr->Output == 0.0 )
    //    {
    //        set_DutyCycle( PWM0_PB5 , Duty0 ,DOWN_MODE);
    //        Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX,STD_LOW );
    //        Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_LOW);
    //    }
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

void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*1000; i++);
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
void Timer1A_ISR()
{
    TICKS1++;
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
uint8 Time_Sec (LedSec sec)
{
    uint8 Time ;
    Time = sec ;
    return Time;
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
float roundToDecimalPlace(float number, int decimalPlaces) {
    float multiplier = 1.0;
    int i ;
    for (i = 0; i < decimalPlaces; i++) {
        multiplier *= 10.0;
    }

    float rounded = (int)(number * multiplier + 0.5) / multiplier;
    return rounded;
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

void App_Start (void)
{

    PID_Conroller test1;
    test1.ki=27;
    test1.kp=2800;
    test1.kd=1.5;

    test1.MaxLevel=1000;
    test1.Minlevel=-1000;
    test1.IntMaxLevel=700;
    test1.IntMinLevel=-700;
    test1.T=1;
    PID_Conroller* ptr=&test1;
    PID_init(ptr);


    while(1)
    {

        if (LED_TICK >= 1 && LED_TICK <= 6000000000)
        {
            Dio_WriteChannel(DioConf_RED_LED_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_GREEN_LED_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_BLUE_LED_CHANNEL_ID_INDEX, STD_HIGH);
        }
        else if (LED_TICK > 6000000000 && LED_TICK <= 12000000000)
        {
            Dio_WriteChannel(DioConf_RED_LED_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_GREEN_LED_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_BLUE_LED_CHANNEL_ID_INDEX, STD_LOW);
        }
        else if (LED_TICK > 12000000000 && LED_TICK <= 18000000000)
        {
            Dio_WriteChannel(DioConf_RED_LED_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_GREEN_LED_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_BLUE_LED_CHANNEL_ID_INDEX, STD_LOW);
            LED_TICK = 0 ;
        }

        uart_receive_string(receive_buffer, value_string);
        SetPoint=Number_1 - 0.01;

        if(SetPoint > 0.0)
        {
            Dio_WriteChannel(DioConf_RIGHT_LED_1_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_RIGHT_LED_2_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_LEFT_LED_1_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_LEFT_LED_2_CHANNEL_ID_INDEX, STD_LOW);
        }
        else if (SetPoint < 0.0 )
        {
            Dio_WriteChannel(DioConf_RIGHT_LED_1_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_RIGHT_LED_2_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_LEFT_LED_1_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_LEFT_LED_2_CHANNEL_ID_INDEX, STD_HIGH);
        }
        else
        {
            Dio_WriteChannel(DioConf_RIGHT_LED_1_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_RIGHT_LED_2_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_LEFT_LED_1_CHANNEL_ID_INDEX, STD_LOW);
            Dio_WriteChannel(DioConf_LEFT_LED_2_CHANNEL_ID_INDEX, STD_LOW);
        }
        //SetPoint=-0.57;
        if (SetPoint>1.5)
        {
            SetPoint=1.5;
        }
        else if (SetPoint<(-1.5))
        {
            SetPoint=-1.5;
        }

        PID_Compute(ptr,SetPoint, measurement);
        if (test1.Output >0.0)
        {
            set_DutyCycle( PWM0_PB5 , (test1.Output)/1000.0  ,DOWN_MODE);
            Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_LOW);
        }

        if (test1.Output < 0.0)
        {

            set_DutyCycle( PWM0_PB5 , (1.0-(1.0-((test1.Output)))/1000.0) ,DOWN_MODE);
            Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX, STD_LOW );
            Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_HIGH);
        }

        if (test1.Output == 0.0 )
        {
            set_DutyCycle( PWM0_PB5 , Duty0 ,DOWN_MODE);
            Dio_WriteChannel(DioConf_M3_INT1_CHANNEL_ID_INDEX,STD_LOW );
            Dio_WriteChannel(DioConf_M3_INT2_CHANNEL_ID_INDEX, STD_LOW);
        }

        Numbers_Send_PID= measurement+0.01;
        Float_to_chars_PID(Numbers_Send_PID, sending_buffer_PID);
        Send_String(UART_1,sending_buffer_PID);

        LED_TICK++;
    }
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
