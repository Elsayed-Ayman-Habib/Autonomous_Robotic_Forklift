/**********************************************************************************************************************
 *
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Regs.h
 *       Module:  Nested Vector Interrupt Driver 
 *
 *  Description: Nested Vector Interrupt Driver Registers     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_RGS_H
#define INTCTRL_RGS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* IntCtrl Registers base addresses */
#define INTCTRL_BASE_ADDRESS             0xE000E000

#define INTCTRL_PRIX_BASE_ADDRESS        0xE000E000
#define INTCTRL_ENX_BASE_ADDRESS         0xE000E000
#define INTCTRL_SWTRIG_BASE_ADDRESS      0xE000E000
#define INTCTRL_INTCTRL_BASE_ADDRESS     0xE000E000
#define INTCTRL_VTABLE_BASE_ADDRESS      0xE000E000
#define INTCTRL_APINT_BASE_ADDRESS       0xE000E000
#define INTCTRL_SYSPRIX_BASE_ADDRESS     0xE000E000
#define INTCTRL_SYSHNDCTRL_BASE_ADDRESS  0xE000E000
#define INTCTRL_FAULTSTAT_BASE_ADDRESS   0xE000E000
#define INTCTRL_HFAULTSTAT_BASE_ADDRESS  0xE000E000

/* IntCtrl Registers offset addresses */
#define INTCTRL_PRI0_BASE_OFFSET       0x400
#define INTCTRL_PRI1_BASE_OFFSET       0x404
#define INTCTRL_PRI2_BASE_OFFSET       0x408
#define INTCTRL_PRI3_BASE_OFFSET       0x40C
#define INTCTRL_PRI4_BASE_OFFSET       0x410
#define INTCTRL_PRI5_BASE_OFFSET       0x414
#define INTCTRL_PRI6_BASE_OFFSET       0x418
#define INTCTRL_PRI7_BASE_OFFSET       0x41C
#define INTCTRL_PRI8_BASE_OFFSET       0x420
#define INTCTRL_PRI9_BASE_OFFSET       0x424
#define INTCTRL_PRI10_BASE_OFFSET      0x428
#define INTCTRL_PRI11_BASE_OFFSET      0x42C
#define INTCTRL_PRI12_BASE_OFFSET      0x430
#define INTCTRL_PRI13_BASE_OFFSET      0x434
#define INTCTRL_PRI14_BASE_OFFSET      0x438
#define INTCTRL_PRI15_BASE_OFFSET      0x43C
#define INTCTRL_PRI16_BASE_OFFSET      0x440
#define INTCTRL_PRI17_BASE_OFFSET      0x444
#define INTCTRL_PRI18_BASE_OFFSET      0x448
#define INTCTRL_PRI19_BASE_OFFSET      0x44C
#define INTCTRL_PRI20_BASE_OFFSET      0x450
#define INTCTRL_PRI21_BASE_OFFSET      0x454
#define INTCTRL_PRI22_BASE_OFFSET      0x458
#define INTCTRL_PRI23_BASE_OFFSET      0x45C
#define INTCTRL_PRI24_BASE_OFFSET      0x460
#define INTCTRL_PRI25_BASE_OFFSET      0x464
#define INTCTRL_PRI26_BASE_OFFSET      0x468
#define INTCTRL_PRI27_BASE_OFFSET      0x46C
#define INTCTRL_PRI28_BASE_OFFSET      0x470
#define INTCTRL_PRI29_BASE_OFFSET      0x474
#define INTCTRL_PRI30_BASE_OFFSET      0x478
#define INTCTRL_PRI31_BASE_OFFSET      0x47C
#define INTCTRL_PRI32_BASE_OFFSET      0x480
#define INTCTRL_PRI33_BASE_OFFSET      0x484
#define INTCTRL_PRI34_BASE_OFFSET      0x488

#define INTCTRL_EN0_BASE_OFFSET        0x100
#define INTCTRL_EN1_BASE_OFFSET        0x104
#define INTCTRL_EN2_BASE_OFFSET        0x108
#define INTCTRL_EN3_BASE_OFFSET        0x10C
#define INTCTRL_EN4_BASE_OFFSET        0x110
   
#define INTCTRL_PEND0_BASE_OFFSET      0x200
#define INTCTRL_PEND1_BASE_OFFSET      0x204
#define INTCTRL_PEND2_BASE_OFFSET      0x208
#define INTCTRL_PEND3_BASE_OFFSET      0x20C
#define INTCTRL_PEND4_BASE_OFFSET      0x210

#define INTCTRL_SWTRIG_BASE_OFFSET     0xF00

#define INTCTRL_INTCTRL_BASE_OFFSET    0xD04

#define INTCTRL_VTABLE_BASE_OFFSET     0xD08

#define INTCTRL_APINT_BASE_OFFSET      0xD0C

#define INTCTRL_SYSPRI1_BASE_OFFSET    0xD18
#define INTCTRL_SYSPRI2_BASE_OFFSET    0xD1C
#define INTCTRL_SYSPRI3_BASE_OFFSET    0xD20

#define INTCTRL_SYSHNDCTRL_BASE_OFFSET 0xD24

#define INTCTRL_FAULTSTAT_BASE_OFFSET  0xD28 

#define INTCTRL_HFAULTSTAT_BASE_OFFSET 0xD2C

