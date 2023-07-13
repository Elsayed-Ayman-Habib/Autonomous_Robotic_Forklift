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
#include "Port.h"
#include "Dio.h"
#include "Port_Regs.h"
#include "Port_Cfg.h"
#include "Encoder.h"
#include "Encoder_Cfg.h"
#include "Uart.h"
#include "Gptm.h"
#include "tm4c123gh6pm_registers.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
STATIC const Encoder_ConfigChannel * Encoder_Configuration1 = NULL_PTR;
STATIC const Encoder_ConfigChanne2 * Encoder_Configuration2 = NULL_PTR;
volatile long encoder_pos =0;
unsigned int IntCtrl_Status = 0;

STATIC uint8 Encoder_Status = ENCODER_NOT_INITIALIZED;
extern float32 measurement;

float Right_Ticks = 0.0 ;
float Left_Ticks = 0.0 ;

float Size_FLoat;
int Size_Int_Left;
int Size_Int_Right ;
extern float32 SetPoint_S ;

extern float Numbers_Send_esp_1;
extern float Numbers_Send_esp_2;

extern char sending_buffer_1[11] ;

// Number of ticks a wheel makes moving a linear distance of 1 meter
const double TICKS_PER_RAD = 1031.0;
const double TICKS_PER_METER = 850;

// Distance from center of the left tire to the center of the right tire in m
const double WHEEL_BASE_W = 0.429;

const double WHEEL_BASE_H = 0.358;

double distance ;
double delta_t;

double velWheel ;
int prevWheelCount;
double prevTime ;

