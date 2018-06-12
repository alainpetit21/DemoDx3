#include <windows.h>
#include "macros.h"
#include "types.h"
#include "input.h"

#define WINCE_KEY_DOWN		40
#define WINCE_KEY_LEFT		37
#define WINCE_KEY_RIGHT		39
#define WINCE_KEY_UP		38
#define WINCE_KEY_FIRE		VK_SPACE
#define WINCE_KEY_OK		VK_ESCAPE
#define WINCE_KEY_OPTION	192
#define WINCE_KEY_HELP		194

unsigned char gJoyBuf;
unsigned long gMouseBuf;

void 
INP_Trap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message){
    case WM_KEYDOWN:
      switch(wParam){
        case WINCE_KEY_DOWN:	
          gJoyBuf|= KEY_DOWN;	break;
        case WINCE_KEY_LEFT:	
          gJoyBuf|= KEY_LEFT;	break;
        case WINCE_KEY_RIGHT :	
          gJoyBuf|= KEY_RIGHT;	break;
        case WINCE_KEY_UP :	
          gJoyBuf|= KEY_UP;		break;
        case WINCE_KEY_FIRE:	
          gJoyBuf|= KEY_FIRE;	break;
        case WINCE_KEY_OK :	
          gJoyBuf|= KEY_OK;		break;
        case WINCE_KEY_OPTION :	
          gJoyBuf|= KEY_OPTION;	break;
        case WINCE_KEY_HELP:	
          gJoyBuf|= KEY_HELP;	break;
      }
      return;
    case WM_KEYUP:
      switch(wParam){
        case WINCE_KEY_DOWN:
          gJoyBuf&= ~KEY_DOWN;	break;
        case WINCE_KEY_LEFT:	
          gJoyBuf&= ~KEY_LEFT;	break;
        case WINCE_KEY_RIGHT :	
          gJoyBuf&= ~KEY_RIGHT;	break;
        case WINCE_KEY_UP :		
          gJoyBuf&= ~KEY_UP;	break;
        case WINCE_KEY_FIRE:	
          gJoyBuf&= ~KEY_FIRE;	break;
        case WINCE_KEY_OK :	
          gJoyBuf&= ~KEY_OK;	break;
        case WINCE_KEY_OPTION :	
          gJoyBuf&= ~KEY_OPTION;break;
        case WINCE_KEY_HELP:	
          gJoyBuf&= ~KEY_HELP;	break;
      }
      return;
    case WM_LBUTTONDOWN:
      gMouseBuf= MSK_MOUSE_DOWN;
      gMouseBuf|= (LOWORD(lParam)<<15);
      gMouseBuf|= ((int)HIWORD(lParam))+26;
      return;
    case WM_LBUTTONUP:
      gMouseBuf&= ~MSK_MOUSE_DOWN;
      return;
  }
  return;
}

void 
INP_Init(void)
{
  gJoyBuf= 0;
}

void 
INP_Quit(void)
{
}

ui32
INP_IsKeyDown(int p_vkKey)
{
  return (gJoyBuf&p_vkKey);
}

ui32
INP_IsMouseDown(void)
{
	return (gMouseBuf&MSK_MOUSE_DOWN);
}

ui32
INP_ReadMouseStatus(int *pnX, int *pnY, int *pnB)
{
  (*pnB)=
    (int)((gMouseBuf&MSK_MOUSE_DOWN)>>30);
  (*pnX)=	
    (int)((gMouseBuf&MSK_MOUSE_DOWN)>>15);
  (*pnY)=	
    (int)(gMouseBuf&MSK_MOUSE_DOWN);
  return 0;
}

