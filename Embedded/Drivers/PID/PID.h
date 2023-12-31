
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <PID.h>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
//#ifndef <PID_H>
//#define <PID_H>

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
  #include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 typedef struct
 {
     /* PID Gains */
      float32 kp,ki,kd;

     /* proportional component, integral component and differential component*/
      float32 X_proportional,X_integral,X_differential;


     /* Sampling Time */
      float32 T;

     /* time constant for the first order low pass filter*/
      float32 tau;

     /*error , previous error and the previous integration */
      float32 Error,PrevError,PrevInteg;

      /* for the anti-wind up */
      float32 IntMaxLevel,IntMinLevel;

      /* for limiting the output */

      float32 MaxLevel,Minlevel;

     /*PID output*/
     float32 Output;

 }PID_Conroller;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

  #define FILTER 1
  #define LIMIT_OUTPUT 1
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 /*initiating the PID by feeding it with its parameters*/
 void PID_init(PID_Conroller* p);

 /* updating the PID output */
 float32 PID_Compute(PID_Conroller* p,float32 setpoint,float32 measurement);


//#endif  /* PID_H */

/**********************************************************************************************************************
 *  END OF FILE: PID.h
 *********************************************************************************************************************/