float Result_Value[361]= {0.599162011173185, 0.607865732418108, 0.61652316233406, 0.625133641624234, 0.633696514567294, 0.642211129067315, 0.650676836703436, 0.659092992779244, 0.667458956371869, 0.675774090380795, 0.684037761576372, 0.692249340648045, 0.700408202252275, 0.708513725060164, 0.716565291804766, 0.724562289328103, 0.73250410862785, 0.74039014490372, 0.748219797603519, 0.755992470468879, 0.763707571580669, 0.77136451340407, 0.778962712833316, 0.786501591236102, 0.793980574497651, 0.801399093064432, 0.808756581987532, 0.816052480965687, 0.82328623438794, 0.830457291375961, 0.837565105825999, 0.844609136450463, 0.851588846819148, 0.858503705400088, 0.86535318560003, 0.872136765804538, 0.878853929417714, 0.885504164901544, 0.892086965814848, 0.89860183085185, 0.905048263880354, 0.911425773979527, 0.917733875477283, 0.92397208798727, 0.930139936445454, 0.936236951146294, 0.942262667778516, 0.948216627460467, 0.954098376775068, 0.959907467804335, 0.965643458163497, 0.971305911034678, 0.976894395200171, 0.982408485075268, 0.987847760740678, 0.993211807974499, 0.998500218283768, 1.00371258893556, 1.00884852298768, 1.01390762931885, 1.01888952265855, 1.02379382361631, 1.02862015871062, 1.03336816039738, 1.03803746709788, 1.04262772322633, 1.04713857921696, 1.05156969155063, 1.05592072278096, 1.06019134156009, 1.06438122266386, 1.06849004701661, 1.07251750171545, 1.07646328005412, 1.08032708154631, 1.08410861194858, 1.08780758328276, 1.09142371385785, 1.09495672829151, 1.09840635753102, 1.10177233887375, 1.10505441598719, 1.10825233892845, 1.11136586416334, 1.11439475458484, 1.11733877953122, 1.12019771480359, 1.12297134268296, 1.12565945194682, 1.12826183788525, 1.13077830231648, 1.133208653602, 1.13555270666115, 1.13781028298522, 1.13998121065103, 1.14206532433403, 1.1440624653209, 1.14597248152162, 1.14779522748105, 1.14953056439004, 1.15117836009597, 1.1527384891128, 1.15421083263069, 1.15559527852495, 1.15689172136469, 1.15810006242076, 1.15922020967331, 1.16025207781879, 1.16119558827644, 1.1620506691943, 1.16281725545463, 1.16349528867893, 1.16408471723235, 1.16458549622761, 1.16499758752845, 1.16532095975253, 1.16555558827381, 1.1657014552244, 1.16575854949599, 1.16572686674061, 1.16560640937103, 1.16539718656055, 1.1650992142423, 1.16471251510802, 1.16423711860634, 1.16367306094055, 1.16302038506583, 1.16227914068598, 1.16144938424961, 1.16053117894589, 1.15952459469972, 1.15842970816638, 1.15724660272573, 1.15597536847581, 1.15461610222604, 1.15316890748981, 1.1516338944766, 1.15001118008359, 1.14830088788677, 1.14650314813151, 1.14461809772266, 1.14264588021409, 1.14058664579781, 1.13844055129249, 1.13620776013154, 1.13388844235065, 1.13148277457484, 1.12899094000504, 1.12641312840409, 1.12374953608233, 1.12100036588262, 1.11816582716492, 1.11524613579032, 1.11224151410464, 1.10915219092143, 1.10597840150463, 1.10272038755059, 1.09937839716968, 1.09595268486741, 1.09244351152503, 1.08885114437968, 1.08517585700403, 1.08141792928544, 1.07757764740466, 1.07365530381401, 1.06965119721515, 1.06556563253631, 1.06139892090903, 1.05715137964456, 1.0528233322096, 1.04841510820173, 1.04392704332425, 1.0393594793607, 1.03471276414876, 1.02998725155377, 1.02518330144181, 1.0203012796523, 1.01534155797008, 1.01030451409717, 1.00519053162395, 1.0 ,0.994733314504391, 0.989390876215617, 0.983973091981036, 0.978480374385893, 0.972913141721901, 0.96727181795538, 0.961556832694976, 0.955768621158945, 0.949907624142003, 0.943974287981766, 0.937969064524754, 0.931892411091984, 0.925744790444141, 0.919526670746338, 0.913238525532467, 0.906880833669129, 0.900454079319175, 0.893958751904832, 0.887395346070429, 0.880764361644732, 0.874066303602877, 0.867301682027919, 0.860471012071978, 0.85357481391702, 0.846613612735232, 0.839587938649037, 0.832498326690716, 0.82534531676167, 0.818129453591299, 0.810851286695519, 0.803511370334919, 0.796110263472547, 0.788648529731345, 0.781126737351228, 0.773545459145806, 0.765905272458767, 0.758206759119908, 0.750450505400825, 0.742637101970268, 0.73476714384916, 0.726841230365281, 0.718859965107629, 0.710823955880455, 0.702733814656974, 0.694590157532762, 0.686393604678839, 0.678144780294439, 0.669844312559475, 0.661492833586702, 0.653090979373577, 0.644639389753829, 0.636138708348728, 0.627589582518075, 0.618992663310902, 0.61034860541589, 0.601658067111515, 0.592921710215915, 0.584140200036493, 0.575314205319247, 0.566444398197847, 0.557531454142445, 0.548576051908239, 0.539578873483782, 0.530540604039045, 0.521461931873238, 0.512343548362398, 0.503186147906731, 0.493990427877737, 0.484757088565098, 0.475486833123351, 0.46618036751834, 0.456838400473452, 0.447461643415646, 0.438050810421275, 0.428606618161708, 0.419129785848751, 0.409621035179874, 0.400081090283256, 0.390510677662635, 0.380910526141987, 0.371281366810019, 0.361623932964493, 0.351938960056388, 0.342227185633888, 0.332489349286216, 0.32272619258731, 0.312938459039354, 0.303126894016151, 0.293292244706366, 0.283435260056619, 0.273556690714454, 0.263657288971174, 0.253737808704548, 0.243799005321403, 0.233841635700097, 0.223866458132878, 0.213874232268137, 0.203865719052562, 0.193841680673182, 0.18380288049933, 0.173750083024507, 0.163684053808161, 0.153605559417388, 0.143515367368558, 0.13341424606886, 0.123302964757791, 0.113182293448567, 0.103053002869495, 0.092915864405268, 0.082771650038229, 0.072621132289575, 0.062465084160533, 0.05230427907349, 0.04213949081309, 0.031971493467316, 0.021801061368531, 0.011628969034517, 0.001455991109487, -0.008717097694903, -0.018889522658553, -0.02906050911192, -0.039229282495005, -0.049395068416346, -0.059557092711986, -0.069714581504431, -0.079866761261584, -0.090012858855651, -0.100152101622016, -0.110283717418088, -0.120406934682098, -0.130520982491858, -0.140625090623468, -0.150718489609975, -0.160800410799968, -0.170870086416114, -0.18092674961363, -0.190969634538675, -0.200997976386682, -0.211011011460592, -0.221007977229016, -0.230988112384308, -0.240950656900534, -0.25089485209136, -0.260819940667819, -0.270725166795991, -0.280609776154557, -0.290473015992243, -0.30031413518515, -0.310132384293949, -0.319927015620957, -0.329697283267078, -0.339442443188604, -0.349161753253876, -0.358854473299803, -0.368519865188226, -0.378157192862132, -0.387765722401708, -0.397344722080226, -0.406893462419775, -0.416411216246809, -0.425897258747524, -0.435350867523057, -0.444771322644499, -0.454157906707719, -0.463509904887999, -0.472826604994471, -0.48210729752435, -0.491351275716969, -0.500557835607597, -0.509726276081055, -0.518855898925105, -0.527946008883618, -0.53699591370953, -0.546004924217548, -0.554972354336643, -0.563897521162292, -0.572779745008487, -0.581618349459493, -0.59041266142136, -0.599162011173184};
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
 * \Syntax          :void EncoderChannelA_Init (const Encoder_ConfigType * ConfigPtr)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void EncoderChannelA_Init (const Encoder_ConfigType1 * ConfigPtr)
{

    Encoder_Status       = ENCODER_INITIALIZED;
    Encoder_Configuration1 = ConfigPtr->Channels1; /* address of the first Channels structure --> Channels[0] */
    uint8 i ;
    for( i = 0; i < ENCODER_CONFIGURED_CHANNLES; i++)
    {

        if (Encoder_Configuration1[i].Sense == EDGE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin2);
        }
        else if (Encoder_Configuration1[i].Sense == LEVEL)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin2);
        }

        if (Encoder_Configuration1[i].Detect_Edges == SINGLE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin2);

            if (Encoder_Configuration1[i].Edge == RISING)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin2);
            }
            else if (Encoder_Configuration1[i].Edge == FALLING)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin2);
            }
        }
        else if (Encoder_Configuration1[i].Detect_Edges == BOTH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin2);
        }

        SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin2);

        if (Encoder_Configuration1[i].Encoder_Notification == INTERRUPT_Off)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin2);
        }
        else if (Encoder_Configuration1[i].Encoder_Notification == INTERRUPT_On)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin2);
        }
    }
}

