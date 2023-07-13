 /******************************************************************************
 *
 * Module: Common - Platform Abstraction
 *
 * File Name: Platform_Types.h
 *
 * Description: Platform types for ARM Cortex-M4F
 *
 *******************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/***********************************************************************************
 * Bit order definition
 ***********************************************************************************/
#define MSB_FIRST                   (0u)        /* Big endian bit ordering        */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering     */
/************************************************************************************
 *                            Byte order definition
 ************************************************************************************/
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering       */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering    */
 /************************************************************************************
  *     Platform type and endianess definitions, specific for ARM Cortex-M4F
  ************************************************************************************/
#define CPU_TYPE            CPU_TYPE_32

#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST
/************************************************************************************
 *                               Boolean Values
 ************************************************************************************/
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif


typedef unsigned char         boolean;

typedef unsigned char         uint8;          /*                    0 .. 255                 */
typedef signed char           sint8;          /*                 -128 .. +127                */
typedef unsigned short        uint16;         /*                    0 .. 65535               */
typedef signed short          sint16;         /*               -32768 .. +32767              */
typedef unsigned long         uint32;         /*                    0 .. 4294967295          */
typedef signed long           sint32;         /*          -2147483648 .. +2147483647         */
typedef unsigned long long    uint64;         /*                     0..1844674407370955161  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

#endif /* PLATFORM_TYPES_H */
