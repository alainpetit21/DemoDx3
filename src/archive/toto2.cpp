#include <windows.h>
#include "toto2.h"
// Look for updated versions of this software at "www.nec.com"
/********************************************
TFT VGA PANEL INITIALIZE PROGRAM for 16 bits per pixel
********************************************/
/****************************************************************/
/* Define LCD register */
#define PANEL_SELECT 0x0
#define PANEL_CONTROL 0x1
#define POWER_CONTROL 0x2
#define MCLK_ENABLE 0x3
#define VCLK_ENABLE 0x4
#define VIDEO_CONTROL 0x5
#define PIXEL_ADJUST 0x6
#define HDISP_CONTROL 0x8
#define HRET_CONTROL 9
#define VDISPE_CONTROL 10
#define VDISP_CONTROL 11
#define VRETS_CONTROL 12
#define VRETE_CONTROL 13
#define START_ADDRESS 14
#define VIDEO_OFFSET 15
// Vrc4171 Companion Chip to drive LCD panels and PC Card interfaces
#define CC_BASE 0xAA800000
#define FRAME_BUFFER 0xAA000000
/****************************************************************/
short *DST_MEM;
short *CC_init_ptr;
short *GMODE_init_ptr;
short *PANEL_init_ptr;
char *LED7SEG = (char *) 0xb600ffa0; // New address on 4102 board. an FPGA change from 4101
short *TERMINAL_LSR = (short *) 0xB600FFCA; // LSR register bit 0 is Receive Data Ready bit.
wchar_t	chainTemp[64];
/****************************************************************/
/****************************************************************/
void crlf(void)
{
	OutputDebugString(L"\r\n");
}
/****************************************************************/
short char_available(void)
{
/*	if ( *TERMINAL_LSR & 0x01) return (1);*/
/*	else return(0);*/
	return (*TERMINAL_LSR & 0x01);
}
/****************************************************************/
// short x,				number of pixels to offset in the Horizontal direction from Left side of screen
// short y,				number of pixels to offset in the Vertical direction from the Top down
// short Width,			Size of Fill in the Horizontal direction
// short Height,		Size of Fill in the Vertical direction
// short ScreenWidth,	LCD panel screen width in pixels 640 or 320 short color)
/****************************************************************/
void Fill16bppScreen(short x, short y, short Width, short Height, short ScreenWidth, short color)
{
long i,j;
// print(" Call FillScreen !\n");
	DST_MEM = (short *) FRAME_BUFFER; // Start from Beginning of Buffer
	DST_MEM += x+(ScreenWidth*(y+Height)); // add in the x & y offsets

// print(" DST_MEM initial value "); putnum(DST_MEM); print(" "); crlf();
// Loop, filling bottom line of rectangle first, then line above the bottom
	for(i=Height; i>0; i--){
		for(j=0; j<(Width+1); j++){
			*((short *)(DST_MEM +j))= color;
		}
		DST_MEM -= ScreenWidth; //DST_MEM didnt change just minus 640 to get previous line
	}
}
/****************************************************************/
int panel_read_out(void)
{
int k01,index1;

	OutputDebugString(L" LCD Panel Registers Read out!"); 
	crlf();

	for(k01=0; k01 < 0x20 ; k01+=2){ // print index array in short 16 bit format
/*		putnum((unsigned short *)(CC_BASE+k01)); */
/*		OutputDebugString(L" -> "); */
/*		putnum(*((unsigned short*)(CC_BASE+(k01)))); */
/*		crlf();*/
		wsprintf(chainTemp, L"%x%s%d\r\n", (CC_BASE+k01), L" -> ", *((unsigned short*)(CC_BASE+(k01))));
		OutputDebugString(chainTemp); 
	}
	return(1);
}

int generic_register_out(unsigned short *BASE_PTR, long count)
{
int k01,index1;

	for(k01=0; k01 < (count<<1) ; k01+=2){ // print index array in short 16 bit format half word addresses
/*		putnum((unsigned short *)(BASE_PTR+k01)); */
/*		OutputDebugString(L" -> "); */
/*		putnum(*((unsigned short *)(BASE_PTR+(k01)))); */
/*		crlf();*/
		wsprintf	(chainTemp, L"%x%s%d\r\n", (BASE_PTR+k01), L" -> ", *((unsigned short*)(BASE_PTR+(k01))));
		OutputDebugString(chainTemp); 
	}
	return(1);
}