/******************************************************************************
 * \Syntax          :void EncoderChannelA_Init (const Encoder_ConfigType * ConfigPtr)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void EncoderChannelB_Init (const Encoder_ConfigType2 * ConfigPtr)
{

    Encoder_Status       = ENCODER_INITIALIZED;
    Encoder_Configuration2 = ConfigPtr->Channels2; /* address of the first Channels structure --> Channels[0] */
    uint8 i ;
    for( i = 0; i < ENCODER_CONFIGURED_CHANNLES; i++)
    {

        if (Encoder_Configuration2[i].Sense == EDGE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin1);
        }
        else if (Encoder_Configuration2[i].Sense == LEVEL)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIS_REG_OFFSET) , PORT_Pin1);
        }

        if (Encoder_Configuration2[i].Detect_Edges == SINGLE)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin1);

            if (Encoder_Configuration2[i].Edge == RISING)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin1);
            }
            else if (Encoder_Configuration2[i].Edge == FALLING)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIEV_REG_OFFSET) , PORT_Pin1);
            }
        }
        else if (Encoder_Configuration2[i].Detect_Edges == BOTH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIBE_REG_OFFSET) , PORT_Pin1);
        }

        SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin1);

        if (Encoder_Configuration2[i].Encoder_Notification == INTERRUPT_Off)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin1);
        }
        else if (Encoder_Configuration2[i].Encoder_Notification == INTERRUPT_On)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOIM_REG_OFFSET) , PORT_Pin1);
        }
    }
}

/******************************************************************************
 * \Syntax          : void GPIOPortF_Handler(void)
 * \Description     : GPIO PORTF External Interrupt - ISR
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void calc_vel_wheel()
{
    double timer=0;

    // Manage rollover and rollunder when we get outside the 16-bit integer range
    int numOfTicks = (  encoder_pos  - prevWheelCount);

    // If we have had a big jump, it means the tick count has rolled over.
    if (numOfTicks > 10000) {
        numOfTicks = 0 - (65535 - numOfTicks);
    }

    // Calculate wheel velocity in meters per second
    distance =(numOfTicks/TICKS_PER_METER);
    timer=millis()/1000.0;
    delta_t=(timer-prevTime);
    velWheel = distance/delta_t;
    prevWheelCount = encoder_pos;
    prevTime = (millis()/1000.0);
}

/******************************************************************************
 * \Syntax          : void GPIOPortF_Handler(void)
 * \Description     : GPIO PORTF External Interrupt - ISR
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void GPIOPortB_Handler(void)
{
    IntCtrl_Status = (*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIORIS_REG_OFFSET));

    if (IntCtrl_Status & GPIO_PIN_2)
    {
        Size_FLoat = (((SetPoint_S + 1.5708)/3.1416)*(360))+ 0.5;
        Size_Int_Left = (int)Size_FLoat;
        Size_Int_Right = 361 - (int)Size_FLoat;
        if ( (*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + PORT_DATA_REG_OFFSET)) & GPIO_PIN_1)
        {
            encoder_pos--;
            Right_Ticks = Right_Ticks - Result_Value[Size_Int_Right];
            Left_Ticks = Left_Ticks - Result_Value[Size_Int_Left];
        }
        else
        {
            encoder_pos++;
            Right_Ticks = Right_Ticks + Result_Value[Size_Int_Right];
            Left_Ticks = Left_Ticks  + Result_Value[Size_Int_Left];
        }
        Numbers_Send_esp_1 = (Right_Ticks / 100.0) + 0.01;
        Numbers_Send_esp_2 = (Left_Ticks / 100.0) + 0.01;
        Float_to_chars_esp(Numbers_Send_esp_1 , Numbers_Send_esp_2 , sending_buffer_1);
        Send_String(UART_2 , sending_buffer_1);
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin2);
    }
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORTB_BASE_ADDRESS + GPIO_GPIOICR_REG_OFFSET) , PORT_Pin1);
}

/******************************************************************************
 * \Syntax          : void GPIOPortF_Handler(void)
 * \Description     : GPIO PORTF External Interrupt - ISR
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
int Encoder_GetPosition(void)
{
    return encoder_pos;
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