/* Name Of Bit - Bit Mask */
#define INTCTRL_PRIX_INTA_MASK           0xFFFFFF1F
#define INTCTRL_PRIX_INTB_MASK           0xFFFF1FFF
#define INTCTRL_PRIX_INTC_MASK           0xFF1FFFFF
#define INTCTRL_PRIX_INTD_MASK           0x1FFFFFFF

#define INTCTRL_INTCTRL_VECACT_MASK      0x000000FF
#define INTCTRL_INTCTRL_RETBASE_MASK     0x00000800
#define INTCTRL_INTCTRL_VECPEND_MASK     0x000FF000
#define INTCTRL_INTCTRL_ISRPEND_MASK     0x00400000
#define INTCTRL_INTCTRL_ISRPRE_MASK      0x00800000
#define INTCTRL_INTCTRL_PENDSTCLR_MASK   0x02000000
#define INTCTRL_INTCTRL_PENDSTSET_MASK   0x04000000
#define INTCTRL_INTCTRL_UNPENDSV_MASK    0x08000000
#define INTCTRL_INTCTRL_PENDSV_MASK      0x10000000
#define INTCTRL_INTCTRL_NMISET_MASK      0x80000000

#define INTCTRL_APINT_VECTRESET_MASK     0x00000001
#define INTCTRL_APINT_VECTCLRACT_MASK    0x00000002
#define INTCTRL_APINT_SYSRESREQ_MASK     0x00000004
#define INTCTRL_APINT_PRIGROUP_MASK      0x00000700
#define INTCTRL_APINT_ENDIANESS_MASK     0x00008000
#define INTCTRL_APINT_VECTKEY_MASK       0xFFFF0000

#define INTCTRL_SYSPRI1_MEM_MASK         0x000000E0
#define INTCTRL_SYSPRI1_BUS_MASK         0x0000E000
#define INTCTRL_SYSPRI1_USAGE_MASK       0x00E00000

#define INTCTRL_SYSPRI2_SVC_MASK         0xE0000000

#define INTCTRL_SYSPRI3_DEBUG_MASK       0x000000E0
#define INTCTRL_SYSPRI3_PENDSV_MASK      0x00E00000
#define INTCTRL_SYSPRI3_TICK_MASK        0xE0000000

#define INTCTRL_SYSHNDCTRL_MEMA_MASK     0x00000001
#define INTCTRL_SYSHNDCTRL_BUSA_MASK     0x00000002
#define INTCTRL_SYSHNDCTRL_USGA_MASK     0x00000008
#define INTCTRL_SYSHNDCTRL_SVCA_MASK     0x00000080
#define INTCTRL_SYSHNDCTRL_MON_MASK      0x00000100
#define INTCTRL_SYSHNDCTRL_PNDSV_MASK    0x00000400
#define INTCTRL_SYSHNDCTRL_TICK_MASK     0x00000800
#define INTCTRL_SYSHNDCTRL_USAGEP_MASK   0x00001000
#define INTCTRL_SYSHNDCTRL_MEMP_MASK     0x00002000
#define INTCTRL_SYSHNDCTRL_BUSP_MASK     0x00004000
#define INTCTRL_SYSHNDCTRL_SVC_MASK      0x00008000
#define INTCTRL_SYSHNDCTRL_MEM_MASK      0x00010000
#define INTCTRL_SYSHNDCTRL_BUS_MASK      0x00020000
#define INTCTRL_SYSHNDCTRL_USAGE_MASK    0x00040000

#define INTCTRL_FAULTSTAT_IERR_MASK      0x00000001
#define INTCTRL_FAULTSTAT_DERR_MASK      0x00000002
#define INTCTRL_FAULTSTAT_MUSTKE_MASK    0x00000008
#define INTCTRL_FAULTSTAT_MSTKE_MASK     0x00000010
#define INTCTRL_FAULTSTAT_MLSPERR_MASK   0x00000020
#define INTCTRL_FAULTSTAT_MMARV_MASK     0x00000080
#define INTCTRL_FAULTSTAT_IBUS_MASK      0x00000100
#define INTCTRL_FAULTSTAT_PRECISE_MASK   0x00000200
#define INTCTRL_FAULTSTAT_IMPRE_MASK     0x00000400
#define INTCTRL_FAULTSTAT_BUSTKE_MASK    0x00000800
#define INTCTRL_FAULTSTAT_BSTKE_MASK     0x00001000
#define INTCTRL_FAULTSTAT_BLSPERR_MASK   0x00002000
#define INTCTRL_FAULTSTAT_BFARV_MASK     0x00008000
#define INTCTRL_FAULTSTAT_UNDEF_MASK     0x00010000
#define INTCTRL_FAULTSTAT_INVSTAT_MASK   0x00020000
#define INTCTRL_FAULTSTAT_INVPC_MASK     0x00040000
#define INTCTRL_FAULTSTAT_NOCP_MASK      0x00080000
#define INTCTRL_FAULTSTAT_UNALIGN_MASK   0x01000000
#define INTCTRL_FAULTSTAT_DIV0_MASK      0x02000000

#define INTCTRL_HFAULTSTAT_VECT_MASK     0x00000002
#define INTCTRL_HFAULTSTAT_FORCED_MASK   0x40000000
#define INTCTRL_HFAULTSTAT_DBG_MASK      0x80000000

#define INTCTRL_PRIMASK_MASK             0x00000001
#define INTCTRL_FAULTMASK_MASK           0x00000001
#define INTCTRL_BASEPRI_MASK             0x0000000E



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

 
#endif  /* INTCTRL_RGS.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