// Program to initialize the CRT screen 640 x 480 pixels and/or TFT LCD 640 x 480 panel size
// Then fill screen with a ROSE color background and 5 rectangles of solid
// color. Green, Yellow, Red, Blue, & Black. Continue repeating until a
// key is pressed.
int vr_main(void)
{
	LED7SEG			= (char *) 0xb600ffa0;			// initialize the address again;
	*LED7SEG		= 0x01;							// Show start of Program
	CC_init_ptr		= (short *) 0xb40005fe;			//Set CC top register address
	GMODE_init_ptr	= (short *) 0xab000002;			//Set GMODE register address
	PANEL_init_ptr	= (short *) 0xaa800000;			//Set LCD register address

	OutputDebugString(L" TFT VGA Initialize for 16 bits per pixel format \r\n"); 
/*	crlf();*/

	*CC_init_ptr	= 0x1a08;						//initially 1000h after reset, set the clock speed
	*GMODE_init_ptr = 0x0001;						// 1 write true data values, 0 write inverted data bus values
	PANEL_init_ptr[PANEL_SELECT]	=VAL_PANEL_SELECT;		//0000h register
	PANEL_init_ptr[PANEL_CONTROL]	=VAL_PANEL_CONTROL;		//002h register 16 bits per pixel
	//PANEL_init_ptr[POWER_CONTROL] =0000;			//0004h register !!Careful Power up LCD voltages in strict order!!
	PANEL_init_ptr[MCLK_ENABLE]		=VAL_MCLK_ENABLE;		//0006h register
	PANEL_init_ptr[VCLK_ENABLE]		=VAL_VCLK_ENABLE;		//0008h register VCLK_ENABLE
	PANEL_init_ptr[VIDEO_CONTROL]	=VAL_VIDEO_CONTROL;		//000Ah register VIDEO_CONTROL
	PANEL_init_ptr[PIXEL_ADJUST]	=VAL_PIXEL_ADJUST;		//000Ch register PIXEL_ADJUST
	PANEL_init_ptr[HDISP_CONTROL]	=VAL_HDISP_CONTROL;		//0010h register was 4f63
	PANEL_init_ptr[HRET_CONTROL]	=VAL_HRET_CONTROL;		//0012h register
	PANEL_init_ptr[VDISPE_CONTROL]	=VAL_VDISPE_CONTROL;		//0014h register
	PANEL_init_ptr[VDISP_CONTROL]	=VAL_VDISP_CONTROL;		//0016h register
	PANEL_init_ptr[VRETS_CONTROL]	=VAL_VRETS_CONTROL;		//0018h register
	PANEL_init_ptr[VRETE_CONTROL]	=VAL_VRETE_CONTROL;		//001Ah register
	PANEL_init_ptr[START_ADDRESS]	=VAL_START_ADDRESS;		//001Ch register
	PANEL_init_ptr[VIDEO_OFFSET]	=0x00a0;		//001Eh register 16 bits per pixel
	*LED7SEG		= 0x02;							// Show start of Progra

	if (0 == PANEL_init_ptr[POWER_CONTROL] ){
		PANEL_init_ptr[POWER_CONTROL]=(short) 4;	//0004h register
		Sleep(30000); 
		OutputDebugString(L" delay 1 \r\n");

		PANEL_init_ptr[POWER_CONTROL]=(short) 6;	//0004h register
		Sleep(30000); 
		OutputDebugString(L" delay 2 \r\n");

		PANEL_init_ptr[POWER_CONTROL]=(short) 7;	//0004h register
		Sleep(30000); 
		OutputDebugString(L" delay 3 \r\n");

		PANEL_init_ptr[POWER_CONTROL]=(short) 0xF ; //Turn on the Back light too
	}
	else 
		OutputDebugString(L" TFT power is already on ");

	OutputDebugString(L" TFT VGA 16 BITS PER PIXEL panel is now on! \r\n");

	*LED7SEG		= 0x99;							// Show end of Program
	panel_read_out();								// Dump the LCD panel registers
	generic_register_out((short *)0xAB000002,(long) 1);
	generic_register_out((short *)0xB40005FC,(long) 2);

	while(1){
		if ((PANEL_init_ptr[01] & 0x0F)==0x7){			// checking AA800002 for bits per pixel size
			// fill_16bpp(0xEA9C);
//			Fill16bppScreen(0,0,640,480,640,0xE19C);	//Fill screen with single Rose Color background
//			Fill16bppScreen(120,80,240,240,640,0x06e0); //write a single Green square offset in the center
//			Fill16bppScreen(20,200,80,140,640,0xF7C0);	//write a single Yellow square offset in the center
//			Fill16bppScreen(400,300,180,140,640,0xE800);//write a single Red square offset in the center
//			Fill16bppScreen(400,100,180,140,640,0x001f);//write a single Blue square offset in the center
//			Fill16bppScreen(120,340,240,40,640,0x0000); //write a single Black square offset in the center
			;
		}
		if (char_available()){							// Check for a Key Hit received from the Terminal!
			OutputDebugString(L" Thank you for observing the Vrc4171 demonstration! ");
			exit(1);
		}
		Sleep(200000);
	}
}

int pascal WinMain(HINSTANCE h1,HINSTANCE h2,LPWSTR lpCmdLine,int c)
{
	vr_main();
	return 0;
}
