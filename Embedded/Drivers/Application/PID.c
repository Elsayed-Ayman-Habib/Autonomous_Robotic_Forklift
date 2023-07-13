#include "PID.h"
//#define FILTER 1
#define LIMIT_OUTPUT 1

  /*initiating the PID by feeding it with its parameters*/
 void PID_init(PID_Conroller* p)
 {
     p->PrevError=0;
     p->PrevInteg=0;
     p->X_differential=0;
     p->X_integral=0;
 }

 /* updating the PID output */
 float32 PID_Compute(PID_Conroller*p,float32 setpoint,float32 measurement)
 {
     float32 error=setpoint-measurement;
     float32 output=0;

//     if (error < 0.08 && error > 0.0)
//     {
//         error = 0.0;
//     }
//     if (error < 0.0 && error > -0.08)
//     {
//         error = 0.0;
//     }
    /* proportional term formula */
    p->X_proportional=(p->kp)*error;

    /* integral term formula */

    p->X_integral=(p->ki)*((((error+p->PrevError)*(p->T/1000))/2)+p->PrevInteg);

    /* the anti-wind up method  */

   if((p->X_integral>p->IntMaxLevel)&&((p->Output < 0)? (error >= 0): (error < 0)))
    {
        p->X_integral=p->IntMaxLevel;
    }
    else if ((p->X_integral<p->IntMinLevel)&&((p->Output < 0)? (error >= 0): (error < 0)))
    {
        p->X_integral=p->IntMinLevel;
    }

    /* the differential term with a first order low pass filter */
   // #ifdef FILTER
   // p->X_differential= ((((2*p->kd)*(error-p->PrevError))/((2*p->tau)+p->T))+((2*p->tau -p->T)*(p->X_differential))/(2*p->tau +p->T));
    //#endif // filter

    /* the differential term without the filter */

//    #ifndef FILTER
    p->X_differential=(((p->kd*error)/(p->T/1000))-((p->kd * p->PrevError)/(p->T/1000)));
//    #endif // nfilter

    p->Output=p->X_differential+p->X_integral+p->X_proportional;

   /* limiting the output if needed */
    #ifdef LIMIT_OUTPUT
    if (p->Output>p->MaxLevel)
    {
        p->Output=p->MaxLevel;
    }
    else if (p->Output<p->Minlevel)
    {
        p->Output=p->Minlevel;
    }

    #endif
    p->PrevInteg=p->PrevInteg+(((error+p->PrevError)*(p->T/1000))/2);
    p->PrevError=error;

    return p->Output;
 }

/* output equation parameters " x(n)=A*e(n)+B*e(n-1)+C*intprev " */
