#define FBBPP 16
// Only one can be defined. These are only used in this file.
// Or you can "set CDEFINES=-DPANEL_TYPE -DFBBPP=X"
// in your compilation environment window to specify
// these variables.
//#define CRT640 1
//#define SHARP_TFT640 1
//#define KYOCERA_DSTN640 1
//#define SHARP_STN320 1
//#define ALPS_STN320 1
#define NEC_TFT320 1

/******** IMPORTANT SETTINGS *********/
/* register init code, which should be done in boot code
* should no longer needed in driver*/
/******** IMPORTANT SETTINGS *********/
#define TEMP_CODE 1
#define BPP_MASK 0xFFF8
/* For calc. DispDrvr_cdwStride */
#if FBBPP==15
	#define NUM_BPP 16
#else
	#define NUM_BPP FBBPP
#endif
/* For GPE and lcd register values */
#if FBBPP==1
	#define GPEBPP gpe1Bpp
	#define REG_BPPBITS 0
#endif
#if FBBPP==2
	#define GPEBPP gpe2Bpp
	#define REG_BPPBITS 1
#endif
#if FBBPP==4
	#define GPEBPP gpe4Bpp
	#define REG_BPPBITS 2
#endif
#if FBBPP==8
	#define GPEBPP gpe8Bpp
	#define REG_BPPBITS 5
#endif
#if FBBPP==15
	#define GPEBPP gpe16Bpp
	#define REG_BPPBITS 6
#endif
#if FBBPP==16
	#define GPEBPP gpe16Bpp
	#define REG_BPPBITS 7
#endif
/****************************************************************/
// VAL_PANEL_CONTROL 'S bpp NEED NOT BE DEFINE; it will be ignored
// It will be calculated in program using FBBPP.
// VALUE OF VIDEO_OFFSET WILL BE CALCULATED IN PROGRAM using SCREEN_WIDTH.
/****************************************************************/
#ifdef SHARP_TFT640
	#define CRT640 1
#endif
#ifdef CRT640 /* crt, Sharp TFT*/
	#ifdef REG_VAL_DEFINED
		#error More than 1 panel/mode defined!
	#endif
	#define REG_VAL_DEFINED 1
	#define SCREEN_WIDTH 640
	#define SCREEN_HEIGHT 480
	#define VAL_CLK_DIV 0x1808
	#define VAL_PANEL_SELECT 0x0005
	#define VAL_PANEL_CONTROL 0x0600
	#define VAL_MCLK_ENABLE 0x0001
	#define VAL_VCLK_ENABLE 0x0001
	#define VAL_VIDEO_CONTROL 0x0008
	#define VAL_PIXEL_ADJUST 0x00F0
	#define VAL_HDISP_CONTROL 0x4F5B
	#define VAL_HRET_CONTROL 0x5C52
	#define VAL_VDISPE_CONTROL 0x01DF
	#define VAL_VDISP_CONTROL 0x020C
	#define VAL_VRETS_CONTROL 0x01EA
	#define VAL_VRETE_CONTROL 0x0002
	#define VAL_START_ADDRESS 0x0000
#endif
/****************************************************************/
#ifdef KYOCERA_DSTN640
	#ifdef REG_VAL_DEFINED
		#error More than 1 panel/mode defined!
	#endif
	#define REG_VAL_DEFINED 1
	#define SCREEN_WIDTH 640
	#define SCREEN_HEIGHT 480
	#define VAL_CLK_DIV 0x1810
	#define VAL_PANEL_SELECT 0x0006
	#define VAL_PANEL_CONTROL 0x0000
	#define VAL_MCLK_ENABLE 0x0001
	#define VAL_VCLK_ENABLE 0x0001
	#define VAL_VIDEO_CONTROL 0x0008
	#define VAL_PIXEL_ADJUST 0x00F0
	#define VAL_HDISP_CONTROL 0x4F63
	#define VAL_HRET_CONTROL 0x6157
	#define VAL_VDISPE_CONTROL 0x01DF
	#define VAL_VDISP_CONTROL 0x020C
	#define VAL_VRETS_CONTROL 0x01EA
	#define VAL_VRETE_CONTROL 0x0008
	#define VAL_START_ADDRESS 0x0000
