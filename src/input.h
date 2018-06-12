#ifndef _INPUT_H_
#define _INPUT_H_
/*=========================*/
/*=========================*/
#define KEY_DOWN		0x01
#define KEY_LEFT		0x02
#define KEY_RIGHT		0x04
#define KEY_UP		0x08
#define KEY_FIRE		0x10
#define KEY_OK		0x20
#define KEY_OPTION	0x40
#define KEY_HELP		0x80
#define KEY_ANY_KEY	0xFF
/*=========================*/
/*=========================*/
#define MSK_MOUSE_DOWN	0x40000000
#define MSK_MOUSE_X		0x3FFF8000
#define MSK_MOUSE_Y		0x00007FFF
/*=========================*/
/*=========================*/
void INP_Trap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void INP_Init(void);
void INP_Quit(void);
ui32 INP_IsKeyDown(int p_vkKey);
ui32 INP_ReadMouseStatus(int *pnX, int *pnY, int *pnB);
ui32 INP_IsMouseDown(void);
/*=========================*/
/*=========================*/
#endif /*_INPUT_H_*/
