/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt_Regs.h
 *       Module:  General-Purpose Timer Registers
 *
 *  Description: General-Purpose Timer Module (GPTM) Registers    
 *  
 *********************************************************************************************************************/
#ifndef GPT_REG.H
#define GPT_REG.H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**/
#define GPT_16_32_BIT_TIMER_0_BASE_ADDRESS        0x40030000
#define GPT_16_32_BIT_TIMER_1_BASE_ADDRESS        0x40031000
#define GPT_16_32_BIT_TIMER_2_BASE_ADDRESS        0x40032000
#define GPT_16_32_BIT_TIMER_3_BASE_ADDRESS        0x40033000
#define GPT_16_32_BIT_TIMER_4_BASE_ADDRESS        0x40034000
#define GPT_16_32_BIT_TIMER_5_BASE_ADDRESS        0x40035000
#define GPT_32_64_BIT_WIDE_TIMER_0_BASE_ADDRESS   0x40036000
#define GPT_32_64_BIT_WIDE_TIMER_1_BASE_ADDRESS   0x40037000
#define GPT_32_64_BIT_WIDE_TIMER_2_BASE_ADDRESS   0x4004C000
#define GPT_32_64_BIT_WIDE_TIMER_3_BASE_ADDRESS   0x4004D000
#define GPT_32_64_BIT_WIDE_TIMER_4_BASE_ADDRESS   0x4004E000
#define GPT_32_64_BIT_WIDE_TIMER_5_BASE_ADDRESS   0x4004F000

/**/
#define GPT_GPTMCFG_BASE_OFFSET    0x000
#define GPT_GPTMTAMR_BASE_OFFSET   0x004
#define GPT_GPTMTBMR_BASE_OFFSET   0x008
#define GPT_GPTMCTL_BASE_OFFSET    0x00C
#define GPT_GPTMIMR_BASE_OFFSET    0x018
#define GPT_GPTMTAR_BASE_OFFSET    0x048
#define GPT_GPTMTBR_BASE_OFFSET    0x04C
#define GPT_GPTMTAILR_BASE_OFFSET  0x028
#define GPT_GPTMTBILR_BASE_OFFSET  0x02C
#define GPT_GPTMRIS_BASE_OFFSET    0x01C
#define GPT_GPTMICR_BASE_OFFSET    0x024
#define GPT_GPTMTAPR_BASE_OFFSET   0x038
#define GPT_GPTMTBPR_BASE_OFFSET   0x03C

/**/
#define GPT_GPTMCFG_GPTMCFG_MASK      0xFFFFFFF8

#define GPT_GPTMTAMR_TAMR_MASK        0xFFFFFFFC
#define GPT_GPTMTAMR_TACMR_MASK       0xFFFFFFFB
#define GPT_GPTMTAMR_TAAMS_MASK       0xFFFFFFF7
#define GPT_GPTMTAMR_TACDIR_MASK      0xFFFFFFEF
#define GPT_GPTMTAMR_TAMIE_MASK       0xFFFFFFDF
#define GPT_GPTMTAMR_TAWOT_MASK       0xFFFFFFBF
#define GPT_GPTMTAMR_TASNAPS_MASK     0xFFFFFF7F
#define GPT_GPTMTAMR_TAILD_MASK       0xFFFFFEFF
#define GPT_GPTMTAMR_TAPWMIE_MASK     0xFFFFFDFF
#define GPT_GPTMTAMR_TAMRSU_MASK      0xFFFFFBFF
#define GPT_GPTMTAMR_TAPLO_MASK       0xFFFFF7FF

#define GPT_GPTMCTL_TAEN_MASK         0xFFFFFFFE
#define GPT_GPTMCTL_TASTALL_MASK      0xFFFFFFFD
#define GPT_GPTMCTL_TAEVENT_MASK      0xFFFFFFF3
#define GPT_GPTMCTL_RTCEN_MASK        0xFFFFFFEF
#define GPT_GPTMCTL_TAOTE_MASK        0xFFFFFFDF
#define GPT_GPTMCTL_TAPWML_MASK       0xFFFFFFBF
#define GPT_GPTMCTL_TBEN_MASK         0xFFFFFEFF
#define GPT_GPTMCTL_TBSTALL_MASK      0xFFFFFDFF
#define GPT_GPTMCTL_TBEVENT_MASK      0xFFFFF3FF
#define GPT_GPTMCTL_TBOTE_MASK        0xFFFFDFFF
#define GPT_GPTMCTL_TBPWML_MASK       0xFFFFBFFF

#define GPT_GPTMIMR_TATOIM_MASK       0xFFFFFFFE
#define GPT_GPTMIMR_CAMIM_MASK        0xFFFFFFFD
#define GPT_GPTMIMR_CAEIM_MASK        0xFFFFFFFB
#define GPT_GPTMIMR_RTCIM_MASK        0xFFFFFFF7
#define GPT_GPTMIMR_TAMIM_MASK        0xFFFFFFEF
#define GPT_GPTMIMR_TBTOIM_MASK       0xFFFFFEFF
#define GPT_GPTMIMR_CBMIM_MASK        0xFFFFFDFF
#define GPT_GPTMIMR_CBEIM_MASK        0xFFFFFBFF
#define GPT_GPTMIMR_TBMIM_MASK        0xFFFFF7FF
#define GPT_GPTMIMR_WUEIM_MASK        0xFFFFEFFF

#define GPT_GPTMIMR_MUSK              0xFFFEF0E0

#define GPT_GPTMTAV_TAV_MASK          0x00000000

/* Clock enable register For GPTM Driver */
#define SYSCTL_RCGCTIMER_REG        (*((volatile uint32 *)0x400FE604))
#define SYSCTL_RCGCW_REG	    (*((volatile uint32 *)0x400FE65C))


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

 
#endif  /* GPT_REG.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