#endif
/****************************************************************/
#ifdef SHARP_STN320 /* Sharp STN*/
	#ifdef REG_VAL_DEFINED
		#error More than 1 panel/mode defined!
	#endif
	#define REG_VAL_DEFINED 1
	#define SCREEN_WIDTH 320
	#define SCREEN_HEIGHT 240
	#define VAL_CLK_DIV 0x1A08
	#define VAL_PANEL_SELECT 0x0046
	#define VAL_PANEL_CONTROL 0x0000
	#define VAL_MCLK_ENABLE 0x0001
	#define VAL_VCLK_ENABLE 0x0001
	#define VAL_VIDEO_CONTROL 0x0008
	#define VAL_PIXEL_ADJUST 0x00F0
	#define VAL_HDISP_CONTROL 0x2731
	#define VAL_HRET_CONTROL 0x2F2B
	#define VAL_VDISPE_CONTROL 0x00EF
	#define VAL_VDISP_CONTROL 0x00FF
	#define VAL_VRETS_CONTROL 0x00F1
	#define VAL_VRETE_CONTROL 0x0385
	#define VAL_START_ADDRESS 0x0000
#endif
/****************************************************************/
#ifdef ALPS_STN320
	#ifdef REG_VAL_DEFINED
		#error More than 1 panel/mode defined!
	#endif
	#define REG_VAL_DEFINED 1
	#define SCREEN_WIDTH 320
	#define SCREEN_HEIGHT 240
	#define VAL_CLK_DIV 0x1818
	#define VAL_PANEL_SELECT 0x0008
	#define VAL_PANEL_CONTROL 0x0000
	#define VAL_MCLK_ENABLE 0x0001
	#define VAL_VCLK_ENABLE 0x0001
	#define VAL_VIDEO_CONTROL 0x0008
	#define VAL_PIXEL_ADJUST 0x00F0
	#define VAL_HDISP_CONTROL 0x2831
	#define VAL_HRET_CONTROL 0x2F2B
	#define VAL_VDISPE_CONTROL 0x00EF
	#define VAL_VDISP_CONTROL 0x00FF
	#define VAL_VRETS_CONTROL 0x00F1
	#define VAL_VRETE_CONTROL 0x0002
	#define VAL_START_ADDRESS 0x0000
#endif
/****************************************************************/
#ifdef NEC_TFT320
	#ifdef REG_VAL_DEFINED
		#error More than 1 panel/mode defined!
	#endif
	#define REG_VAL_DEFINED 1
	#define SCREEN_WIDTH 320
	#define SCREEN_HEIGHT 240
	#define VAL_CLK_DIV 0x1830
	#define VAL_PANEL_SELECT 0x0005
	#define VAL_PANEL_CONTROL 0x0400
	#define VAL_MCLK_ENABLE 0x0001
	#define VAL_VCLK_ENABLE 0x0001
	#define VAL_VIDEO_CONTROL 0x0008
	#define VAL_PIXEL_ADJUST 0x00F0
	#define VAL_HDISP_CONTROL 0x2731
	#define VAL_HRET_CONTROL 0x312A
	#define VAL_VDISPE_CONTROL 0x00F0
	#define VAL_VDISP_CONTROL 0x0106
	#define VAL_VRETS_CONTROL 0x00F4
	#define VAL_VRETE_CONTROL 0x000C
	#define VAL_START_ADDRESS 0x0000
#endif
/****************************************************************/
/* Some error checks */
#ifndef REG_VAL_DEFINED
	#error No panel/mode defined!
#endif